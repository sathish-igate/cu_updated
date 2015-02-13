<?php
/**
 * @file
 * pub_tv.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function pub_tv_taxonomy_default_vocabularies() {
  return array(
    'rating_attributes' => array(
      'name' => 'TV Rating Attributes',
      'machine_name' => 'rating_attributes',
      'description' => 'Rating Attributes for TV Ratings',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'tv_episode_type' => array(
      'name' => 'Episode Type',
      'machine_name' => 'tv_episode_type',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'tv_rating' => array(
      'name' => 'TV Rating',
      'machine_name' => 'tv_rating',
      'description' => 'Television Show Ratings',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
