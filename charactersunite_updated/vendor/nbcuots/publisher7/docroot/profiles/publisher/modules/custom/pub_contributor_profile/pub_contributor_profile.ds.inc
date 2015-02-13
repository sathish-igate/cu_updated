<?php
/**
 * @file
 * pub_contributor_profile.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function pub_contributor_profile_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'user|user|user_image_preview';
  $ds_layout->entity_type = 'user';
  $ds_layout->bundle = 'user';
  $ds_layout->view_mode = 'user_image_preview';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'field_profile_image',
      ),
    ),
    'fields' => array(
      'field_profile_image' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['user|user|user_image_preview'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function pub_contributor_profile_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'user_image_preview';
  $ds_view_mode->label = 'User Image Preview';
  $ds_view_mode->entities = array(
    'user' => 'user',
  );
  $export['user_image_preview'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'user_ref_preview';
  $ds_view_mode->label = 'User Ref Preview';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['user_ref_preview'] = $ds_view_mode;

  return $export;
}
