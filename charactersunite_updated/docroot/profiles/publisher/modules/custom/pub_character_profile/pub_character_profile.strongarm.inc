<?php
/**
 * @file
 * pub_character_profile.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pub_character_profile_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_character_profile';
  $strongarm->value = '1';
  $export['ant_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_pattern_character_profile';
  $strongarm->value = '<?php
  $lang = $node->language;
  $title = \'\';
  if (!empty($node->field_character_prefix[$lang][0][\'value\'])) { $title .= $node->field_character_prefix[$lang][0][\'value\'] . \' \'; }
  if (!empty($node->field_character_first_name[$lang][0][\'value\'])) { $title .= $node->field_character_first_name[$lang][0][\'value\'] . \' \'; }
  if (!empty($node->field_character_middle_name[$lang][0][\'value\'])) { $title .= $node->field_character_middle_name[$lang][0][\'value\'] . \' \'; }
  if (!empty($node->field_character_last_name[$lang][0][\'value\'])) { $title .= $node->field_character_last_name[$lang][0][\'value\'] . \' \'; }
  if (!empty($node->field_character_suffix[$lang][0][\'value\'])) { $title .= $node->field_character_suffix[$lang][0][\'value\'] . \' \'; }
  return trim($title);
?>';
  $export['ant_pattern_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_php_character_profile';
  $strongarm->value = 1;
  $export['ant_php_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_character_profile';
  $strongarm->value = 0;
  $export['comment_anonymous_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_character_profile';
  $strongarm->value = '2';
  $export['comment_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_character_profile';
  $strongarm->value = 1;
  $export['comment_default_mode_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_character_profile';
  $strongarm->value = '50';
  $export['comment_default_per_page_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_character_profile';
  $strongarm->value = 1;
  $export['comment_form_location_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_character_profile';
  $strongarm->value = '1';
  $export['comment_preview_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_character_profile';
  $strongarm->value = 1;
  $export['comment_subject_field_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__character_profile';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'print' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'portable_gallery' => array(
        'custom_settings' => FALSE,
      ),
      'user_ref_preview' => array(
        'custom_settings' => FALSE,
      ),
      'admin_reference_preview' => array(
        'custom_settings' => FALSE,
      ),
      'promoted_content' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'metatags' => array(
          'weight' => '5',
        ),
        'title' => array(
          'weight' => '2',
        ),
        'path' => array(
          'weight' => '3',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_character_profile';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_character_profile';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_character_profile';
  $strongarm->value = array(
    0 => 'revision',
  );
  $export['node_options_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_character_profile';
  $strongarm->value = '1';
  $export['node_preview_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_character_profile';
  $strongarm->value = 1;
  $export['node_submitted_character_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'representative_image_field_node_character_profile';
  $strongarm->value = 'field_character_cover_photo';
  $export['representative_image_field_node_character_profile'] = $strongarm;

  return $export;
}
