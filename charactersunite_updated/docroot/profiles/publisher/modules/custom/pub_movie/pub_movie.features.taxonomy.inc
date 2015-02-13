<?php
/**
 * @file
 * pub_movie.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function pub_movie_taxonomy_default_vocabularies() {
  return array(
    'movie_rating' => array(
      'name' => 'Movie Rating',
      'machine_name' => 'movie_rating',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'movie_types' => array(
      'name' => 'Movie Types',
      'machine_name' => 'movie_types',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
