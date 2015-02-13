<?php
/**
 * @file
 * pub_hide_submit.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pub_hide_submit_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
