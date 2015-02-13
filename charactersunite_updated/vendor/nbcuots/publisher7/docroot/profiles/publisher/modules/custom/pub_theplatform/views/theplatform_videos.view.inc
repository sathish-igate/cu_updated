<?php

$view = new view();
$view->name = 'theplatform_videos';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'thePlatform';
$view->human_name = 'thePlatform Videos';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'thePlatform Videos';
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['exposed_form']['options']['autosubmit'] = FALSE;
$handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = FALSE;
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '100';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'guid' => 'guid',
  'custom_runtime' => 'custom_runtime',
  'pl1_shortDescription' => 'pl1_shortDescription',
  'plmedia_defaultThumbnailUrl' => 'plmedia_defaultThumbnailUrl',
  'title' => 'title',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'guid' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'custom_runtime' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'pl1_shortDescription' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'plmedia_defaultThumbnailUrl' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'title' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* Field: thePlatform: Reference ID */
$handler->display->display_options['fields']['guid']['id'] = 'guid';
$handler->display->display_options['fields']['guid']['table'] = 'thePlatform';
$handler->display->display_options['fields']['guid']['field'] = 'guid';
/* Field: thePlatform: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'thePlatform';
$handler->display->display_options['fields']['title']['field'] = 'title';
/* Field: thePlatform: Runtime */
$handler->display->display_options['fields']['custom_runtime']['id'] = 'custom_runtime';
$handler->display->display_options['fields']['custom_runtime']['table'] = 'thePlatform';
$handler->display->display_options['fields']['custom_runtime']['field'] = 'custom_runtime';
/* Field: thePlatform: Short Description */
$handler->display->display_options['fields']['pl1_shortDescription']['id'] = 'pl1_shortDescription';
$handler->display->display_options['fields']['pl1_shortDescription']['table'] = 'thePlatform';
$handler->display->display_options['fields']['pl1_shortDescription']['field'] = 'pl1_shortDescription';
/* Field: thePlatform: Thumbnail */
$handler->display->display_options['fields']['plmedia_defaultThumbnailUrl']['id'] = 'plmedia_defaultThumbnailUrl';
$handler->display->display_options['fields']['plmedia_defaultThumbnailUrl']['table'] = 'thePlatform';
$handler->display->display_options['fields']['plmedia_defaultThumbnailUrl']['field'] = 'plmedia_defaultThumbnailUrl';
/* Filter criterion: thePlatform: Categories */
$handler->display->display_options['filters']['media_categories']['id'] = 'media_categories';
$handler->display->display_options['filters']['media_categories']['table'] = 'thePlatform';
$handler->display->display_options['filters']['media_categories']['field'] = 'media_categories';
$handler->display->display_options['filters']['media_categories']['operator'] = 'is';
$handler->display->display_options['filters']['media_categories']['exposed'] = TRUE;
$handler->display->display_options['filters']['media_categories']['expose']['operator_id'] = 'media_categories_op';
$handler->display->display_options['filters']['media_categories']['expose']['label'] = 'Categories';
$handler->display->display_options['filters']['media_categories']['expose']['operator'] = 'media_categories_op';
$handler->display->display_options['filters']['media_categories']['expose']['identifier'] = 'media_categories';
$handler->display->display_options['filters']['media_categories']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  26 => 0,
  31 => 0,
  36 => 0,
  41 => 0,
);
/* Filter criterion: thePlatform: Reference ID */
$handler->display->display_options['filters']['guid']['id'] = 'guid';
$handler->display->display_options['filters']['guid']['table'] = 'thePlatform';
$handler->display->display_options['filters']['guid']['field'] = 'guid';
$handler->display->display_options['filters']['guid']['operator'] = 'is';
$handler->display->display_options['filters']['guid']['exposed'] = TRUE;
$handler->display->display_options['filters']['guid']['expose']['operator_id'] = 'guid_op';
$handler->display->display_options['filters']['guid']['expose']['label'] = 'Reference ID';
$handler->display->display_options['filters']['guid']['expose']['operator'] = 'guid_op';
$handler->display->display_options['filters']['guid']['expose']['identifier'] = 'guid';
$handler->display->display_options['filters']['guid']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  26 => 0,
  31 => 0,
  36 => 0,
  41 => 0,
);
/* Filter criterion: thePlatform: Title */
$handler->display->display_options['filters']['title']['id'] = 'title';
$handler->display->display_options['filters']['title']['table'] = 'thePlatform';
$handler->display->display_options['filters']['title']['field'] = 'title';
$handler->display->display_options['filters']['title']['operator'] = 'starts';
$handler->display->display_options['filters']['title']['exposed'] = TRUE;
$handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
$handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
$handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  26 => 0,
  31 => 0,
  36 => 0,
  41 => 0,
);

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
$handler->display->display_options['path'] = 'pub_theplatform/videos';
