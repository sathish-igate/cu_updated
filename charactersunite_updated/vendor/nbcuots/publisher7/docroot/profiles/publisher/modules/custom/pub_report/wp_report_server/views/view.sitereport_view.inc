<?php

$view = new view();
$view->name = 'wp_sitereport';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'wp_report_sites';
$view->human_name = 'WP Site Report';
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
$handler->display->display_options['fields']['site_name']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['site_name']['field'] = 'site_name';
$handler->display->display_options['fields']['site_name']['label'] = 'Site name';
$handler->display->display_options['fields']['site_name']['element_label_type'] = 'strong';
/* Field: Site Reports: Label */
$handler->display->display_options['fields']['site_fullname']['id'] = 'site_fullname';
$handler->display->display_options['fields']['site_fullname']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['site_fullname']['field'] = 'site_fullname';
$handler->display->display_options['fields']['site_fullname']['label'] = 'Site fullname';
$handler->display->display_options['fields']['site_fullname']['element_label_type'] = 'strong';
/* Field: Site Reports: wordpress_version */
$handler->display->display_options['fields']['wordpress_version']['id'] = 'wordpress_version';
$handler->display->display_options['fields']['wordpress_version']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['wordpress_version']['field'] = 'wordpress_version';
$handler->display->display_options['fields']['wordpress_version']['label'] = 'Wordpress version';
$handler->display->display_options['fields']['wordpress_version']['element_label_type'] = 'strong';
/* Field: Site Reports: nbcupress_version */
$handler->display->display_options['fields']['nbcupress_version']['id'] = 'nbcupress_version';
$handler->display->display_options['fields']['nbcupress_version']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['nbcupress_version']['field'] = 'nbcupress_version';
$handler->display->display_options['fields']['nbcupress_version']['label'] = 'NBCUPress Version';
$handler->display->display_options['fields']['nbcupress_version']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['nbcupress_version']['empty'] = 'N/A';
/* Field: Site Reports: site_plugins */
$handler->display->display_options['fields']['site_plugins']['id'] = 'site_plugins';
$handler->display->display_options['fields']['site_plugins']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['site_plugins']['field'] = 'site_plugins';
$handler->display->display_options['fields']['site_plugins']['element_label_type'] = 'strong';
/* Field: Site Reports: site_plugins_count */
$handler->display->display_options['fields']['site_plugins_count']['id'] = 'site_plugins_count';
$handler->display->display_options['fields']['site_plugins_count']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['site_plugins_count']['field'] = 'site_plugins_count';
$handler->display->display_options['fields']['site_plugins_count']['label'] = 'site_plugins count';
$handler->display->display_options['fields']['site_plugins_count']['element_label_type'] = 'strong';
/* Field: Site Reports: nbcupress_plugins */
$handler->display->display_options['fields']['nbcupress_plugins']['id'] = 'nbcupress_plugins';
$handler->display->display_options['fields']['nbcupress_plugins']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['nbcupress_plugins']['field'] = 'nbcupress_plugins';
$handler->display->display_options['fields']['nbcupress_plugins']['element_label_type'] = 'strong';
/* Field: Site Reports: nbcupress_plugins_count */
$handler->display->display_options['fields']['nbcupress_plugins_count']['id'] = 'nbcupress_plugins_count';
$handler->display->display_options['fields']['nbcupress_plugins_count']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['nbcupress_plugins_count']['field'] = 'nbcupress_plugins_count';
$handler->display->display_options['fields']['nbcupress_plugins_count']['label'] = 'nbcupress_plugins count';
$handler->display->display_options['fields']['nbcupress_plugins_count']['element_label_type'] = 'strong';
/* Field: Site Reports: Default_theme */
$handler->display->display_options['fields']['default_theme']['id'] = 'default_theme';
$handler->display->display_options['fields']['default_theme']['table'] = 'wp_report_sites';
$handler->display->display_options['fields']['default_theme']['field'] = 'default_theme';
$handler->display->display_options['fields']['default_theme']['label'] = 'Default theme';
$handler->display->display_options['fields']['default_theme']['element_label_type'] = 'strong';
/* Contextual filter: Site Reports: Site reports ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'wp_report_sites';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'admin/reports/wp_report_detail';
