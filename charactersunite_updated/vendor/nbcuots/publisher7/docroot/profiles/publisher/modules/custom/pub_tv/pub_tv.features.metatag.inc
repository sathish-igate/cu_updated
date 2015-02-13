<?php
/**
 * @file
 * pub_tv.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function pub_tv_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:tv_episode.
  $config['node:tv_episode'] = array(
    'instance' => 'node:tv_episode',
    'config' => array(
      'description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:image' => array(
        'value' => '[node:field_tv_cover_media]',
      ),
      'twitter:image' => array(
        'value' => '[node:field_tv_cover_media]',
      ),
    ),
  );

  // Exported Metatag config instance: node:tv_season.
  $config['node:tv_season'] = array(
    'instance' => 'node:tv_season',
    'config' => array(
      'description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:image' => array(
        'value' => '[node:field_tv_cover_media]',
      ),
      'twitter:image' => array(
        'value' => '[node:field_tv_cover_media]',
      ),
    ),
  );

  // Exported Metatag config instance: node:tv_show.
  $config['node:tv_show'] = array(
    'instance' => 'node:tv_show',
    'config' => array(
      'description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:image' => array(
        'value' => '[node:field_tv_cover_media]',
      ),
      'twitter:image' => array(
        'value' => '[node:field_tv_cover_media]',
      ),
    ),
  );

  return $config;
}
