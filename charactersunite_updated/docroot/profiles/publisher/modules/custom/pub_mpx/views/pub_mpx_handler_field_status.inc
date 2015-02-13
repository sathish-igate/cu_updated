<?php

/**
 * @file pub_mpx_handler_field_status.inc
 */

/**
 * Handler for converting the MPX status and MPX expiration_date to a field we
 * can display and sort.
 */
class pub_mpx_handler_field_status extends views_handler_field {

  function render($values) {
    $status = $this->case_transform($this->get_value($values), 'ucwords');
    return t($status);
  }

  function get_value($values, $field = NULL) {
    $value = '';
    $unix_time = time();

    // If the expiration_date is 0, we're to use the MPX status.  Otherwise,
    // if the expiration_date is less than equal to the current time, consider
    // the status to be expired.
    if (!empty($values->mpx_video_expiration_date) && $values->mpx_video_expiration_date <= $unix_time) {
      $value = 'expired';
    }
    else {
      $value = $values->mpx_video_status ? 'published' : 'unpublished';
    }
    return $value;
  }

  function click_sort($order) {
    $unix_time = time();
    //expiration_date = 0 or
    $expression = 'if(expiration_date > ' . $unix_time . ', 1, 0)';
    $this->query->add_field(NULL, $expression, 'expiration_state');

    if (strtolower($order) === 'asc') {
      $this->query->add_orderby(NULL, NULL, 'asc', 'expiration_state');
      $this->query->add_orderby(NULL, NULL, 'desc', 'mpx_video.status');
    }
    else {
      $this->query->add_orderby(NULL, NULL, 'desc', 'expiration_state');
      $this->query->add_orderby(NULL, NULL, 'asc', 'mpx_video.status');
    }
  }
}
