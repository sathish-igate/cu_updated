<?php
/**
 * @file
 * pub_files.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function pub_files_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'file|image|figure';
  $ds_fieldsetting->entity_type = 'file';
  $ds_fieldsetting->bundle = 'image';
  $ds_fieldsetting->view_mode = 'figure';
  $ds_fieldsetting->settings = array(
    'file_name' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['file|image|figure'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'file|image|promoted_content';
  $ds_fieldsetting->entity_type = 'file';
  $ds_fieldsetting->bundle = 'image';
  $ds_fieldsetting->view_mode = 'promoted_content';
  $ds_fieldsetting->settings = array(
    'file_name' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['file|image|promoted_content'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function pub_files_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'file|image|entityreference_live_preview';
  $ds_layout->entity_type = 'file';
  $ds_layout->bundle = 'image';
  $ds_layout->view_mode = 'entityreference_live_preview';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'file',
      ),
    ),
    'fields' => array(
      'file' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['file|image|entityreference_live_preview'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'file|image|figure';
  $ds_layout->entity_type = 'file';
  $ds_layout->bundle = 'image';
  $ds_layout->view_mode = 'figure';
  $ds_layout->layout = 'html5_figure';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'media' => array(
        0 => 'file',
      ),
      'title' => array(
        0 => 'file_name',
      ),
      'caption' => array(
        0 => 'field_caption',
      ),
    ),
    'fields' => array(
      'file' => 'media',
      'file_name' => 'title',
      'field_caption' => 'caption',
    ),
    'classes' => array(),
  );
  $export['file|image|figure'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'file|image|promoted_content';
  $ds_layout->entity_type = 'file';
  $ds_layout->bundle = 'image';
  $ds_layout->view_mode = 'promoted_content';
  $ds_layout->layout = 'promotional_content';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'media' => array(
        0 => 'file',
      ),
      'marquee' => array(
        0 => 'file_name',
      ),
      'details' => array(
        0 => 'field_caption',
      ),
    ),
    'fields' => array(
      'file' => 'media',
      'file_name' => 'marquee',
      'field_caption' => 'details',
    ),
    'classes' => array(),
  );
  $export['file|image|promoted_content'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'file|video|figure';
  $ds_layout->entity_type = 'file';
  $ds_layout->bundle = 'video';
  $ds_layout->view_mode = 'figure';
  $ds_layout->layout = 'html5_figure';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'media' => array(
        0 => 'file',
      ),
    ),
    'fields' => array(
      'file' => 'media',
    ),
    'classes' => array(),
    'wrappers' => array(),
    'layout_wrapper' => 'div',
  );
  $export['file|video|figure'] = $ds_layout;

  return $export;
}
