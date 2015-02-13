<?php
/**
 * @file
 * pub_image_styles.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pub_image_styles_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'imagefield_focus_media_settings';
  $strongarm->value = array(
    'focus' => '1',
    'focus_lock_ratio' => '',
    'focus_min_size' => '',
  );
  $export['imagefield_focus_media_settings'] = $strongarm;

  return $export;
}
