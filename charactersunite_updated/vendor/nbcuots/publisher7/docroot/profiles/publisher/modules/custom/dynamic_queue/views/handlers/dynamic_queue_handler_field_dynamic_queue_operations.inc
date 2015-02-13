<?php

/**
 * @file
 * Definition of dynamic_queue_handler_field_dynamic_queue_operations.
 */

/**
 * Class dynamic_queue_handler_field_dynamic_queue_operations.
 *
 * A handler to display Operations links as a dropdown.
 *
 * @ingroup views_field_handlers
 */
class dynamic_queue_handler_field_dynamic_queue_operations extends views_handler_field {

  public function query() {
    // Do nothing -- to override the parent query.
  }

  public function get_value($values, $field = NULL) {
    if (isset($values->{$field})) {
      return $values->{$field};
    }
  }

  public function render($values) {
    $output = '';
    $links = array();
    if (empty($this->relationship)) {
      $dqid = $this->get_value($values, 'dqid');
      $dynamic_queue = queue_load($dqid);

      if (dynamic_queue_access('edit', $dynamic_queue)) {
        $links[] = array(
          'title' => t('Edit'),
          'href' => 'dynamic-queue/' . $dqid . '/edit',
          'query' => drupal_get_destination(),
        );
      }
      if (dynamic_queue_access('delete', $dynamic_queue)) {
        $links[] = array(
          'title' => t('Delete'),
          'href' => 'dynamic-queue/' . $dqid . '/delete',
          'query' => drupal_get_destination(),
        );
      }

      $output = theme('links__ctools_dropbutton', array('title' => t('Operations'), 'links' => $links));
    }

    $this->add_ctools_css();

    return $output;
  }

  public function add_ctools_css() {
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.css');
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.ctools.css');
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.seven.css');
    drupal_add_css(drupal_get_path('module', 'dynamic_queue') . '/css/dynamic_queue.css');
  }

}
