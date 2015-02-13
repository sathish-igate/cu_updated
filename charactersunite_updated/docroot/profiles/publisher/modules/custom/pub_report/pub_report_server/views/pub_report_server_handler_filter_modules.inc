<?php

/**
 * @file
 * Class pub_report_server_handler_filter_modules
 */

class pub_report_server_handler_filter_modules extends views_handler_filter_string {
  /**
   * Add this filter to the query.
   *
   * Due to the nature of fapi, the value and the operator have an unintended
   * level of indirection. You will find them in $this->operator
   * and $this->value respectively.
   */
  function query() {
    // Wrapping the value before query execution to ensure that it works
    // correctly with module names that contain other module names.
    $this->value = '(' . trim($this->value) . ')';

    $this->ensure_my_table();
    $field = "$this->table_alias.$this->real_field";

    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}($field);
    }
  }
}
