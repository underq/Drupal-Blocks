<?php
/**
 * @file
 * This interface will be used by all custom file block
 */

interface alg_block_interface {

  public function getInfo();

  public function getView();

  public function getForm();
  
}