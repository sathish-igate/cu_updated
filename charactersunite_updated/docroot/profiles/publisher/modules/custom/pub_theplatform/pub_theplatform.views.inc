<?php

/**
 * @file
 * Standard views.inc for pub_theplatform.
 */

/**
 * Implements hook_views_default_views().
 */
function pub_theplatform_views_default_views() {
  // We use the same media module function, since we depend on that heavily.
  // Otherwise we could roll our own.
  return media_load_all_exports('pub_theplatform', 'views', 'view.inc', 'view');
}

/**
 * Implements hook_views_data().
 *
 * Note, that for items you'd like to add that should be media$, they're media_
 * because of how Views does object access. Ditto for the plmedia$ items.
 * Thank you XML translations....
 */
function pub_theplatform_views_data() {
  $data = array();

  // Base table definition.
  $data['thePlatform']['table'] = array(
    'group' => t('thePlatform'),
    'base' => array(
      'title' => t('thePlatform Videos'),
      'help' => t('Videos from thePlatform'),
      'query class' => 'theplatform_query',
    ),
  );

  // Reference ID.
  $data['thePlatform']['guid'] = array(
    'title' => t('Reference ID'),
    'help' => t('Reference ID in thePlatform.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'pub_theplatform_views_handler_filter_guid',
    ),
    'sort' => array(
      'handler' => 'pub_theplatform_views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'pub_theplatform_views_handler_argument_guid',
    ),
  );

  // Title.
  $data['thePlatform']['title'] = array(
    'title' => t('Title'),
    'help' => t('Title of the video in thePlatform.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'pub_theplatform_views_handler_filter_title',
    ),
    'sort' => array(
      'handler' => 'pub_theplatform_views_handler_sort',
    ),
  );

  // Description.
  $data['thePlatform']['description'] = array(
    'title' => t('Description'),
    'help' => t('Description of the video in thePlatform.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );

  // Short Description.
  $data['thePlatform']['pl1_shortDescription'] = array(
    'title' => t('Short Description'),
    'help' => t('Short description of the video in thePlatform.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'pub_theplatform_views_handler_sort_short_description',
    ),
  );

  // Categories.
  $data['thePlatform']['media_categories'] = array(
    'title' => t('Categories'),
    'help' => t('thePlatform categories that apply to this video.'),
    'field' => array(
      'handler' => 'pub_theplatform_views_handler_field_category',
    ),
    'filter' => array(
      'handler' => 'pub_theplatform_views_handler_filter_category',
    ),
    'argument' => array(
      'handler' => 'pub_theplatform_views_handler_argument_category',
    ),
  );

  // Thumbnails.
  $data['thePlatform']['plmedia_defaultThumbnailUrl'] = array(
    'title' => t('Thumbnail'),
    'help' => t('thePlatform default thumbnail for this video.'),
    'field' => array(
      'handler' => 'pub_theplatform_views_handler_field_thumb',
    ),
  );

  // Runtime.
  $data['thePlatform']['custom_runtime'] = array(
    'title' => t('Runtime'),
    'help' => t('Runtime of the clip in seconds.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );

  // PubDate.
  $data['thePlatform']['pubDate'] = array(
    'title' => t('pubDate'),
    'help' => t('The publication date from the feed.'),
    'field' => array(
      'handler' => 'pub_theplatform_views_handler_field_pubdate',
    ),
    'sort' => array(
      'handler' => 'pub_theplatform_views_handler_sort_pubdate',
    ),
  );

  // FullEpisode.
  $data['thePlatform']['pl1_fullEpisode'] = array(
    'title' => t('Full Episode'),
    'help' => t('The full episode flag.'),
    'argument' => array(
      'handler' => 'pub_theplatform_views_handler_argument_customvalue',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_plugins().
 */
function pub_theplatform_views_plugins() {
  $plugins = array(
    'query' => array(
      'theplatform_query' => array(
        'title' => t('thePlatformAPIRequest'),
        'help' => t('Uses thePlatformAPIRequest for querying information about thePlatform videos.'),
        'handler' => 'pub_theplatform_views_plugin_query',
      ),
    ),
  );

  return $plugins;
}
