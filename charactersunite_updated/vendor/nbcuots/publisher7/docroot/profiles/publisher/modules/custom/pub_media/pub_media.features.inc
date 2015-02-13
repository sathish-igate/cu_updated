<?php
/**
 * @file
 * pub_media.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pub_media_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function pub_media_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function pub_media_image_default_styles() {
  $styles = array();

  // Exported image style: pub_media_thumbnail.
  $styles['pub_media_thumbnail'] = array(
    'effects' => array(
      0 => array(
        'label' => 'Focus Scale And Crop',
        'help' => 'Scale and crop based on data provided by <em>ImageField Focus</em>.',
        'effect callback' => 'imagefield_focus_scale_and_crop_effect',
        'form callback' => 'imagefield_focus_scale_and_crop_form',
        'summary theme' => 'imagefield_focus_scale_and_crop_summary',
        'module' => 'imagefield_focus',
        'name' => 'imagefield_focus_scale_and_crop',
        'data' => array(
          'width' => 336,
          'height' => 198,
          'upscale' => 0,
          'strength' => 'medium',
        ),
        'weight' => 0,
      ),
    ),
    'name' => 'pub_media_thumbnail',
    'label' => 'pub_media_thumbnail',
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function pub_media_node_info() {
  $items = array(
    'media_gallery' => array(
      'name' => t('Media Gallery'),
      'base' => 'node_content',
      'description' => t('Create and manage a gallery of media.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
