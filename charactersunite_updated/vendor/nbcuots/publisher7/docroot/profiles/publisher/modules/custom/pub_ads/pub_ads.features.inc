<?php
/**
 * @file
 * pub_ads.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pub_ads_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "pub_ads" && $api == "pub_ads_file_paths_default") {
    return array("version" => "1");
  }
}
