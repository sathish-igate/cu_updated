<?php
/**
 * @file
 * pub_schema_example.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pub_schema_example_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__article';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'locations' => array(
          'weight' => '30',
        ),
        'metatags' => array(
          'weight' => '40',
        ),
        'title' => array(
          'weight' => '-5',
        ),
        'path' => array(
          'weight' => '30',
        ),
        'redirect' => array(
          'weight' => '30',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_article';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_article';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_article';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_article';
  $strongarm->value = '1';
  $export['node_preview_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_article';
  $strongarm->value = 1;
  $export['node_submitted_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'restws_schema_map';
  $strongarm->value = array(
    'show:entity' => 'node',
    'show:bundle' => 'tv_show',
    'show:name' => 'title',
    'show:id' => 'nid',
    'show:description' => 'body',
    'show:genre' => 'field_primary_genre',
    'show:seasons' => '',
    'show:status' => 'status',
    'season:entity' => 'node',
    'season:bundle' => 'tv_season',
    'season:name' => 'title',
    'season:id' => 'nid',
    'season:description' => 'body',
    'season:show' => 'field_tv_shows',
    'season:episodes' => '',
    'season:status' => 'status',
    'episode:entity' => 'node',
    'episode:bundle' => 'tv_episode',
    'episode:name' => 'title',
    'episode:id' => 'nid',
    'episode:description' => 'body',
    'episode:show' => 'field_tv_shows',
    'episode:season' => 'field_tv_shows',
    'episode:status' => 'status',
    'blog:entity' => 'node',
    'blog:bundle' => 'article',
    'blog:name' => 'title',
    'blog:id' => 'nid',
    'blog:description' => 'body',
    'blog:show' => 'field_tv_shows',
    'blog:season' => 'field_tv_shows',
    'blog:episode' => 'field_tv_shows',
    'blog:status' => 'status',
    'gallery:entity' => 'node',
    'gallery:bundle' => 'media_gallery',
    'gallery:name' => 'title',
    'gallery:id' => 'nid',
    'gallery:description' => 'body',
    'gallery:photos' => 'field_media_items',
    'gallery:show' => '',
    'gallery:season' => '',
    'gallery:episode' => '',
    'gallery:status' => 'status',
  );
  $export['restws_schema_map'] = $strongarm;

  return $export;
}
