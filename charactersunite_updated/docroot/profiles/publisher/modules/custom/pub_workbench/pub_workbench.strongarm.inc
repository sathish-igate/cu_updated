<?php
/**
 * @file
 * pub_workbench.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pub_workbench_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'state_flow_etity_date_format';
  $strongarm->value = 'edit_date';
  $export['state_flow_etity_date_format'] = $strongarm;

  return $export;
}
