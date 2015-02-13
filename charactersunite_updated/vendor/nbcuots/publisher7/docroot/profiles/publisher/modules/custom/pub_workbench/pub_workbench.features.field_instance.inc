<?php
/**
 * @file
 * pub_workbench.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function pub_workbench_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'state_flow_history_entity-state_flow_history_entity-field_workbench_assigned'
  $field_instances['state_flow_history_entity-state_flow_history_entity-field_workbench_assigned'] = array(
    'bundle' => 'state_flow_history_entity',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'state_flow_history_entity',
    'fences_wrapper' => 'div',
    'field_name' => 'field_workbench_assigned',
    'label' => 'Assign to',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Assign to');

  return $field_instances;
}
