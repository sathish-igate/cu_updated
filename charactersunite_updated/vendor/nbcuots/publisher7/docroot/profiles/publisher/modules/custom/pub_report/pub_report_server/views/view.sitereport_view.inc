<?php

$view = new view();
$view->name = 'sitereport';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'pub_report_sites';
$view->human_name = 'Site Report';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Site Report';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'administer site configuration';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '1';
$handler->display->display_options['style_plugin'] = 'grid';
$handler->display->display_options['style_options']['grouping'] = array(
  0 => array(
    'field' => 'site_name',
    'rendered' => 1,
    'rendered_strip' => 0,
  ),
);
$handler->display->display_options['style_options']['alignment'] = 'vertical';
$handler->display->display_options['row_plugin'] = 'fields';
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['label'] = 'Report not available';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = 'Report not available';
$handler->display->display_options['empty']['area']['format'] = 'wysiwyg_mini';
/* Field: Site Reports: Label */
$handler->display->display_options['fields']['site_name']['id'] = 'site_name';
$handler->display->display_options['fields']['site_name']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['site_name']['field'] = 'site_name';
$handler->display->display_options['fields']['site_name']['label'] = 'Site name';
$handler->display->display_options['fields']['site_name']['element_label_type'] = 'strong';
/* Field: Site Reports: Drupal_version */
$handler->display->display_options['fields']['drupal_version']['id'] = 'drupal_version';
$handler->display->display_options['fields']['drupal_version']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['drupal_version']['field'] = 'drupal_version';
$handler->display->display_options['fields']['drupal_version']['label'] = 'Drupal version';
$handler->display->display_options['fields']['drupal_version']['element_label_type'] = 'strong';
/* Field: Site Reports: Publisher_version */
$handler->display->display_options['fields']['publisher_version']['id'] = 'publisher_version';
$handler->display->display_options['fields']['publisher_version']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['publisher_version']['field'] = 'publisher_version';
$handler->display->display_options['fields']['publisher_version']['label'] = 'Publisher version';
$handler->display->display_options['fields']['publisher_version']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['publisher_version']['empty'] = 'N/A';
/* Field: Site Reports: Publisher_profile */
$handler->display->display_options['fields']['publisher_profile']['id'] = 'publisher_profile';
$handler->display->display_options['fields']['publisher_profile']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['publisher_profile']['field'] = 'publisher_profile';
$handler->display->display_options['fields']['publisher_profile']['label'] = 'Publisher profile';
$handler->display->display_options['fields']['publisher_profile']['element_label_type'] = 'strong';
/* Field: Site Reports: Admin_theme */
$handler->display->display_options['fields']['admin_theme']['id'] = 'admin_theme';
$handler->display->display_options['fields']['admin_theme']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['admin_theme']['field'] = 'admin_theme';
$handler->display->display_options['fields']['admin_theme']['label'] = 'Admin theme';
$handler->display->display_options['fields']['admin_theme']['element_label_type'] = 'strong';
/* Field: Site Reports: Default_theme */
$handler->display->display_options['fields']['default_theme']['id'] = 'default_theme';
$handler->display->display_options['fields']['default_theme']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['default_theme']['field'] = 'default_theme';
$handler->display->display_options['fields']['default_theme']['label'] = 'Default theme';
$handler->display->display_options['fields']['default_theme']['element_label_type'] = 'strong';
/* Field: Site Reports: Modules_count */
$handler->display->display_options['fields']['modules_count']['id'] = 'modules_count';
$handler->display->display_options['fields']['modules_count']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['modules_count']['field'] = 'modules_count';
$handler->display->display_options['fields']['modules_count']['label'] = 'Modules count';
$handler->display->display_options['fields']['modules_count']['element_label_type'] = 'strong';
/* Field: Site Reports: Modules */
$handler->display->display_options['fields']['modules']['id'] = 'modules';
$handler->display->display_options['fields']['modules']['table'] = 'pub_report_sites';
$handler->display->display_options['fields']['modules']['field'] = 'modules';
$handler->display->display_options['fields']['modules']['element_label_type'] = 'strong';
/* Contextual filter: Site Reports: Site reports ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'pub_report_sites';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'admin/reports/pub_report_detail';
