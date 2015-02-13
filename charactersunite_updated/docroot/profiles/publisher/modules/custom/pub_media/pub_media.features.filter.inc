<?php
/**
 * @file
 * pub_media.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function pub_media_filter_default_formats() {
  $formats = array();

  // Exported format: WYSIWYG Mini.
  $formats['wysiwyg_mini'] = array(
    'format' => 'wysiwyg_mini',
    'name' => 'WYSIWYG Mini',
    'cache' => 1,
    'status' => 1,
    'weight' => -10,
    'filters' => array(
      'filter_html' => array(
        'weight' => -50,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<p> <a> <em> <strong> <strike> <cite> <code> <ul> <ol> <li> <dl> <dt> <dd> <img> <table> <tbody> <tr> <td> <th> <tbody> <caption> <thead> <tfoot> <h1> <h2> <h3> <h4> <h5> <h6> <blockquote> <hr> <span> <br> <sup> <sub> <div> <article> <aside>',
          'filter_html_help' => 0,
          'filter_html_nofollow' => 1,
        ),
      ),
      'media_filter' => array(
        'weight' => -46,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_url' => array(
        'weight' => -45,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'filter_htmlcorrector' => array(
        'weight' => -44,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
