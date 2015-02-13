<?php

/*
 * @file pub_theplatform_views_handler_field_category.inc
 * Basic thePlatform handler for views categories from thePlatform fields.
 */

/*
 * Field handler to provide simple renderer for thePlatform.
 */
class pub_theplatform_views_handler_field_category extends views_handler_field {

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
   * @return array|mixed|string
   *   Information about the category.
   */
  function get_value($values, $field = NULL) {
    $alias = isset($field) ? $this->aliases[$field] : $this->field_alias;

    $categories = array();
    if (isset($values->{$alias}) && is_array($values->{$alias})) {
      foreach ($values->{$alias} as $item) {
        if (is_object($item) && isset($item->{'media$name'})) {
          $categories[] = $item->{'media$name'};
        }
      }
    }

    // Let's only return the last part of the most specific category.
    $category = array_pop($categories);
    // Chop off the Chiller/Movies or Chiller/TV Shows portion of category.
    $single_category = preg_split("/\/[a-zA-Z' ]+$/", $category);
    $single_category = str_replace($single_category[0], '', $category);
    $single_category = substr($single_category, 1);

    return $single_category;
  }
}
