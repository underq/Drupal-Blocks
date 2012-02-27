<?php

class mes_documents implements alg_block_interface {

  public function __construct() {
    
  }

  public function getInfo() {
    return array(
      'info' => 'Header',
      'region' => 'header',
      'visibility' => 0,
      'pages' => '',
      'status' => 1,
      'cache' => BLOCK_NO_CACHE,
      'weight' => 50,
    );
  }

  public function getView() {
    return array(
      'subject' => t('Block Left'),
      'content' => 'Left Menu block',
    );
  }

}
