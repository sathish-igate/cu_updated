<?php

/**
 * @file pub_theplatform_views_handler_field_pubdate.inc
 * Basic handler for the views pubDate field.
 */

/**
 * Field handler for the pubDate field for thePlatform.
 */
class pub_theplatform_views_handler_field_pubDate extends views_handler_field_date {

  /**
   * Get the value that's supposed to be rendered.
   *
   * This uses an api that Views exposes for exactly this simplicity.
   *
   * @param mixed $values
   *   An object containing all retrieved values.
   * @param null $field
   *   Optional name of the field where the value is stored.
   *
   * @return string
   *   The date in the desired format.
   */
  public function get_value($values, $field = NULL) {
    $alias = isset($field) ? $this->aliases[$field] : $this->field_alias;

    $pubDate = $values->{$alias};
    // Chop off the 3 unnecessary trailing 0's.
    $date = substr($pubDate, 0, -3);

    return $date;
  }
}
