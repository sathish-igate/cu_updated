<?php

/**
 * @file
 * Provide views data and handlers for pub_mpx.module.
 */

/**
 * Implements hook_views_data().
 */
function pub_mpx_views_data() {

  $data = array();

  $data['mpx_player']['table']['group'] = t('thePlatform MPX Player');
  $data['mpx_player']['table']['base'] = array(
    'field' => 'player_id',
    'title' => t('thePlatform MPX Player'),
  );
  $data['mpx_player']['table']['join']['file_managed'] = array(
    'left_field' => 'fid',
    'field' => 'fid',
  );

  $data['mpx_video']['table']['group'] = t('thePlatform MPX Video');
  $data['mpx_video']['table']['join']['file_managed'] = array(
    'left_field' => 'fid',
    'field' => 'fid',
  );

  // Make metadata fields available.
  // MPX Player.
  $data['mpx_player']['title'] = array(
    'title' => t('thePlatform MPX Player Title'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mpx_player']['description'] = array(
    'title' => t('thePlatform MPX Player Description'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );

  $data['mpx_player']['id'] = array(
    'title' => t('thePlatform MPX Player ID'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  
  $data['mpx_player']['pid'] = array(
    'title' => t('thePlatform MPX Player Public ID'),
    'help' => t('The Public ID as defined in MPX.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mpx_player']['status'] = array(
    'title' => t('thePlatform MPX Player Status'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
      'output formats' => array(
        'published-notpublished' => array(t('Enabled'), t('Disabled')),
      ),
    ),
    'filter' => array(
      'handler' => 'pub_mpx_handler_filter_player_status',
      'label' => t('MPX Status')
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['mpx_player']['account'] = array(
    'title' => t('thePlatform MPX Player Account'),
    'help' => t('The MPX account associated with the player.'),
    'field' => array(
      'handler' => 'pub_mpx_handler_field_player_account',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'pub_mpx_handler_filter_player_account',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mpx_player']['created'] = array(
    'title' => t('thePlatform MPX Player Created (First Imported) Date'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['mpx_player']['updated'] = array(
    'title' => t('thePlatform MPX Player Updated (Last Updated) Date'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );


  // MPX Video.
  $data['mpx_video']['title'] = array(
    'title' => t('thePlatform MPX Video Title'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mpx_video']['description'] = array(
    'title' => t('thePlatform MPX Video Description'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
  );

  $data['mpx_video']['id'] = array(
    'title' => t('thePlatform MPX Video ID'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['mpx_video']['guid'] = array(
    'title' => t('thePlatform MPX Video Reference ID'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mpx_video']['thumbnail_url'] = array(
    'title' => t('thePlatform MPX Video Thumbnail'),
    'field' => array(
      'handler' => 'pub_mpx_views_handler_field_mpx_video_thumbnail_url',
      'click sortable' => TRUE,
    ),
  );

  $data['mpx_video']['airdate'] = array(
    'title' => t('Air Date'),
    'help' => t('thePlatform MPX Video Air Date field.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['mpx_video']['available_date'] = array(
    'title' => t('thePlatform MPX Video Available Date (Sunrise)'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['mpx_video']['expiration_date'] = array(
    'title' => t('thePlatform MPX Video Expiration Date (Sunset)'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['mpx_video']['updated'] = array(
    'title' => t('thePlatform MPX Video Updated Date'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['mpx_video']['status'] = array(
    'title' => t('thePlatform MPX Video Status'),
    'help' => t('The MPX status may be Published, Unpublished or Expired.'),
    'field' => array(
      'handler' => 'pub_mpx_handler_field_status',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'pub_mpx_handler_filter_status',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mpx_video']['account'] = array(
    'title' => t('thePlatform MPX Account'),
    'help' => t('The MPX account associated with the video.'),
    'field' => array(
      'handler' => 'pub_mpx_handler_field_account',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'pub_mpx_handler_filter_account',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mpx_video']['categories'] = array(
    'title' => t('thePlatform MPX Categories'),
    'help' => t('The MPX categories associated with the video.'),
    /* @todo
    'field' => array(
      'handler' => 'pub_mpx_handler_field_category',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    //*/
    'filter' => array(
      'handler' => 'pub_mpx_handler_filter_categories',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function pub_mpx_views_data_alter(&$data) {
  if (isset($data['revision_scheduler']['actions']['field']['handler'])) {
    $data['revision_scheduler']['actions']['field']['handler'] = 'pub_mpx_revision_scheduler_handler_field_actions';
  }
}

/**
 * Implements hook_views_query_alter().
 */
function pub_mpx_views_query_alter(&$view, &$query) {
  if ($view->name === 'content_files') {
    if ($view->current_display === 'mpx_players_page') {
      $query->add_where(0,'mpx_player.player_id', NULL, 'IS NOT NULL');
    }
    elseif ($view->current_display === 'mpx_files_page') {
      $query->add_where(0,'mpx_video.video_id', NULL, 'IS NOT NULL');
    }
  }
}

/**
 * Implements hook_views_pre_render().
 */
function pub_mpx_views_pre_render(&$view) {

  if ($view->name === 'content_files') {
    drupal_add_css(drupal_get_path('module', 'pub_mpx') . '/css/pub_mpx.css');

    if ($view->current_display === 'mpx_players_page') {
      $form_sync = drupal_get_form('media_theplatform_mpx_form_mpx_player_sync');
    }
    else {
      $form_sync = drupal_get_form('media_theplatform_mpx_form_mpx_video_sync');
    }

    $output = render($form_sync);
    $view->attachment_before = $output;
  }

  // Sometimes an operation is manually run when MPX value overrides are
  // overridden. This is indicated in the view with '**'. We display some text
  // telling the user what this means at the top of the view.
  if ($view->name === 'pub_workbench_scheduled_videos') {
    $view->attachment_before = '** indicates MPX value overridden';
  }
}
