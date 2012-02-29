<?php

class mes_documents implements AlgBlockInterface {

  public function __construct() {

  }

  public function getInfo() {
    return array(
      'info' => 'Header Mes Documents',
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
      'subject' => t('Mes Documents'),
      'content' => 'HEADER',
    );
  }

  public function getForm() {

  }

}
