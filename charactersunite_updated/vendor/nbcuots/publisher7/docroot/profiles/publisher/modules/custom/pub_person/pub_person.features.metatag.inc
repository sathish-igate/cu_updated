<?php
/**
 * @file
 * pub_person.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function pub_person_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:person.
  $config['node:person'] = array(
    'instance' => 'node:person',
    'config' => array(
      'description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:image' => array(
        'value' => '[node:field_person_cover_photo]',
      ),
      'twitter:image' => array(
        'value' => '[node:field_person_cover_photo]',
      ),
    ),
  );

  return $config;
}
