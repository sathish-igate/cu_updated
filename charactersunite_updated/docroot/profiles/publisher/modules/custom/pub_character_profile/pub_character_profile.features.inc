<?php
/**
 * @file
 * pub_character_profile.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pub_character_profile_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function pub_character_profile_node_info() {
  $items = array(
    'character_profile' => array(
      'name' => t('Character Profile'),
      'base' => 'node_content',
      'description' => t('Profile of a character.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
