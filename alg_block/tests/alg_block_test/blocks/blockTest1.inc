<?php

/**
 * @file
 * Block test N1
 */

class BlockTest1 implements AlgBlockInterface {

  protected $info = array();

  /**
   * Constructor
   */
  public function __construct() {
    $this->info = array(
      'info' => 'blockTest1',
      'region' => 'content',
      'status' => TRUE,
      'visibility' => 0,
      'pages' => '',
    );
  }

  /**
   * Get block info
   *
   * @return array
   *   Block info
   */
  public function getInfo() {
    return $this->info;
  }

  /**
   * Get block roles
   *
   * @return array
   *   Block roles
   */
  public function getRoles() {
    return array();
  }

  /**
   * Get block view
   *
   * @return array
   *   Block view
   */
  public function getView() {
    return array(
      'subject' => 'blockTest1',
      'content' => 'test',
    );
  }

}
