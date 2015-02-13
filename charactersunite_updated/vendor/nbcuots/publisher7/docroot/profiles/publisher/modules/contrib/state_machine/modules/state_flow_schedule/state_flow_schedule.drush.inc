<?php

/**
 * @file
 * Drush integration for state_flow_schedule.
 */

/**
 * Implements hook_drush_help().
 */
function state_flow_schedule_drush_help($command) {
  switch ($command) {
    case 'drush:state_flow_schedule':
      return dt('Process entities that have been scheduled to publish in state_machine.');
  }
}

/**
 * Implements hook_drush_command().
 */
function state_flow_schedule_drush_command() {
  $items = array();
  $items['process-items'] = array(
    'description' => dt('Process entities that have been scheduled to publish in state_machine.'),
    /* @TODO
    'arguments'   => array(
      'entity_type'    => dt('An optional entity type'),
      'entity_id'    => dt('An optional entity id'),
      'revision_id'    => dt('An optional entity revision id'),
      'time'    => dt('An optional strtotime() string in a valid format'),
    ),
    */
    'examples' => array(
      'Standard example' => 'drush state_flow_schedule',
    ),
    'aliases' => array('smsfs'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  return $items;
}

/**
 * Publish scheduled entities via drush.
 */
function drush_state_flow_schedule_process_items() {
  global $user;
  $user = user_load(1);
  $results = state_flow_schedule_get_scheduled_entities(NULL, NULL, NULL, time());

  if (empty($results)) {
    drush_log(dt('No scheduled items to process.'), 'completed');
    return;
  }
  foreach ($results as $data) {
    state_flow_schedule_process_scheduled_item($data->sid, 'Executed ' . $data->target_event . ' via cron.');
  }
  drupal_set_message(dt('All scheduled items processed.'), 'status');
}
