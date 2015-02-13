<?php
/**
 * @file
 * pub_editorial.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pub_editorial_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'revision_scheduler_date_pattern';
  $strongarm->value = 'm/d/Y - h:i A';
  $export['revision_scheduler_date_pattern'] = $strongarm;

  return $export;
}
