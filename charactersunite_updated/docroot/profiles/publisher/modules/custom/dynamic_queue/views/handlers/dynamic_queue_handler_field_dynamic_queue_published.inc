<?php

/**
 * @file
 * Definition of dynamic_queue_handler_field_dynamic_queue_published.
 */

/**
 * Class dynamic_queue_handler_field_dynamic_queue_published.
 *
 * A handler to display Published state as strings instead of integers.
 *
 * @ingroup views_field_handlers
 */
class dynamic_queue_handler_field_dynamic_queue_published extends views_handler_field {

  public function get_value($values, $field = NULL) {
    if (isset($values->{$field})) {
      return $values->{$field};
    }
  }

  public function render($values) {
    $status = $this->get_value($values, $this->field_alias);
    if ($status == 1) {
      $output = t('Published');
    }
    else {
      $output = t('Unpublished');
    }

    return $output;
  }

  public function click_sort($order) {
    if (strtolower($order) === 'desc') {
      $this->query->add_orderby(NULL, NULL, 'asc', $this->field_alias);
    }
    else {
      $this->query->add_orderby(NULL, NULL, 'desc', $this->field_alias);
    }
  }
}
