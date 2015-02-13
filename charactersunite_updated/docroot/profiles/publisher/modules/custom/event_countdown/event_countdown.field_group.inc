<?php
/**
 * @file
 * event_countdown.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function event_countdown_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_active|node|event_countdown|form';
  $field_group->group_name = 'group_active';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event_countdown';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Active',
    'weight' => '6',
    'children' => array(
      0 => 'field_active_background_color',
      1 => 'field_active_event',
      2 => 'field_active_event_image',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-active field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_active|node|event_countdown|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_expiry|node|event_countdown|form';
  $field_group->group_name = 'group_expiry';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event_countdown';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Expiry',
    'weight' => '10',
    'children' => array(
      0 => 'field_expiry_background_color',
      1 => 'field_expiry_event',
      2 => 'field_expiry_event_image',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-expiry field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_expiry|node|event_countdown|form'] = $field_group;

  return $export;
}
