<?php
/**
 * @file
 * pub_media.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function pub_media_taxonomy_default_vocabularies() {
  return array(
    'media_categories' => array(
      'name' => 'Media Categories',
      'machine_name' => 'media_categories',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'media_tags' => array(
      'name' => 'Media Tags',
      'machine_name' => 'media_tags',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
