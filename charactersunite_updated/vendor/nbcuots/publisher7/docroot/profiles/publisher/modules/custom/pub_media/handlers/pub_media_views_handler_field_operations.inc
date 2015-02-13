<?php

/**
 * @file
 * Definition of pub_editorial_views_handler_field_operations.
 */

/**
 * A handler to provide proper displays for the representative image.
 *
 * @ingroup views_field_handlers
 */
class pub_media_views_handler_field_operations extends views_handler_field {

  function query() {
    // Do nothing -- to override the parent query.
  }

  function render($values) {
    $nid = $values->nid;
    $node = node_load($nid);

    $links = array();
    if (node_access('update', $node)) {
      $links[] = array(
        'title' => t('Edit'),
        'href' => 'node/' . $nid .'/edit',
      );
    }
    if (node_access('delete', $node)) {
      $links[] = array(
        'title' => t('Delete'),
        'href' => 'node/' . $nid .'/delete',
      );
    }

    $output = '';
    if (!empty($links)) {
      $output = theme('links__ctools_dropbutton', array('title' => t('operations'), 'links' => $links));
    }

    // Include the Ctools Dropbutton CSS from Views.
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.css');
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.ctools.css');
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.seven.css');
    drupal_add_css(drupal_get_path('module', 'pub_editorial') . '/css/pub_editorial.css', array('weight' => 100));

    return $output;
  }
}
