<?php
/**
 * @file
 * pub_display_suite.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pub_display_suite_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
}
