<?php
/**
 * @file
 * feature_pub_mpx_file_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function feature_pub_mpx_file_types_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "file_entity" && $api == "file_type") {
    return array("version" => "1");
  }
}
