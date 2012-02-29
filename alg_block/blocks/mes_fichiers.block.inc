<?php

class mes_fichiers implements AlgBlockInterface {

  public function __construct() {

  }

  public function getInfo() {
    return array(
      'info' => 'Footer Mes Fichiers',
      'region' => 'footer',
      'visibility' => 0,
      'pages' => '',
      'status' => 1,
      'cache' => BLOCK_NO_CACHE,
      'weight' => 50,
    );
  }

  public function getView() {
    return array(
      'subject' => t('Mes Fichiers'),
      'content' => 'FOOTER',
    );
  }

  public function getForm() {

  }

}
