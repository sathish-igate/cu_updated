<?php
/**
 * @file
 * pub_promotional_content.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pub_promotional_content_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function pub_promotional_content_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function pub_promotional_content_node_info() {
  $items = array(
    'promotional_content' => array(
      'name' => t('Promotional Content'),
      'base' => 'node_content',
      'description' => t('Promoted Content to be used wherever you need a piece of promoted content.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
