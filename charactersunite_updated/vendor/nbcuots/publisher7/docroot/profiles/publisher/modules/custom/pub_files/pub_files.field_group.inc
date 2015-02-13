<?php
/**
 * @file
 * pub_files.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function pub_files_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_image_left|file|image|form';
  $field_group->group_name = 'group_image_left';
  $field_group->entity_type = 'file';
  $field_group->bundle = 'image';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_image_top_wrapper';
  $field_group->data = array(
    'label' => 'Left',
    'weight' => '1',
    'children' => array(
      0 => 'field_caption',
      1 => 'preview',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Left',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'file-entity-left-view file-entity-panel',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_image_left|file|image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_image_right|file|image|form';
  $field_group->group_name = 'group_image_right';
  $field_group->entity_type = 'file';
  $field_group->bundle = 'image';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_image_top_wrapper';
  $field_group->data = array(
    'label' => 'Right',
    'weight' => '2',
    'children' => array(
      0 => 'field_file_image_alt_text',
      1 => 'field_file_image_title_text',
      2 => 'field_copyright',
      3 => 'field_credit',
      4 => 'field_keywords',
      5 => 'field_media_categories',
      6 => 'field_media_tags',
      7 => 'field_source',
      8 => 'filename',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'file-entity-right-view file-entity-panel',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_image_right|file|image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_image_top_wrapper|file|image|form';
  $field_group->group_name = 'group_image_top_wrapper';
  $field_group->entity_type = 'file';
  $field_group->bundle = 'image';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Top Wrapper',
    'weight' => '1',
    'children' => array(
      0 => 'group_image_left',
      1 => 'group_image_right',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Top Wrapper',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'clearfix image-top-wrapper',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_image_top_wrapper|file|image|form'] = $field_group;

  return $export;
}
