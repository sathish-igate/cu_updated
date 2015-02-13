<?php

/**
 * @file
 * Contains theme implementations for the TVE MVPD.
 */

/**
 * Theme function for custom radio buttons.
 */
function theme_tve_mvpd_custom_radios($variables) {
  $element = $variables['element'];
  // Get keys from parent's "#options".
  $keys = array_keys($element['#options']);
  $output = '';
  foreach ($keys as $key) {
    // Theme single radio button (customized too).
    $output .= theme('tve_mvpd_custom_radio', $element[$key]);
  }

  return $output;
}

/**
 * Theme for a single radio button.
 */
function theme_tve_mvpd_custom_radio($variables) {
  $element = $variables['element'];
  $html_image = '';
  $image_class = '';
  _form_set_class($element, array('form-radio'));

  $html_radio = '<div class="mvpd-selector-wrapper">' . theme('radio', $variables) . '</div>';
  if ($element['#return_value'] == TVE_MVPD_COLOR_LIGHT || $element['#return_value'] == TVE_MVPD_LOGO_LIGHT) {
    $image_class = 'mvpd-logo-light';
  }

  if (!is_null($element['#title']) && $element['#return_value'] != TVE_MVPD_DEFAULT) {
    $html_image = '<div>' . theme('image', array(
      'path' => $element['#title'],
      'attributes' => array(
        'class' => $image_class,
      ),
    )) . '</div>';
  }
  $label = _tve_mvpd_get_radio_button_label($element['#return_value']);
  // Add styles for custom element.
  drupal_add_css(drupal_get_path('module', 'tve_mvpd') . '/css/tve_mvpd.css');
  // Create "label" HTML element.
  $html_label = theme('html_tag', array(
    'element' => array(
      '#tag' => 'label',
      '#value' => $label . $html_image,
      '#attributes' => array(
        'class' => array('option', 'mvpd-selector'),
        'for' => $element['#id'],
      ),
    ),
  ));

  return '<div class="mvpd-item">' . $html_radio . $html_label . '<div class="clearfix"></div></div>';
}
