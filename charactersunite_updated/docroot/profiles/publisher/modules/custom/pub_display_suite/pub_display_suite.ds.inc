<?php
/**
 * @file
 * pub_display_suite.ds.inc
 */

/**
 * Implements hook_ds_custom_fields_info().
 */
function pub_display_suite_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'file_name';
  $ds_field->label = 'File Name';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'file' => 'file',
  );
  $ds_field->properties = array(
    'code' => array(
      'value' => '[file:name]',
      'format' => 'ds_code',
    ),
    'use_token' => 1,
  );
  $export['file_name'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function pub_display_suite_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'admin_reference_preview';
  $ds_view_mode->label = 'Administrative Reference Preview';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['admin_reference_preview'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'entityreference_live_preview';
  $ds_view_mode->label = 'Entity Reference Live Preview';
  $ds_view_mode->entities = array(
    'file' => 'file',
  );
  $export['entityreference_live_preview'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'figure';
  $ds_view_mode->label = 'Figure';
  $ds_view_mode->entities = array(
    'file' => 'file',
  );
  $export['figure'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'promoted_content';
  $ds_view_mode->label = 'Promoted Content';
  $ds_view_mode->entities = array(
    'node' => 'node',
    'file' => 'file',
  );
  $export['promoted_content'] = $ds_view_mode;

  return $export;
}
