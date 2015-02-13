<?php
/**
 * @file
 * pub_media.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function pub_media_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|media_gallery|admin_reference_preview';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'media_gallery';
  $ds_layout->view_mode = 'admin_reference_preview';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'field_cover_item',
      ),
    ),
    'fields' => array(
      'field_cover_item' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|media_gallery|admin_reference_preview'] = $ds_layout;

  return $export;
}
