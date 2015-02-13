<?php
/**
 * @file
 * pub_contributor_profile.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function pub_contributor_profile_taxonomy_default_vocabularies() {
  return array(
    'people_tags' => array(
      'name' => 'People Tags',
      'machine_name' => 'people_tags',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
  );
}
