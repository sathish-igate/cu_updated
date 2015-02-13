<?php
/**
 * @file
 * pub_person.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function pub_person_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_additional_information|node|person|form';
  $field_group->group_name = 'group_additional_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'person';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Additional Information',
    'weight' => '1',
    'children' => array(
      0 => 'field_person_birth_date',
      1 => 'field_person_birth_location',
      2 => 'field_person_external_links',
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
  $export['group_additional_information|node|person|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_legal_name|node|person|form';
  $field_group->group_name = 'group_legal_name';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'person';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_persons_information';
  $field_group->data = array(
    'label' => 'Legal Name',
    'weight' => '12',
    'children' => array(
      0 => 'field_different_legal_name',
      1 => 'field_legal_name_first_name',
      2 => 'field_legal_name_last_name',
      3 => 'field_legal_name_middle_name',
      4 => 'field_legal_name_prefix',
      5 => 'field_legal_name_suffix',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_legal_name|node|person|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_persons_information|node|person|form';
  $field_group->group_name = 'group_persons_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'person';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Person\'s Information',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'field_person_cover_photo',
      2 => 'field_person_first_name',
      3 => 'field_person_last_name',
      4 => 'field_person_middle_name',
      5 => 'field_person_prefix',
      6 => 'field_person_suffix',
      7 => 'field_summary',
      8 => 'group_legal_name',
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
  $export['group_persons_information|node|person|form'] = $field_group;

  return $export;
}
