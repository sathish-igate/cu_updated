<?php

$view = new view();
$view->name = 'site_reports_view';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'pub_report_sites';
$view->human_name = 'Site Reports View';
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
  'drupal_version' => 'drupal_version',
  'site_name' => 'site_name',
  'modules_count' => 'modules_count',
  'publisher_profile' => 'publisher_profile',
  'publisher_version' => 'publisher_version',
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
  'drupal_version' => array(
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
  'publisher_profile' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'publisher_version' => array(
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
/* Field: Site Reports: Api_version */
$handler->display->display_options['fields']['api_version']['id'] = 'api_version';
$handler->display->display_options['fields']['api_version']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['api_version']['field'] = 'api_version';
$handler->display->display_options['fields']['api_version']['label'] = 'Report API version';
$handler->display->display_options['fields']['api_version']['empty'] = '1.0';
/* Field: Site Reports: Site reports ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
/* Field: Site Reports: Label */
$handler->display->display_options['fields']['site_name']['id'] = 'site_name';
$handler->display->display_options['fields']['site_name']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['site_name']['field'] = 'site_name';
$handler->display->display_options['fields']['site_name']['label'] = 'Site name';
$handler->display->display_options['fields']['site_name']['alter']['path'] = '[url]';
/* Field: Site Reports: Drupal_version */
$handler->display->display_options['fields']['drupal_version']['id'] = 'drupal_version';
$handler->display->display_options['fields']['drupal_version']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['drupal_version']['field'] = 'drupal_version';
$handler->display->display_options['fields']['drupal_version']['label'] = 'Drupal version';
/* Field: Site Reports: Publisher_version */
$handler->display->display_options['fields']['publisher_version']['id'] = 'publisher_version';
$handler->display->display_options['fields']['publisher_version']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['publisher_version']['field'] = 'publisher_version';
$handler->display->display_options['fields']['publisher_version']['label'] = 'Publisher version';
$handler->display->display_options['fields']['publisher_version']['empty'] = 'N/A';
$handler->display->display_options['fields']['publisher_version']['empty_zero'] = TRUE;
/* Field: Site Reports: Publisher_profile */
$handler->display->display_options['fields']['publisher_profile']['id'] = 'publisher_profile';
$handler->display->display_options['fields']['publisher_profile']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['publisher_profile']['field'] = 'publisher_profile';
$handler->display->display_options['fields']['publisher_profile']['label'] = 'Publisher profile';
/* Field: Site Reports: Admin_theme */
$handler->display->display_options['fields']['admin_theme']['id'] = 'admin_theme';
$handler->display->display_options['fields']['admin_theme']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['admin_theme']['field'] = 'admin_theme';
$handler->display->display_options['fields']['admin_theme']['label'] = 'Admin theme';
/* Field: Site Reports: Default_theme */
$handler->display->display_options['fields']['default_theme']['id'] = 'default_theme';
$handler->display->display_options['fields']['default_theme']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['default_theme']['field'] = 'default_theme';
$handler->display->display_options['fields']['default_theme']['label'] = 'Default theme';
/* Field: Site Reports: Modules_count */
$handler->display->display_options['fields']['modules_count']['id'] = 'modules_count';
$handler->display->display_options['fields']['modules_count']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['modules_count']['field'] = 'modules_count';
$handler->display->display_options['fields']['modules_count']['label'] = 'Modules count';
/* Field: Site Reports: Time_sent */
$handler->display->display_options['fields']['time_sent']['id'] = 'time_sent';
$handler->display->display_options['fields']['time_sent']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['time_sent']['field'] = 'time_sent';
$handler->display->display_options['fields']['time_sent']['label'] = 'Time sent';
$handler->display->display_options['fields']['time_sent']['exclude'] = TRUE;
$handler->display->display_options['fields']['time_sent']['separator'] = '';
/* Field: Site Reports: Modules */
$handler->display->display_options['fields']['modules']['id'] = 'modules';
$handler->display->display_options['fields']['modules']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['modules']['field'] = 'modules';
$handler->display->display_options['fields']['modules']['exclude'] = TRUE;
/* Field: Site Reports: Tabular_data */
$handler->display->display_options['fields']['tabular_data']['id'] = 'tabular_data';
$handler->display->display_options['fields']['tabular_data']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['tabular_data']['field'] = 'tabular_data';
$handler->display->display_options['fields']['tabular_data']['exclude'] = TRUE;
/* Field: Site Reports: Module_versions */
$handler->display->display_options['fields']['module_versions']['id'] = 'module_versions';
$handler->display->display_options['fields']['module_versions']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['module_versions']['field'] = 'module_versions';
$handler->display->display_options['fields']['module_versions']['exclude'] = TRUE;
/* Field: Site Reports: Last_report_diff */
$handler->display->display_options['fields']['last_report_diff']['id'] = 'last_report_diff';
$handler->display->display_options['fields']['last_report_diff']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['last_report_diff']['field'] = 'last_report_diff';
$handler->display->display_options['fields']['last_report_diff']['exclude'] = TRUE;
/* Sort criterion: Site Reports: Time_sent */
$handler->display->display_options['sorts']['time_sent']['id'] = 'time_sent';
$handler->display->display_options['sorts']['time_sent']['table'] = 'pub_report_sites';
$handler->display->display_options['sorts']['time_sent']['field'] = 'time_sent';
$handler->display->display_options['sorts']['time_sent']['order'] = 'DESC';
/* Filter criterion: Site Reports: Label */
$handler->display->display_options['filters']['site_name']['id'] = 'site_name';
$handler->display->display_options['filters']['site_name']['table'] = 'pub_report_sites';
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
/* Filter criterion: Site Reports: Publisher_profile */
$handler->display->display_options['filters']['publisher_profile']['id'] = 'publisher_profile';
$handler->display->display_options['filters']['publisher_profile']['table'] = 'pub_report_sites';
$handler->display->display_options['filters']['publisher_profile']['field'] = 'publisher_profile';
$handler->display->display_options['filters']['publisher_profile']['exposed'] = TRUE;
$handler->display->display_options['filters']['publisher_profile']['expose']['operator_id'] = 'publisher_profile_op';
$handler->display->display_options['filters']['publisher_profile']['expose']['label'] = 'Publisher_profile';
$handler->display->display_options['filters']['publisher_profile']['expose']['operator'] = 'publisher_profile_op';
$handler->display->display_options['filters']['publisher_profile']['expose']['identifier'] = 'publisher_profile';
$handler->display->display_options['filters']['publisher_profile']['is_grouped'] = TRUE;
$handler->display->display_options['filters']['publisher_profile']['group_info']['label'] = 'Publisher_profile';
$handler->display->display_options['filters']['publisher_profile']['group_info']['identifier'] = 'publisher_profile';
$handler->display->display_options['filters']['publisher_profile']['group_info']['group_items'] = array(
  1 => array(
    'title' => 'pub_entertainment',
    'operator' => '=',
    'value' => 'pub_entertainment',
  ),
  2 => array(
    'title' => 'pub_vanilla',
    'operator' => '=',
    'value' => 'pub_vanilla',
  ),
  3 => array(
    'title' => 'pub_dev',
    'operator' => '=',
    'value' => 'pub_dev',
  ),
  4 => array(
    'title' => 'minimal',
    'operator' => '=',
    'value' => 'minimal',
  ),
  5 => array(
    'title' => 'pub_blog',
    'operator' => '=',
    'value' => 'pub_blog',
  ),
  6 => array(
    'title' => 'standard',
    'operator' => '=',
    'value' => 'standard',
  ),
  7 => array(
    'title' => 'testing',
    'operator' => '=',
    'value' => 'testing',
  ),
);
/* Filter criterion: Site Reports: Admin_theme */
$handler->display->display_options['filters']['admin_theme']['id'] = 'admin_theme';
$handler->display->display_options['filters']['admin_theme']['table'] = 'pub_report_sites';
$handler->display->display_options['filters']['admin_theme']['field'] = 'admin_theme';
$handler->display->display_options['filters']['admin_theme']['operator'] = 'contains';
$handler->display->display_options['filters']['admin_theme']['exposed'] = TRUE;
$handler->display->display_options['filters']['admin_theme']['expose']['operator_id'] = 'admin_theme_op';
$handler->display->display_options['filters']['admin_theme']['expose']['label'] = 'Admin theme';
$handler->display->display_options['filters']['admin_theme']['expose']['operator'] = 'admin_theme_op';
$handler->display->display_options['filters']['admin_theme']['expose']['identifier'] = 'admin_theme';
$handler->display->display_options['filters']['admin_theme']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
  7 => 0,
);
/* Filter criterion: Site Reports: Modules */
$handler->display->display_options['filters']['modules']['id'] = 'modules';
$handler->display->display_options['filters']['modules']['table'] = 'pub_report_sites';
$handler->display->display_options['filters']['modules']['field'] = 'modules';
$handler->display->display_options['filters']['modules']['operator'] = 'contains';
$handler->display->display_options['filters']['modules']['exposed'] = TRUE;
$handler->display->display_options['filters']['modules']['expose']['operator_id'] = 'modules_op';
$handler->display->display_options['filters']['modules']['expose']['label'] = 'Has module';
$handler->display->display_options['filters']['modules']['expose']['description'] = '( exact name of the module )';
$handler->display->display_options['filters']['modules']['expose']['operator'] = 'modules_op';
$handler->display->display_options['filters']['modules']['expose']['identifier'] = 'modules';
$handler->display->display_options['filters']['modules']['expose']['remember_roles'] = array(
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
$handler->display->display_options['filters']['last_report']['table'] = 'pub_report_sites';
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
$handler->display->display_options['path'] = 'admin/reports/pub_report';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Publisher Reports';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
