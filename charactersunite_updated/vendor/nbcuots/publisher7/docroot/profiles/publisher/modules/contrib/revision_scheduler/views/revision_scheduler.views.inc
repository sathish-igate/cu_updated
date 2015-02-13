<?php
/**
 * @file
 * Provides support for the Views module.
 */

/**
 * Implements hook_views_data().
 */
function revision_scheduler_views_data() {
  $data = array();
  $data['revision_scheduler']['table']['group'] = t('Revision scheduler');
  $data['revision_scheduler']['id'] = array(
    'title' => t('Revision Scheduler ID'),
    'help' => t('Identifier for the Revision Scheduler action.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['revision_scheduler']['revision_id'] = array(
    'title' => t('Revision ID'),
    'help' => t('Revision ID of the scheduled revision.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['revision_scheduler']['operation'] = array(
    'title' => t('Action'),
    'help' => t('The transition to occur on the scheduled date.'),
    'field' => array(
      'handler' => 'revision_scheduler_handler_field_operation',
      'click sortable' => TRUE,
      'additional fields' => array('entity_id'),
    ),
    'filter' => array(
      'handler' => 'revision_scheduler_handler_filter_operation',
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['revision_scheduler']['time_scheduled'] = array(
    'title' => t('Scheduled time'),
    'help' => t('The scheduled time to perform the transition.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['revision_scheduler']['time_queued'] = array(
    'title' => t('Queued time'),
    'help' => t('The time the revision scheduled event was queued.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'revision_scheduler_handler_filter_date',
    ),
  );
  $data['revision_scheduler']['time_executed'] = array(
    'title' => t('Executed time'),
    'help' => t('The time when the scheduled event was executed.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'revision_scheduler_handler_filter_date',
    ),
  );
  $data['revision_scheduler']['actions'] = array(
    'title' => t('Operations'),
    'help' => t('Revision Scheduler operations.'),
    'real field' => 'operation',
    'field' => array(
      'title' => t('Operations'),
      'handler' => 'revision_scheduler_handler_field_actions',
      'click sortable' => FALSE,
      'additional fields' => array(
        'id',
        'operation',
        'time_scheduled',
        'time_executed',
        'time_queued',
      ),
    ),
  );

  // This is not a real field, it aggregates data from two sources.
  $data['revision_scheduler']['scheduled_executed_time'] = array(
    'field' => array(
      'title' => t('Scheduled or Executed Time'),
      'help' => t('Show the scheduled time if not yet executed otherwise show the executed time.'),
      'handler' => 'revision_scheduler_handler_field_scheduled_executed_time',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_data_alter().
 *
 * @todo Explain why this is here for those who don't know. Can we just declare
 *  base and join on our views data?
 */
function revision_scheduler_views_data_alter(&$data) {
  foreach (entity_get_info() as $entity_type => $info) {
    // Check that this entity type supports revisions.
    $has_revisions = (!empty($info['entity keys']['revision']) && !empty($info['revision table']));
    // Check to make sure the base table is set.
    $has_base = (!empty($info['base table']) && isset($data[$info['base table']]['table']));

    if ($has_revisions && $has_base) {
      $data[$info['base table']]['revision_scheduler'] = array(
        'title' => $data[$info['base table']]['table']['group'],
        'group' => t('Revision Scheduler'),
        'help' => t('Relate entities to revision scheduled events by entity ID.'),
        'relationship' => array(
          'base' => 'revision_scheduler',
          'handler' => 'views_handler_relationship',
          'label' => t('Scheduled revision entity id'),
          'base field' => 'entity_id',
          'relationship field' => $info['entity keys']['id'],
          'extra' => array(
            0 => array(
              'field' => 'entity_type',
              'value' => $entity_type,
            ),
          ),
        ),
      );
      $data[$info['base table']]['revision_scheduler_revision'] = array(
        'title' => $data[$info['base table']]['table']['group'],
        'group' => t('Revision Scheduler revision'),
        'help' => t('Relate entities to revision scheduled events by revision ID.'),
        'relationship' => array(
          'base' => 'revision_scheduler',
          'handler' => 'views_handler_relationship',
          'label' => t('Scheduled revision revision id'),
          'base field' => 'revision_id',
          'relationship field' => $info['entity keys']['revision'],
          'extra' => array(
            0 => array(
              'field' => 'entity_type',
              'value' => $entity_type,
            ),
          ),
        ),
      );
    }
  }
}
