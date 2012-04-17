<?php

/**
 * @file
 * Provide a class for handler block
 */

/**
 * AlgBlockRouter Implementation
 */
final class AlgBlockRouter {

  protected $blocks = array();

  const MODULE_NAME = 'alg_block';
  const INSTANCE_NAME = 'alg_block_router_instance';

  /**
   * Private constructor
   */
  protected function __construct() {
    $this->blocks = module_invoke_all('alg_block_router');

    // Initialize the roles.
    $this->applyRolesAll();

    variable_set(self::INSTANCE_NAME, serialize($this));
  }

  /**
   * Forbidden clone
   */
  protected function __clone() {

  }

  /**
   * Get instance of alg_block_router class
   *
   * @param bool $reset
   *   Reset cache instance
   *
   * @return object
   *   alg_block_router object
   */
  public static function getInstance($reset = FALSE) {
    if ($reset === TRUE) {
      self::clearInstance();
    }

    module_invoke_all('alg_autoload');
    module_load_include('interface.inc', 'alg_block');

    $instance = unserialize(variable_get(self::INSTANCE_NAME, NULL));
    if ($instance == NULL) {
      $instance = new self();
    }

    return $instance;
  }

  /**
   * Get block instance from delta
   * Try Factory Design Pattern
   *
   * @param string $delta
   *   Which block to return
   *
   * @return object
   *   Block object
   */
  public function getBlockInstance($delta) {
    // Instance Object.
    if (!is_object($this->blocks[$delta]) && file_exists($this->blocks[$delta])) {
      require_once $this->blocks[$delta];
      $this->blocks[$delta] = new $delta();
    }

    // Check instance of AlgBlockInterface.
    if (!$this->blocks[$delta] instanceof AlgBlockInterface) {
      throw new Exception(t("La classe du block %delta n'implemente pas l'interface AlgBlockInterface", array('%delta' => $delta)));
    }
    return $this->blocks[$delta];
  }

  /**
   * Clear cache instance
   */
  public function clearInstance() {
    variable_del(self::INSTANCE_NAME);
  }

  /**
   * List all block which are in module blocks dir
   *
   * @return array
   *   An array of block descriptions.
   */
  public function listBlock() {
    $blocks = array();

    foreach (array_keys($this->blocks) as $delta) {
      try {
        // Get block object.
        $block = $this->getBlockInstance($delta);

        // Set block list.
        $blocks[$delta] = $block->getInfo();
      } catch (Exception $exc) {
        debug_print($exc->getMessage());
      }
    }

    return $blocks;
  }

  /**
   * Call the applyRoles function for all the defined blocks
   */
  public function applyRolesAll() {
    foreach (array_keys($this->blocks) as $delta) {
      try {
        // Get block object.
        $block = $this->getBlockInstance($delta);

        // Apply block roles if roles have changed.
        $this->applyRoles($block);
      } catch (Exception $exc) {
        debug_print($exc->getMessage());
      }
    }
  }

  /**
   * Check role in DB and create if don't exist or change
   *
   * @param AlgBlockInterface $block
   *   block object
   *
   * @return array
   *   Return array of roles if exist
   */
  public function applyRoles(AlgBlockInterface $block) {
    // Set block roles.
    $rids = $block->getRoles();

    if (!empty($rids)) {
      $args_default = array(self::MODULE_NAME, get_class($block));
      $old_rids = array();

      // Check if roles exists.
      $result = db_query('SELECT rid
                             FROM {blocks_roles}
                             WHERE module = "%s"
                             AND delta = "%s"', $args_default);

      while ($row = db_fetch_array($result)) {
        $old_rids[] = $row['rid'];
      }

      $rids_diff = array_diff($rids, $old_rids);
      if (!empty($rids_diff)) {
        $args_roles = array_merge($rids, $args_default);
        // Delete old roles.
        db_query('DELETE FROM {blocks_roles}
                        WHERE module = "%s"
                        AND delta = "%s"', $args_default);

        // Insertion new roles.
        db_query('INSERT INTO {blocks_roles} (rid, module, delta)
                        VALUES (' . db_placeholders($rids, 'int') . ', "%s", "%s")', $args_roles);
      }

      return $rids;
    }

    return FALSE;
  }

  /**
   * View block delta
   *
   * @param string $delta
   *   Which block to return.
   *
   * @return array
   *   return an array which must define a 'subject' element
   *   (the localized block title) and a 'content' element
   *   (the block body) defining the block indexed by $delta.
   */
  public function viewBlock($delta) {
    global $user;

    if (isset($this->blocks[$delta])) {
      try {
        // Check if the block should be displayed to the current user.
        // Useful when the block is included in a panel.
        foreach ($this->getBlockInstance($delta)->getRoles() as $role) {
          if (in_array($role, array_keys($user->roles))) {
            return $this->getBlockInstance($delta)->getView();
          }
        }
      } catch (Exception $exc) {
        debug_print($exc->getMessage());
      }
    }
  }

}
