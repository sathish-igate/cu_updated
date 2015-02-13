<?php

/*
 * @file pub_mpx_views_handler_field_mpx_video_thumbnail_url.inc
 */

/**
 * Field handler to provide simple renderer for mpx video thumbnails.
 */
class pub_mpx_views_handler_field_mpx_video_thumbnail_url extends views_handler_field {

  /**
   * Get the value that's supposed to be rendered.
   *
   * This uses an api that Views exposes for exactly this simplicity.
   *
   * @param $values
   *   An object containing all retrieved values.
   * @param $field
   *   Optional name of the field where the value is stored.
   *
   * @return string
   */
  function get_value($values, $field = NULL) {
    $alias = isset($field) ? $this->aliases[$field] : $this->field_alias;
    if (isset($values->{$alias})) {
      return $values->{$alias};
    }
  }

  /**
   * Render the field.
   *
   * @param $values
   *   The values retrieved from the database.
   *
   * @return string
   */
  function render($values) {
    $value = $this->get_value($values);
    if ($value) {
      // If we don't get a proper cached thumbnail path, we fall back to
      // rendering the MPX image directly.
      if (!($cached_thumbnail = pub_mpx_cache_thumbnail($value))) {
        return theme('image', array('path' => $value, 'width' => 100, 'attributes' => array('class' => 'pub-mpx-video-thumbnail')));
      }

      $options = array(
        'style_name' => $this->options['image_style'],
        'path' => $cached_thumbnail,
        'attributes' => array(
          'class' => 'pub-mpx-video-thumbnail',
        ),
      );
      $result = theme('image_style', $options);
      return $result;
    }
    return '';
  }

  /**
   * Override option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();
    // By default, use the 100x100 thumbnail style.
    $options['image_style'] = array(
      'default' => 'thumbnail',
    );

    return $options;
  }

  /**
   * Override options_form().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['image_style'] = array(
      '#type' => 'select',
      '#title' => t('Image style'),
      '#options' => image_style_options(TRUE, PASS_THROUGH),
      '#default_value' => $this->options['image_style'],
    );
  }
}
