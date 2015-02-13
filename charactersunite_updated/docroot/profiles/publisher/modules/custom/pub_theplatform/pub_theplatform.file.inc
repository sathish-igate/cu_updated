<?php
/**
 * @file
 * File specific functionality.
 */

/**
 * Implements hook_file_formatter_info().
 */
function pub_theplatform_file_formatter_info() {
  $formatters['theplatform_iframe'] = array(
    'label' => t('thePlatform Video in a player services Embed Player'),
    'file types' => array('video'),
    'default settings' => array(),
    'view callback' => 'pub_theplatform_file_formatter_video_view',
  );

  $formatters['theplatform_image'] = array(
    'label' => t('thePlatform Preview Image'),
    'file types' => array('video'),
    'default settings' => array(
      'image_style' => '',
    ),
    'view callback' => 'pub_theplatform_file_formatter_image_view',
    'settings callback' => 'pub_theplatform_file_formatter_image_settings',
  );

  return $formatters;
}


/**
 * Define the view callback for the file formatter.
 */
function pub_theplatform_file_formatter_video_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);

  if ($scheme == 'theplatform') {
    $guid = file_uri_target($file->uri);
    $platform_file_id = _pub_the_platform_get_file_id($guid);

    // Collapse this area if there is no video.
    if ($platform_file_id === FALSE) {
      return array();
    }

    $element = array(
      '#theme' => 'pub_theplatform_video_player',
      '#platform_file_id' => $platform_file_id,
      '#theplatform_player' => variable_get('theplatform_player_url', ''),
    );
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function pub_theplatform_file_formatter_image_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  if ($scheme == 'theplatform') {
    $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
    $image_style = $display['settings']['image_style'];
    $valid_image_styles = image_style_options(FALSE);
    if (empty($image_style) || !isset($valid_image_styles[$image_style])) {
      $element = array(
        '#theme' => 'image',
        '#path' => $wrapper->getOriginalThumbnailPath(),
        '#alt' => isset($file->override['attributes']['alt']) ? $file->override['attributes']['alt'] : $file->filename,
      );
    }
    else {
      $element = array(
        '#theme' => 'image_style',
        '#style_name' => $image_style,
        '#path' => $wrapper->getLocalThumbnailPath(),
        '#alt' => isset($file->override['attributes']['alt']) ? $file->override['attributes']['alt'] : $file->filename,
      );
    }

    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function pub_theplatform_file_formatter_image_settings($form, &$form_state, $settings) {
  $element = array();
  $element['image_style'] = array(
    '#title' => t('Image style'),
    '#type' => 'select',
    '#options' => image_style_options(FALSE),
    '#default_value' => $settings['image_style'],
    '#empty_option' => t('None (original image)'),
  );
  return $element;
}
