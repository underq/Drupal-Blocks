<?php

/**
 * @file
 * Defines a common interface for a prepared block.
 */

interface AlgBlockInterface {

  /**
   * Get prepared block info.
   */
  public function getInfo();

  /**
   * Get user's roles whom can see the block
   */
  public function getRoles();

  /**
   * Get prepared block view.
   */
  public function getView();
}
