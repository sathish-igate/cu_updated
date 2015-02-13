<?php

/**
 * @file
 * pub_theplatform_views_handler_sort.inc
 */

/**
 * Simple sort handler specifically for sorting by generic fields in thePlatform.
 */
class pub_theplatform_views_handler_sort extends views_handler_sort {

  /**
   * Add the sort to the request.
   */
  public function query() {
    $this->query->thePlatform->sort($this->options['id'], $this->options['order'] === 'DESC');
  }
}
