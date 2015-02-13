<?php
/**
 * @file
 * pub_wysiwyg.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function pub_wysiwyg_filter_default_formats() {
  $formats = array();

  // Exported format: Publisher.
  $formats['publisher'] = array(
    'format' => 'publisher',
    'name' => 'Publisher',
    'cache' => 0,
    'status' => 1,
    'weight' => -10,
    'filters' => array(
      'filter_html' => array(
        'weight' => -10,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<a> <em> <strong> <youtube> <div> <p> <br><mpx>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ),
      ),
      'filter_autop' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'pub_wysiwyg_mpx' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'pub_wysiwyg_youtube' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_htmlcorrector' => array(
        'weight' => 10,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
