<?php
/**
 * @file
 * pub_character_profile.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function pub_character_profile_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:character_profile.
  $config['node:character_profile'] = array(
    'instance' => 'node:character_profile',
    'config' => array(
      'description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:description' => array(
        'value' => '[node:field_summary]',
      ),
      'og:image' => array(
        'value' => '[node:field_character_cover_photo]',
      ),
      'twitter:image' => array(
        'value' => '[node:field_character_cover_photo]',
      ),
    ),
  );

  return $config;
}
