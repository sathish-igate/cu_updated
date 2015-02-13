<?php
/**
 * @file
 * pub_blog_post.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function pub_blog_post_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:blog_post.
  $config['node:blog_post'] = array(
    'instance' => 'node:blog_post',
    'config' => array(
      'og:image' => array(
        'value' => '[node:field_cover_media]',
      ),
    ),
  );

  return $config;
}
