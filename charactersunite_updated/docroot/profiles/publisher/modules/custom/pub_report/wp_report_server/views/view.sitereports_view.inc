<?php

$view = new view();
$view->name = 'wp_site_reports_view';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'wp_report_sites';
$view->human_name = 'WP Site Reports View';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Site Reports';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'administer site configuration';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '15';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'id' => 'id',
  'admin_theme' => 'admin_theme',
  'default_theme' => 'default_theme',
  'wordpress_version' => 'wordpress_version',
  'site_name' => 'site_name',
  'modules_count' => 'modules_count',
  'publisher_profile' => 'publisher_profile',
  'nbcupress_version' => 'nbcupress_version',
  'url' => 'url',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'id' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'admin_theme' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'default_theme' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'wordpress_version' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'site_name' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'modules_count' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'nbcupress_version' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'url' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* Footer: Global: Result summary */
$handler->display->display_options['footer']['result']['id'] = 'result';
$handler->display->display_options['footer']['result']['table'] = 'views';
$handler->display->display_options['footer']['result']['field'] = 'result';
/* Field: Site Reports: Site reports ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
/* Field: Site Reports: Label */
$handler->display->display_options['fields']['site_name']['id'] = 'site_name';
$handler->display->display_options['fields']['site_name']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['site_name']['field'] = 'site_name';
$handler->display->display_options['fields']['site_name']['label'] = 'Site name';
$handler->display->display_options['fields']['site_name']['alter']['path'] = '[url]';
/* Field: Site Reports: site_fullname */
$handler->display->display_options['fields']['site_fullname']['id'] = 'site_fullname';
$handler->display->display_options['fields']['site_fullname']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['site_fullname']['field'] = 'site_fullname';
$handler->display->display_options['fields']['site_fullname']['label'] = 'Site Fullname';
/* Field: Site Reports: Api_version */
$handler->display->display_options['fields']['api_version']['id'] = 'api_version';
$handler->display->display_options['fields']['api_version']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['api_version']['field'] = 'api_version';
$handler->display->display_options['fields']['api_version']['label'] = 'Report API version';
$handler->display->display_options['fields']['api_version']['empty'] = '1.0';
/* Field: Site Reports: wordpress_version */
$handler->display->display_options['fields']['wordpress_version']['id'] = 'wordpress_version';
$handler->display->display_options['fields']['wordpress_version']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['wordpress_version']['field'] = 'wordpress_version';
$handler->display->display_options['fields']['wordpress_version']['label'] = 'Wordpress version';
/* Field: Site Reports: nbcupress_version */
$handler->display->display_options['fields']['nbcupress_version']['id'] = 'nbcupress_version';
$handler->display->display_options['fields']['nbcupress_version']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['nbcupress_version']['field'] = 'nbcupress_version';
$handler->display->display_options['fields']['nbcupress_version']['label'] = 'NBCUPress Version';
/* Field: Site Reports: site_plugins */
$handler->display->display_options['fields']['site_plugins']['id'] = 'site_plugins';
$handler->display->display_options['fields']['site_plugins']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['site_plugins']['field'] = 'site_plugins';
$handler->display->display_options['fields']['site_plugins']['label'] = 'Site Plugins';
$handler->display->display_options['fields']['site_plugins']['exclude'] = TRUE;
/* Field: Site Reports: site_plugins_count */
$handler->display->display_options['fields']['site_plugins_count']['id'] = 'site_plugins_count';
$handler->display->display_options['fields']['site_plugins_count']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['site_plugins_count']['field'] = 'site_plugins_count';
$handler->display->display_options['fields']['site_plugins_count']['label'] = 'site_plugins count';
/* Field: Site Reports: nbcupress_plugins */
$handler->display->display_options['fields']['nbcupress_plugins']['id'] = 'nbcupress_plugins';
$handler->display->display_options['fields']['nbcupress_plugins']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['nbcupress_plugins']['field'] = 'nbcupress_plugins';
$handler->display->display_options['fields']['nbcupress_plugins']['label'] = 'nbcupress Plugins';
$handler->display->display_options['fields']['nbcupress_plugins']['exclude'] = TRUE;
/* Field: Site Reports: nbcupress_plugins_count */
$handler->display->display_options['fields']['nbcupress_plugins_count']['id'] = 'nbcupress_plugins_count';
$handler->display->display_options['fields']['nbcupress_plugins_count']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['nbcupress_plugins_count']['field'] = 'nbcupress_plugins_count';
$handler->display->display_options['fields']['nbcupress_plugins_count']['label'] = 'nbcupress_plugins count';
/* Field: Site Reports: Default_theme */
$handler->display->display_options['fields']['default_theme']['id'] = 'default_theme';
$handler->display->display_options['fields']['default_theme']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['default_theme']['field'] = 'default_theme';
$handler->display->display_options['fields']['default_theme']['label'] = 'Default theme';
/* Field: Site Reports: Time_sent */
$handler->display->display_options['fields']['time_sent']['id'] = 'time_sent';
$handler->display->display_options['fields']['time_sent']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['time_sent']['field'] = 'time_sent';
$handler->display->display_options['fields']['time_sent']['label'] = 'Time sent';
$handler->display->display_options['fields']['time_sent']['exclude'] = TRUE;
$handler->display->display_options['fields']['time_sent']['separator'] = '';
/* Field: Site Reports: Last_report_diff */
$handler->display->display_options['fields']['last_report_diff']['id'] = 'last_report_diff';
$handler->display->display_options['fields']['last_report_diff']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['last_report_diff']['field'] = 'last_report_diff';
$handler->display->display_options['fields']['last_report_diff']['exclude'] = TRUE;
/* Field: Site Reports: Last_report_diff_nbcupress */
$handler->display->display_options['fields']['last_report_diff_nbcupress']['id'] = 'last_report_diff_nbcupress';
$handler->display->display_options['fields']['last_report_diff_nbcupress']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['last_report_diff_nbcupress']['field'] = 'last_report_diff_nbcupress';
$handler->display->display_options['fields']['last_report_diff_nbcupress']['exclude'] = TRUE;
/* Sort criterion: Site Reports: Time_sent */
$handler->display->display_options['sorts']['time_sent']['id'] = 'time_sent';
$handler->display->display_options['sorts']['time_sent']['table'] = 'wp_report_sites';
$handler->display->display_options['sorts']['time_sent']['field'] = 'time_sent';
$handler->display->display_options['sorts']['time_sent']['order'] = 'DESC';
/* Filter criterion: Site Reports: Label */
$handler->display->display_options['filters']['site_name']['id'] = 'site_name';
$handler->display->display_options['filters']['site_name']['table'] = 'wp_report_sites';
$handler->display->display_options['filters']['site_name']['field'] = 'site_name';
$handler->display->display_options['filters']['site_name']['group'] = 1;
$handler->display->display_options['filters']['site_name']['exposed'] = TRUE;
$handler->display->display_options['filters']['site_name']['expose']['operator_id'] = '';
$handler->display->display_options['filters']['site_name']['expose']['operator'] = 'site_name_op';
$handler->display->display_options['filters']['site_name']['expose']['identifier'] = 'site_name';
$handler->display->display_options['filters']['site_name']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
  7 => 0,
);
/* Filter criterion: Site Reports: Last_report */
$handler->display->display_options['filters']['last_report']['id'] = 'last_report';
$handler->display->display_options['filters']['last_report']['table'] = 'wp_report_sites';
$handler->display->display_options['filters']['last_report']['field'] = 'last_report';
$handler->display->display_options['filters']['last_report']['exposed'] = TRUE;
$handler->display->display_options['filters']['last_report']['expose']['operator_id'] = 'last_report_op';
$handler->display->display_options['filters']['last_report']['expose']['label'] = 'Last_report';
$handler->display->display_options['filters']['last_report']['expose']['operator'] = 'last_report_op';
$handler->display->display_options['filters']['last_report']['expose']['identifier'] = 'last_report';
$handler->display->display_options['filters']['last_report']['is_grouped'] = TRUE;
$handler->display->display_options['filters']['last_report']['group_info']['label'] = 'Time sent';
$handler->display->display_options['filters']['last_report']['group_info']['identifier'] = 'last_report';
$handler->display->display_options['filters']['last_report']['group_info']['default_group'] = '1';
$handler->display->display_options['filters']['last_report']['group_info']['group_items'] = array(
  1 => array(
    'title' => 'most recent',
    'operator' => '=',
    'value' => array(
      'value' => '1',
      'min' => '',
      'max' => '',
    ),
  ),
  2 => array(
    'title' => '',
    'operator' => '=',
    'value' => array(
      'value' => '',
      'min' => '',
      'max' => '',
    ),
  ),
  3 => array(
    'title' => '',
    'operator' => '=',
    'value' => array(
      'value' => '',
      'min' => '',
      'max' => '',
    ),
  ),
);

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'admin/reports/wp_report';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Wordpress Reports';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
