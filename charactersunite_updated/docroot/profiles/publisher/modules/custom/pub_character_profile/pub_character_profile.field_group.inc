<?php
/**
 * @file
 * pub_character_profile.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function pub_character_profile_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_additional_information|node|character_profile|form';
  $field_group->group_name = 'group_additional_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'character_profile';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Additional Information',
    'weight' => '1',
    'children' => array(
      0 => 'field_character_alias',
      1 => 'field_character_birth_date',
      2 => 'field_character_external_links',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_additional_information|node|character_profile|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_characters_information|node|character_profile|form';
  $field_group->group_name = 'group_characters_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'character_profile';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Character\'s Information',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'field_character_cover_photo',
      2 => 'field_character_first_name',
      3 => 'field_character_last_name',
      4 => 'field_character_middle_name',
      5 => 'field_character_prefix',
      6 => 'field_character_suffix',
      7 => 'field_summary',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_characters_information|node|character_profile|form'] = $field_group;

  return $export;
}
