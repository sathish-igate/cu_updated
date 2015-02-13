<?php
/**
 * @file
 * pub_movie.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function pub_movie_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:movie.
  $config['node:movie'] = array(
    'instance' => 'node:movie',
    'config' => array(
      'description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:image' => array(
        'value' => '[node:field_movie_cover_media]',
      ),
      'twitter:image' => array(
        'value' => '[node:field_movie_cover_media]',
      ),
    ),
  );

  return $config;
}
