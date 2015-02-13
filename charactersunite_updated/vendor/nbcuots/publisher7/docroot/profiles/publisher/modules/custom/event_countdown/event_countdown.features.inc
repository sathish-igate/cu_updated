<?php
/**
 * @file
 * event_countdown.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function event_countdown_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function event_countdown_node_info() {
  $items = array(
    'event_countdown' => array(
      'name' => t('Event Countdown'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
