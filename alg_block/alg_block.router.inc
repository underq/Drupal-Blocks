<?php

/**
 * @file
 * Provide a class for handler block
 */
class AlgBlockRouter {

  private static $blocks = array();
  private static $instance = FALSE;

  /**
   * Constructeur privé
   */
  private function __construct() {
    self::$blocks = module_invoke_all('alg_block_router');
  }

  /**
   * Le clonage interdit
   */
  private function __clone() {

  }

  /**
   * Get instance of alg_block_router class
   * @return object
   *   alg_block_router object
   */
  public static function getInstance() {
    // Si l'instance n'existe pas encore, alors elle est créée.
    if (self::$instance === FALSE) {
      self::$instance = new AlgBlockRouter();
    }
    // L'instance existe, on peut la retourner à l'extérieur.
    return self::$instance;
  }

  /**
   * Get block instance of delta block
   *
   * @param string $delta
   *
   * @return object
   */
  private function getBlockInstance($delta) {
    if (!self::$blocks[$delta] instanceof AlgBlockInterface) {
      require_once self::$blocks[$delta];
      self::$blocks[$delta] = new $delta();
    }
    return self::$blocks[$delta];
  }

  /**
   * List all block which are in module blocks dir
   *
   * @return array
   */
  public function listBlock() {
    $blocks = array();

    foreach (array_keys(self::$blocks) as $delta) {
      $blocks[$delta] = $this->getBlockInstance($delta)->getInfo();
    }

    return $blocks;
  }

  /**
   * View block delta
   *
   * @param string $delta
   *
   * @return array
   */
  public function viewBlock($delta) {
    if (isset(self::$blocks[$delta])) {
      return $this->getBlockInstance($delta)->getView();
    }
  }

  public function configureBlock($delta) {

  }

  public function saveBlock($delta, $edit) {
    
  }

}