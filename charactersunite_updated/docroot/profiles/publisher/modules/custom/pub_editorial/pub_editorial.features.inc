<?php
/**
 * @file
 * pub_editorial.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pub_editorial_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "permission_sets" && $api == "default_permission_sets") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function pub_editorial_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
