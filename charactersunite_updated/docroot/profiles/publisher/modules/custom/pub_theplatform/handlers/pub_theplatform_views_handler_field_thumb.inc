<?php

/*
 * @file pub_theplatform_views_handler_field_thumb.inc
 * Basic thePlatform handler for views thumbnail fields.
 */

/*
 * Field handler to provide simple renderer for thePlatform.
 */
class pub_theplatform_views_handler_field_thumb extends views_handler_field {
  /**
   * Get the value that's supposed to be rendered.
   *
   * This uses an api that Views exposes for exactly this simplicity.
   *
   * @param mixed $values
   *   An object containing all retrieved values.
   * @param null $field
   *   Optional name of the field where the value is stored.
   */
  public function get_value($values, $field = NULL) {
    $alias = isset($field) ? $this->aliases[$field] : $this->field_alias;
    if (isset($values->{$alias})) {
      return $values->{$alias};
    }
  }

  /**
   * Render the field.
   *
   * @param mixed $values
   *   The values retrieved from the database.
   *
   * @return string
   *   A string representing the themed image.
   */
  public function render($values) {
    $value = $this->get_value($values);
    return theme_image(array('path' => $value, 'attributes' => array('class' => 'pub-theplatform-thumb')));
  }
}
