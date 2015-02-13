<?php

/**
 * @file
 * Provides action links for Views.
 */

/**
 * A handler to provide the time the operation is scheduled or was executed.
 *
 * This is essentially a handler for a fake field, we bring in values from other
 * fields to output data from either one of those fields based on conditions.
 *
 * @ingroup views_field_handlers
 */
class revision_scheduler_handler_field_scheduled_executed_time extends views_handler_field_date {
  /**
   * Declare fields that we want to bring in data from.
   */
  public function construct() {
    parent::construct();
    $this->additional_fields['time_scheduled'] = 'time_scheduled';
    $this->additional_fields['time_executed'] = 'time_executed';
  }

  /**
   * Override the parent::query() to allow the fake field to work.
   *
   * Also execute the addition of our additional fields so it is available to
   * $this.
   */
  public function query() {
    $this->add_additional_fields();
  }

  /**
   * Render the field.
   *
   * Not sure if we should be using more of the parent::render but the this
   * works for now.
   */
  public function render($values) {
    $timezone = !empty($this->options['timezone']) ? $this->options['timezone'] : NULL;
    $format = $this->options['date_format'];
    $timeExecuted = $values->time_executed;
    $timeScheduled = $values->time_scheduled;
    $completed = $timeExecuted;

    if ($completed) {
      return format_date($timeExecuted, $format, '', $timezone) . '**';
    }
    else {
      return format_date($timeScheduled, $format, '', $timezone);
    }
  }
}
