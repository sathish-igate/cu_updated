<?php
/**
 * @file
 * pub_commerce_example.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function pub_commerce_example_taxonomy_default_vocabularies() {
  return array(
    'color' => array(
      'name' => 'Product Color',
      'machine_name' => 'color',
      'description' => 'Commerce product color',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'size' => array(
      'name' => 'Product Size',
      'machine_name' => 'size',
      'description' => 'Commerce product size',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
