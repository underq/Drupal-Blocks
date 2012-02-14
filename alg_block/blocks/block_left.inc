<?php

/**
 * @info Block Left
 * @region left
 * @visibility 1
 * @pages page/1
 * @status 1
 * @cache BLOCK_NO_CACHE
 * @weigth 0
 */
function block_left() {
  return array(
    'subject' => t('Block Left'),
    'content' => 'Left Menu block',
  );
}


// Class qui sers de modele à tous les blocks
class Block{
  static $info
  static $region
  static $visibility
  static $pages
  static $cache
  static $weight
  
  public function output();    
    
}

// class fille qui definit le block demander
class BlockLeft extends Block{
  public function output(){
    
    return array(
      'subject' => t('Block Left'),
      'content' => 'Left Menu block',
    );
  }
  
}