<?php
/**
 * @file
 * pub_post.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function pub_post_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:post.
  $config['node:post'] = array(
    'instance' => 'node:post',
    'config' => array(
      'description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:image' => array(
        'value' => '[node:field_cover_media]',
      ),
      'twitter:image' => array(
        'value' => '[node:field_cover_media]',
      ),
    ),
  );

  return $config;
}
