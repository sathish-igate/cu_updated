<?php

/**
 * @file
 * A standard views.inc for wp_pub_server.
 */

/**
 * Implements hook_views_data_alter().
 */
function wp_report_server_views_data_alter(&$data) {
  $data['wp_report_sites']['site_name']['filter']['handler'] = 'wp_report_server_handler_filter_sitename';
  $data['wp_report_sites']['site_plugins']['filter']['handler'] = 'wp_report_server_handler_filter_site_plugins';
}

/**
 * Implements hook_views_pre_render().
 */
function wp_report_server_views_pre_render(&$view) {
  switch ($view->name) {
    // Single site report view.
    case 'wpsitereport':
      foreach ($view->result as $k => $v) {
        $com_str = preg_replace('/[()]/', '', $v->wp_report_sites_site_plugins);
        $arr = explode(',', $com_str);
        asort($arr);
        $v->wp_report_sites_site_plugins = implode(', ', $arr);
      }
      break;

    // List of reports.
    case 'wp_site_reports_view':
      foreach ($view->result as $k => $v) {
        $v->wp_report_sites_time_sent_formatted = date('Y-m-d h:i:s a', $v->wp_report_sites_time_sent);
      }
      foreach ($view->result as $k => $v) {
        // Calculate site plugin differences.
        $plugin_diff_array = unserialize($v->wp_report_sites_last_report_diff);
        if ($plugin_diff_array) {
          $plugin_versions_diff = $plugin_diff_array['site_plugin_versions'];
        }
        else {
          // We need this to handle old reports that are already in the DB.
          $plugin_versions_diff = array();
          $plugin_versions_diff['new_site_plugins'] = array();
          $plugin_versions_diff['deleted_site_plugins'] = array();
          $plugin_versions_diff['previous_versions'] = array();
        }
        $v->wp_report_sites_site_plugins_diff = $plugin_versions_diff;
        $v->mod_updated_count = count((array) $plugin_versions_diff['previous_versions']);
        $v->mod_deleted_count = count((array) $plugin_versions_diff['deleted_site_plugins']);
        $v->mod_added_count = count((array) $plugin_versions_diff['new_site_plugins']);
        $site_plugins = array();

        $sitepluginsversions = (array) unserialize($v->wp_report_sites_site_plugins);
        foreach ($sitepluginsversions as $plugname => $version) {
          $site_plugins[] = array(
            'name' => $plugname,
            'ver' => empty($version) ? 'N/A' : $version,
            'prev_ver' => array_key_exists($plugname, $plugin_versions_diff['previous_versions']) ? $plugin_versions_diff['previous_versions'][$plugname] : '',
            'del' => 0,
            'new' => array_key_exists($plugname, $plugin_versions_diff['new_site_plugins']) ? 1 : 0,
          );
        }
        usort($site_plugins, 'wp_report_server_cmp_plugin_names');
        foreach ($plugin_versions_diff['deleted_site_plugins'] as $plugname_del => $version_del) {
          $site_plugins[] = array(
            'name' => $plugname_del,
            'ver' => $version_del,
            'prev_ver' => '',
            'del' => 1,
            'new' => 0,
          );
        }
        // Display site_plugins in 4 columns.
        $v->mod_in_column = ceil(count($site_plugins) / 4);

        $v->wp_report_sites_site_plugins_array = $site_plugins;
        // Calculate nbcupress plugin differences.
        $plugin_diff_array = unserialize($v->wp_report_sites_last_report_diff_nbcupress);
        if ($plugin_diff_array) {
          $plugin_versions_diff = $plugin_diff_array['nbcupress_plugin_versions'];
        }
        else {
          // We need this to handle old reports that are already in the DB.
          $plugin_versions_diff = array();
          $plugin_versions_diff['new_site_plugins'] = array();
          $plugin_versions_diff['deleted_site_plugins'] = array();
          $plugin_versions_diff['previous_versions'] = array();
        }
        $v->wp_report_sites_site_plugins_diff_nbcupress = $plugin_versions_diff;
        $v->mod_updated_count_nbcupress = count((array) $plugin_versions_diff['previous_versions']);
        $v->mod_deleted_count_nbcupress = count((array) $plugin_versions_diff['deleted_site_plugins']);
        $v->mod_added_count_nbcupress = count((array) $plugin_versions_diff['new_site_plugins']);
        $nbcupress_plugins = array();

        $nbcupresspluginsversions = (array) unserialize($v->wp_report_sites_nbcupress_plugins);
        foreach ($nbcupresspluginsversions as $plugname => $version) {
          $nbcupress_plugins[] = array(
            'name' => $plugname,
            'ver' => empty($version) ? 'N/A' : $version,
            'prev_ver' => array_key_exists($plugname, $plugin_versions_diff['previous_versions']) ? $plugin_versions_diff['previous_versions'][$plugname] : '',
            'del' => 0,
            'new' => array_key_exists($plugname, $plugin_versions_diff['new_site_plugins']) ? 1 : 0,
          );
        }
        usort($site_plugins, 'wp_report_server_cmp_plugin_names');
        foreach ($plugin_versions_diff['deleted_site_plugins'] as $plugname_del => $version_del) {
          $nbcupress_plugins[] = array(
            'name' => $plugname_del,
            'ver' => $version_del,
            'prev_ver' => '',
            'del' => 1,
            'new' => 0,
          );
        }
        // Display site_plugins in 4 columns.
        $v->mod_in_column_nbcupress = ceil(count($nbcupress_plugins) / 4);

        $v->wp_report_sites_nbcupress_plugins_array = $nbcupress_plugins;
      }
      drupal_add_js(drupal_get_path('module', 'pub_report_server') . '/pub_report_server.scripts.js');
      drupal_add_css(drupal_get_path('module', 'pub_report_server') . '/pub_report_server.styles.css');
      break;
  }
}

/**
 * Compares plugin names.
 */
function wp_report_server_cmp_plugin_names($plugin1, $plugin2) {
  return $plugin1['name'] > $plugin2['name'];
}
