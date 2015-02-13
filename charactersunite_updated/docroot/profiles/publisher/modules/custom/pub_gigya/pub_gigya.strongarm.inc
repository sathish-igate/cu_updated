<?php
/**
 * @file
 * pub_gigya.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pub_gigya_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gigya_comments_enabled';
  $strongarm->value = 1;
  $export['gigya_comments_enabled'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gigya_login_enabled';
  $strongarm->value = 0;
  $export['gigya_login_enabled'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gigya_network_list';
  $strongarm->value = 'Facebook, Twitter';
  $export['gigya_network_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gigya_share_advanced';
  $strongarm->value = array(
    'wrap' => 'true',
  );
  $export['gigya_share_advanced'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gigya_share_buttons';
  $strongarm->value = 'twitter-tweet, facebook-like';
  $export['gigya_share_buttons'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gigya_share_image_behavior';
  $strongarm->value = 'first';
  $export['gigya_share_image_behavior'] = $strongarm;

  return $export;
}
