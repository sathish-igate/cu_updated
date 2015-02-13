<?php
/**
 * @file
 * pub_gigya.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function pub_gigya_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_gigya_share_bar'
  $field_bases['field_gigya_share_bar'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_gigya_share_bar',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'gigya',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'gigya_sharebar',
  );

  return $field_bases;
}
