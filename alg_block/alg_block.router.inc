<?php

/**
 * @file
 * Provide a class for handler block
 */

final class AlgBlockRouter {

  protected $blocks = array();
  protected static $instance = FALSE;

  const MODULE_NAME = 'alg_block';

  /**
   * Constructeur privé
   */
  protected function __construct() {
    $this->blocks = module_invoke_all('alg_block_router');
  }

  /**
   * Le clonage interdit
   */
  protected function __clone() {

  }

  /**
   * Get instance of alg_block_router class
   * @return object
   *   alg_block_router object
   */
  public static function getInstance() {
    // Si l'instance n'existe pas encore, alors elle est créée.
    if (self::$instance === FALSE) {
      self::$instance = new self();
    }
    // L'instance existe, on peut la retourner à l'extérieur.
    return self::$instance;
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
  protected function getBlockInstance($delta) {

    // Instance Object.
    if (!is_object($this->blocks[$delta])) {
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
   * List all block which are in module blocks dir
   *
   * @return array
   *   An array of block descriptions.
   */
  public function listBlock() {
    $blocks = array();
    $rids = array();

    foreach (array_keys($this->blocks) as $delta) {
      try {
        // Get block object.
        $block = $this->getBlockInstance($delta);

        // Set block list.
        $blocks[$delta] = $block->getInfo();

        // Set block roles.
        $rids = $block->getRoles();

        if (!empty($rids)) {
          $args_default = array(self::MODULE_NAME, $delta);
          $args_roles = array_merge($rids, $args_default);

          $num_rows = db_result(db_query('SELECT COUNT(*) 
                                            FROM {blocks_roles}
                                            WHERE module = "%s"
                                            AND delta = "%s"', $args_default));
          if ($num_rows != count($rids)) {
            // Suppression des anciens roles existant.
            db_query('DELETE FROM {blocks_roles} 
                        WHERE module = "%s"
                        AND delta = "%s"', $args_default);

            // Insertion des nouveaux roles.
            db_query('INSERT INTO {blocks_roles} (rid, module, delta)
                        VALUES (' . db_placeholders($rids, 'int') . ', "%s", "%s")', $args_roles);
          }
        }
      } catch (Exception $exc) {
        debug_print($exc->getMessage());
      }
    }

    return $blocks;
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
    if (isset($this->blocks[$delta])) {
      return $this->getBlockInstance($delta)->getView();
    }
  }

}
