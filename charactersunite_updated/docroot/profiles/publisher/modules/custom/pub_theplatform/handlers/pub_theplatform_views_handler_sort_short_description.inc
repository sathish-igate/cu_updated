<?php

/**
 * @file
 * pub_theplatform_views_handler_sort_short_description.inc
 */

/**
 * Simple sort handler specifically for sorting by short description.
 */
class pub_theplatform_views_handler_sort_short_description extends pub_theplatform_views_handler_sort {

  /**
   * Set an option on the query.
   */
  public function query() {
    $this->options['id'] = ':shortDescription';
    parent::query();
  }
}
