<?php
/**
 * @file
 * pub_promo_queue.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function pub_promo_queue_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'queues-promo_queue-field_qt_promo_queue'
  $field_instances['queues-promo_queue-field_qt_promo_queue'] = array(
    'bundle' => 'promo_queue',
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
        'weight' => 1,
      ),
    ),
    'entity_type' => 'queues',
    'fences_wrapper' => 'div',
    'field_name' => 'field_qt_promo_queue',
    'label' => 'Queue items',
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
      'weight' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Queue items');

  return $field_instances;
}
