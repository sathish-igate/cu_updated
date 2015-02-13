<?php

/**
 * @file
 * A standard views.inc for pub_report.
 */

/**
 * Implements hook_views_data_alter().
 */
function pub_report_server_views_data_alter(&$data) {
  $data['pub_report_sites']['site_name']['filter']['handler'] = 'pub_report_server_handler_filter_sitename';
  $data['pub_report_sites']['modules']['filter']['handler'] = 'pub_report_server_handler_filter_modules';
}

/**
 * Implements hook_views_pre_render().
 */
function pub_report_server_views_pre_render(&$view) {
  switch ($view->name) {
    // Single site report view.
    case 'sitereport':
      foreach ($view->result as $k => $v) {
        $com_str = preg_replace('/[()]/', '', $v->pub_report_sites_modules);
        $arr = explode(',', $com_str);
        asort($arr);
        $v->pub_report_sites_modules = implode(', ', $arr);
      }
      break;

    // List of reports.
    case 'site_reports_view':
      foreach ($view->result as $k => $v) {
        $v->pub_report_sites_time_sent_formatted = date('Y-m-d h:i:s a', $v->pub_report_sites_time_sent);
      }
      foreach ($view->result as $k => $v) {
        $module_diff_array = unserialize($v->pub_report_sites_last_report_diff);
        if ($module_diff_array) {
          $module_versions_diff = $module_diff_array['module_versions'];
        }
        else {
          // We need this to handle old reports that are already in the DB.
          $module_versions_diff = array();
          $module_versions_diff['new_modules'] = array();
          $module_versions_diff['deleted_modules'] = array();
          $module_versions_diff['previous_versions'] = array();
        }
        $v->pub_report_sites_modules_diff = $module_versions_diff;
        $v->mod_updated_count = count((array) $module_versions_diff['previous_versions']);
        $v->mod_deleted_count = count((array) $module_versions_diff['deleted_modules']);
        $v->mod_added_count = count((array) $module_versions_diff['new_modules']);
        $modules = array();
        if ($v->pub_report_sites_api_version == '2.0') {
          $modversions = (array) unserialize($v->pub_report_sites_module_versions);
          foreach ($modversions as $modname => $version) {
            $modules[] = array(
              'name' => $modname,
              'ver' => empty($version) ? 'N/A' : $version,
              'prev_ver' => array_key_exists($modname, $module_versions_diff['previous_versions']) ? $module_versions_diff['previous_versions'][$modname] : '',
              'del' => 0,
              'new' => array_key_exists($modname, $module_versions_diff['new_modules']) ? 1 : 0,
            );
          }
          usort($modules, 'pub_report_server_cmp_module_names');
          foreach ($module_versions_diff['deleted_modules'] as $modname_del => $version_del) {
            $modules[] = array(
              'name' => $modname_del,
              'ver' => $version_del,
              'prev_ver' => '',
              'del' => 1,
              'new' => 0,
            );
          }
          // Display modules in 4 columns.
          $v->mod_in_column = ceil(count($modules) / 4);
        }
        else {
          $com_str = preg_replace('/[()]/', '', $v->pub_report_sites_modules);
          $modules_arr = explode(',', $com_str);
          foreach ($modules_arr as $module) {
            $modules[] = array(
              'name' => $module,
              'ver' => '',
              'prev_ver' => '',
              'del' => 0,
              'new' => array_key_exists($module, $module_versions_diff['new_modules']) ? 1 : 0,
            );
          }
          usort($modules, 'pub_report_server_cmp_module_names');
          foreach ($module_versions_diff['deleted_modules'] as $modname_del => $version_del) {
            $modules[] = array(
              'name' => $modname_del,
              'ver' => '',
              'prev_ver' => '',
              'del' => 1,
              'new' => 0,
            );
          }
          // Display modules in 7 columns.
          $v->mod_in_column = ceil(count($modules) / 7);
        }
        $v->pub_report_sites_modules_array = $modules;
        $v->pub_report_sites_tabular_data_array = unserialize($v->pub_report_sites_tabular_data);
      }
      drupal_add_js(drupal_get_path('module', 'pub_report_server') . '/pub_report_server.scripts.js');
      drupal_add_css(drupal_get_path('module', 'pub_report_server') . '/pub_report_server.styles.css');
      break;

  }
}

/**
 * Compares module names.
 */
function pub_report_server_cmp_module_names($module1, $module2) {
  return $module1['name'] > $module2['name'];
}
