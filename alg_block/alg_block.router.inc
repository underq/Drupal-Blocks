<?php

class alg_block_router {

  private static $_blocks = array();
  private static $_instance = FALSE;

  /**
   * Constructeur privé
   */
  private function __construct() {
    foreach (module_implements('alg_block_router') as $module) {
      foreach (module_invoke($module, 'alg_block_router') as $delta => $filepath) {
        if (file_exists($filepath)) {
          self::$_blocks[$delta] = $filepath;
        }
        else {
          drupal_set_message(t('Block %delta ! file missing', array('%delta' => $delta)), 'error');
        }
      }
    }
  }

  /**
   * Le clonage interdit
   */
  private function __clone() {
    
  }

  /**
   * Get instance of alg_block_router class
   * @return type
   */
  public static function getInstance() {
    // Si l'instance n'existe pas encore, alors elle est créée.
    if (self::$_instance === FALSE) {
      self::$_instance = new alg_block_router();
    }
    // L'instance existe, on peut la retourner à l'extérieur.
    return self::$_instance;
  }

  /**
   * Get block instance of delta block
   * 
   * @param string $delta
   * @return object
   */
  private function getBlockInstance($delta) {
    if (!self::$_blocks[$delta] instanceof alg_block_interface) {
      require_once self::$_blocks[$delta];
      self::$_blocks[$delta] = new $delta();
    }
    return self::$_blocks[$delta];
  }

  /**
   * List all block which are in module blocks dir
   * 
   * @return array
   */
  public function listBlock() {
    $blocks = array();

    foreach (self::$_blocks as $delta => $filepath) {
      $blocks[$delta] = $this->getBlockInstance($delta)->getInfo();
    }

    return $blocks;
  }

  /**
   * View block delta
   * 
   * @param string $delta
   * @return array
   */
  public function viewBlock($delta) {
    if (isset(self::$_blocks[$delta])) {
      return $this->getBlockInstance($delta)->getView();
    }
  }

  public function configureBlock($delta) {

  }

  public function saveBlock($delta, $edit) {

  }

}