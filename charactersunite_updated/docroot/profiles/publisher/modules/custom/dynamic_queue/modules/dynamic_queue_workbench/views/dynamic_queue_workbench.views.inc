<?php

/**
 * @file
 * Views integration for Dynamic Queue workbench.
 */

/**
 * Implements hook_views_data_alter().
 */
function dynamic_queue_workbench_views_data_alter(&$data) {

  $data['state_flow_states']['table']['join']['dynamic_queue_revision'] = array(
    'left_field' => 'vid',
    'field' => 'revision_id',
    'type' => 'INNER',
    'extra' => array(
      array(
        'field' => 'entity_type',
        'value' => 'dynamic_queue',
        'operator' => '=',
      ),
    ),
  );

  $data['state_flow_history']['table']['join']['dynamic_queue'] = array(
    'left_field' => 'dqid',
    'field' => 'entity_id',
    'type' => 'INNER',
    'extra' => array(
      array(
        'field' => 'entity_type',
        'value' => 'dynamic_queue',
        'operator' => '=',
      ),
    ),
  );

  $data['state_flow_history']['revision_id']['relationship'] = array(
    'title' => t('Dynamic Queue Revision'),
    'label' => t('Dynamic Queue Revision'),
    'base' => 'dynamic_queue_revision',
    'base field' => 'vid',
    'type' => 'INNER',
  );

  $data['state_flow_history']['dqid'] = array(
    'title' => t('Dynamic Queue'),
    'help' => t('The queue according to the State Flow.'),
    'relationship' => array(
      'base' => 'dynamic_queue',
      'field' => 'entity_id',
      'handler' => 'views_handler_relationship',
      'label' => t('Dynamic Queue'),
    ),
  );
}
