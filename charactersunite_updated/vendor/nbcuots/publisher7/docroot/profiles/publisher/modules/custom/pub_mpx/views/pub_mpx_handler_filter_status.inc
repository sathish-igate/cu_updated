<?php

/**
 * @file
 * pub_mpx_handler_filter_status.inc
 */

/**
 * Handler to provide an exposed filter for the mpx video published state.
 */
class pub_mpx_handler_filter_status extends views_handler_filter {

  function exposed_form(&$form, &$form_state) {
    parent::exposed_form($form, $form_state);

    $options = array(
      'All' => '- Any -',
      'Published' => 'Published',
      'Unpublished' => 'Unpublished',
      'Expired' => 'Expired',
    );

    $form['status']['#type'] = 'select';
    $form['status']['#options'] = $options;
    $form['status']['#default_value'] = 'All';

    $form['#info']['filter-status'] = array(
      'operator' => '',
      'value' => 'published',
      'label' => t('Published'),
      'description' => '',
    );
  }

  function query() {
    parent::ensure_my_table();

    if (!empty($this->value[0])) {
      $test_value = strtolower($this->value[0]);
      $unix_time = time();

      // Condition for testing that the expiration date has not been expired.
      $condition_not_expired = db_or()
        ->condition('mpx_video.expiration_date', 0, '=')
        ->condition('mpx_video.expiration_date', $unix_time, '>');

      if ($test_value === 'published') {
        $this->query->add_where(0, 'mpx_video.status', 1, '=');
        $this->query->add_where(0, $condition_not_expired);
      }
      elseif ($test_value === 'unpublished') {
        $this->query->add_where(0, 'mpx_video.status', 0, '=');
        $this->query->add_where(0, $condition_not_expired);
      }
      else {
        $this->query->add_where(0, 'mpx_video.expiration_date', 0, '>');
        $this->query->add_where(0, 'mpx_video.expiration_date', $unix_time, '<=');
      }
    }
  }
}
