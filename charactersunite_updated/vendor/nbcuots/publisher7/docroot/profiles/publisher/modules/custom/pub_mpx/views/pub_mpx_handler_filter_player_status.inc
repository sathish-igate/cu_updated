<?php

/**
 * @file
 * pub_mpx_handler_filter_player_status.inc
 */

/**
 * Handler to provide an exposed filter for the mpx player published state.
 */
class pub_mpx_handler_filter_player_status extends views_handler_filter {

  function exposed_form(&$form, &$form_state) {
    parent::exposed_form($form, $form_state);

    $options = array(
      'All' => '- Any -',
      'published' => 'Published',
      'unpublished' => 'Unpublished',
    );

    $form['status']['#type'] = 'select';
    $form['status']['#options'] = $options;
    $form['status']['#default_value'] = 'All';

    $form['#info']['filter-status'] = array(
      'operator' => '',
      'value' => 'published',
      'label' => t('MPX Status'),
      'description' => '',
    );
  }

  function query() {
    parent::ensure_my_table();

    if (!empty($this->value[0])) {
      $test_value = strtolower($this->value[0]);
      if ($test_value === 'published') {
        $this->query->add_where(0, 'mpx_player.status', 1, '=');
      }
      elseif ($test_value === 'unpublished') {
        $this->query->add_where(0, 'mpx_player.status', 0, '=');
      }
    }
  }
}
