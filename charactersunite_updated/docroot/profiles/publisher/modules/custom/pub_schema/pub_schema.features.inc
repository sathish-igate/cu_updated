<?php
/**
 * @file
 * pub_schema.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pub_schema_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
