<?php
/**
 * @file
 * feature_pub_mpx_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function feature_pub_mpx_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'pub_mpx_video_media_browser';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'file_managed';
  $view->human_name = 'Publisher7 MPX Video Media Browser';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Media Browser:  Pub MPX Videos';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['total_pages'] = '5';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: File: File ID */
  $handler->display->display_options['fields']['fid']['id'] = 'fid';
  $handler->display->display_options['fields']['fid']['table'] = 'file_managed';
  $handler->display->display_options['fields']['fid']['field'] = 'fid';
  $handler->display->display_options['fields']['fid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['fid']['alter']['text'] = '{"fid":"[fid]"}';
  /* Field: thePlatform MPX Video: thePlatform MPX Video Reference ID */
  $handler->display->display_options['fields']['guid']['id'] = 'guid';
  $handler->display->display_options['fields']['guid']['table'] = 'mpx_video';
  $handler->display->display_options['fields']['guid']['field'] = 'guid';
  $handler->display->display_options['fields']['guid']['label'] = 'Reference ID';
  $handler->display->display_options['fields']['guid']['element_label_colon'] = FALSE;
  /* Field: thePlatform MPX Video: thePlatform MPX Video Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mpx_video';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Title';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: thePlatform MPX Video: thePlatform MPX Video Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'mpx_video';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = 'Description';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  /* Field: thePlatform MPX Video: thePlatform MPX Video Thumbnail */
  $handler->display->display_options['fields']['thumbnail_url']['id'] = 'thumbnail_url';
  $handler->display->display_options['fields']['thumbnail_url']['table'] = 'mpx_video';
  $handler->display->display_options['fields']['thumbnail_url']['field'] = 'thumbnail_url';
  $handler->display->display_options['fields']['thumbnail_url']['label'] = '';
  $handler->display->display_options['fields']['thumbnail_url']['element_label_colon'] = FALSE;
  /* Sort criterion: File: Upload date */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'file_managed';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Filter criterion: File: Mime type */
  $handler->display->display_options['filters']['filemime']['id'] = 'filemime';
  $handler->display->display_options['filters']['filemime']['table'] = 'file_managed';
  $handler->display->display_options['filters']['filemime']['field'] = 'filemime';
  $handler->display->display_options['filters']['filemime']['value'] = 'video/mpx';
  $handler->display->display_options['filters']['filemime']['group'] = 1;
  /* Filter criterion: thePlatform MPX Video: thePlatform MPX Video ID */
  $handler->display->display_options['filters']['id']['id'] = 'id';
  $handler->display->display_options['filters']['id']['table'] = 'mpx_video';
  $handler->display->display_options['filters']['id']['field'] = 'id';
  $handler->display->display_options['filters']['id']['operator'] = '>';
  $handler->display->display_options['filters']['id']['value']['value'] = '0';
  $handler->display->display_options['filters']['id']['group'] = 1;
  /* Filter criterion: thePlatform MPX Video: thePlatform MPX Video Reference ID */
  $handler->display->display_options['filters']['guid']['id'] = 'guid';
  $handler->display->display_options['filters']['guid']['table'] = 'mpx_video';
  $handler->display->display_options['filters']['guid']['field'] = 'guid';
  $handler->display->display_options['filters']['guid']['group'] = 1;
  $handler->display->display_options['filters']['guid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['guid']['expose']['operator_id'] = 'guid_op';
  $handler->display->display_options['filters']['guid']['expose']['label'] = 'Reference ID';
  $handler->display->display_options['filters']['guid']['expose']['operator'] = 'guid_op';
  $handler->display->display_options['filters']['guid']['expose']['identifier'] = 'guid';
  $handler->display->display_options['filters']['guid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
  );
  /* Filter criterion: thePlatform MPX Video: thePlatform MPX Video Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'mpx_video';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
  );
  /* Filter criterion: thePlatform MPX Video: thePlatform MPX Categories */
  $handler->display->display_options['filters']['categories']['id'] = 'categories';
  $handler->display->display_options['filters']['categories']['table'] = 'mpx_video';
  $handler->display->display_options['filters']['categories']['field'] = 'categories';
  $handler->display->display_options['filters']['categories']['exposed'] = TRUE;
  $handler->display->display_options['filters']['categories']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['categories']['expose']['label'] = 'Categories';
  $handler->display->display_options['filters']['categories']['expose']['operator'] = 'categories_op';
  $handler->display->display_options['filters']['categories']['expose']['identifier'] = 'categories';
  $handler->display->display_options['filters']['categories']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'pub-mpx/video-media-browser';
  $export['pub_mpx_video_media_browser'] = $view;

  return $export;
}
