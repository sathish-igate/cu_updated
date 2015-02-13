<?php

/**
 * @file
 * Provides action links for Views.
 */
class revision_scheduler_handler_field_actions extends views_handler_field {
  function render($values) {
    if (!user_access('schedule revisions')) {
      return '';
    }

    $operation = array(
      'id' => $values->{$this->aliases['id']},
      'operation' => $values->{$this->aliases['operation']},
      'time_scheduled' => $values->{$this->aliases['time_scheduled']},
      'time_executed' => $values->{$this->aliases['time_executed']},
      'time_queued' => $values->{$this->aliases['time_queued']},
    );

    if (!empty($operation['time_executed'])) {
      $output = t('Completed');
    }
    elseif (!empty($operation['time_queued'])) {
      $output = t('Queued');
    }
    else {
      $items = array();
      $value = implode('-', array('run', $operation['id'], $operation['operation'], $operation['time_scheduled']));
      $items['links']['run'] = array(
        'title' => t('Run now'),
        'href' => 'revision-scheduler/' . $operation['id'] . '/run',
        'query' => array(
          'token' => drupal_get_token($value),
        ) + drupal_get_destination(),
      );
      $items['links']['delete'] = array(
        'title' => t('Cancel'),
        'href' => 'revision-scheduler/' . $operation['id'] . '/delete',
        'query' => drupal_get_destination(),
      );

      $output = theme('links__ctools_dropbutton', $items);
    }

    return $output;
  }
}
