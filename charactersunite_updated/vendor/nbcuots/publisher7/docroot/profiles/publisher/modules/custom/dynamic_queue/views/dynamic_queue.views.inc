<?php

/**
 * @file
 * Provides Views integration for Dynamic Queue module.
 */

/**
 * Implements hook_views_data_alter().
 */
function dynamic_queue_views_data_alter(&$data) {
  $data['dynamic_queue']['edit_link'] = array(
    'field' => array(
      'title' => t('Operation Links'),
      'help' => t('Provide an Operation link widget for Dynamic Queue.'),
      'handler' => 'dynamic_queue_handler_field_dynamic_queue_operations',
    ),
  );
  $data['dynamic_queue']['status'] = array(
    'title' => t('Published'),
    'help' => t('Whether or not the content is published.'),
    'field' => array(
      'handler' => 'dynamic_queue_handler_field_dynamic_queue_published',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Published'),
      'type' => 'yes-no',
      'use equal' => TRUE, // Use status = 1 instead of status <> 0 in WHERE statment
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['dynamic_queue_revision']['edit_link'] = array(
    'field' => array(
      'title' => t('Operation Links (Revision)'),
      'help' => t('Provide an Operation link widget for Dynamic Queue revisions.'),
      'handler' => 'dynamic_queue_handler_field_dynamic_queue_revision_operations',
    ),
  );
  $data['dynamic_queue_revision']['status'] = array(
    'field' => array(
      'title' => t('Publish State (Revision)'),
      'help' => t('Published or unpublished?'),
      'handler' => 'dynamic_queue_handler_field_dynamic_queue_revision_published',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['dynamic_queue_revision']['is_public'] = array(
    'field' => array(
      'title' => t('Is Public Revision'),
      'help' => t('Is this revision public?'),
      'handler' => 'dynamic_queue_handler_field_dynamic_queue_revision_is_public',
    ),
  );
}
