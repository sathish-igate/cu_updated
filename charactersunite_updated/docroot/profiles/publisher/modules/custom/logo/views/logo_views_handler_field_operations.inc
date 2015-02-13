<?php

/**
 * @file
 * Definition of logo_views_handler_field_operations.
 */

/**
 * A handler to provide operations links for the Logo entity type.
 *
 * @ingroup views_field_handlers
 */
class logo_views_handler_field_operations extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function query() {
    // Do nothing -- to override the parent query.
  }

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    $output = '';

    $type = 'logo';
    $value = $values->lid;

    $links[] = array(
      'title' => t('Edit'),
      'href' => $type . '/edit/' . $value ,
    );
    $links[] = array(
      'title' => t('Delete'),
      'href' => $type . '/delete/' . $value,
    );

    if (!empty($links)) {
      $output = theme('links__ctools_dropbutton', array('title' => t('operations'), 'links' => $links));
    }

    $this->logoCSS();

    return $output;
  }

  /**
   * Add any CSS necessary.
   */
  private function logoCSS() {
    // Include the Ctools Dropbutton CSS from Views.
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.css');
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.ctools.css');
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.seven.css');
    drupal_add_css(drupal_get_path('module', 'logo') . '/css/logo.css', array('weight' => 100));
  }
}
