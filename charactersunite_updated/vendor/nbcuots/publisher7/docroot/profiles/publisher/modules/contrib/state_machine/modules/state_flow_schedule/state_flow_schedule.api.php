<?php
/**
 * @file
 * The API documentation for state_flow_schedule.
 */

/**
 * Defines the events that are schedulable and the event that is triggered.
 *
 * @return array
 *   Associative array with the schedulable event as key and the event that is
 *   scheduled / triggered as value.
 */
function hook_state_flow_schedule_schedulable_events_alter(&$schedulable_events) {
  $schedulable_events['schedule_unpublish'] = 'unpublish';
}
