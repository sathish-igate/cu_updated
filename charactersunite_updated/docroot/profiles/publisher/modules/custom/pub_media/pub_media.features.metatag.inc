<?php
/**
 * @file
 * pub_media.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function pub_media_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:media_gallery.
  $config['node:media_gallery'] = array(
    'instance' => 'node:media_gallery',
    'config' => array(
      'description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:image' => array(
        'value' => '[node:field_cover_item]',
      ),
      'twitter:image' => array(
        'value' => '[node:field_cover_item]',
      ),
    ),
  );

  return $config;
}
