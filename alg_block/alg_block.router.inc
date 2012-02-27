<?php

class alg_block_router {

  private static $_blocks = array();
  private static $_instance = FALSE;

  /**
   * Constructeur privé
   */
  private function __construct() {
    
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
    if (!array_key_exists($delta, self::$_blocks)) {
      require_once __DIR__ . '/blocks/' . $delta . '.block.inc';
      self::$_blocks[$delta] = new $delta();
    }
    if (!self::$_blocks[$delta] instanceof alg_block_interface) {
      drupal_set_message(t('Le block %delta n\'a pas implémenté l\'interface alg_block_interface', array('%delta' => $delta)), 'error');
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

    $files = file_scan_directory(__DIR__ . '/blocks', '\.block\.inc$');
    foreach ($files as $file) {
      require_once $file->filename;
      $delta = str_replace('.block', '', $file->name);
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
    return $this->getBlockInstance($delta)->getView();
  }

  public function configureBlock($delta) {

  }

  public function saveBlock($delta, $edit) {

  }

}