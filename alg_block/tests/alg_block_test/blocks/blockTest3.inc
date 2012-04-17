<?php

/**
 * @file
 * Block test N3
 */

class BlockTest3 implements AlgBlockInterface {

  /**
   * Get block info
   *
   * @return array
   *   Block info
   */
  public function getInfo() {
    return array(
      'info' => 'blockTest3',
      'region' => 'content',
      'status' => TRUE,
      'visibility' => 0,
      'pages' => '',
    );
  }

  /**
   * Get block roles
   *
   * @return array
   *   Block roles
   */
  public function getRoles() {
    return array(2);
  }

  /**
   * Get block view
   *
   * @return array
   *   Block view
   */
  public function getView() {
    return array(
      'subject' => 'blockTest3',
      'content' => 'Content block test 3',
    );
  }

}
