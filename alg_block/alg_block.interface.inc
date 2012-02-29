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
   * Get prepared block view.
   */
  public function getView();

  /**
   * Get prepared block form.
   */
  public function getForm();
}