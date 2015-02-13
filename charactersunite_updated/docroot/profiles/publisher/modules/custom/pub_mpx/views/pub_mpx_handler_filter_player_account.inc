<?php

/**
 * @file
 * pub_mpx_handler_filter_player_account.inc
 */

/**
 * Handler to provide an exposed filter for the mpx player account.
 */
class pub_mpx_handler_filter_player_account extends views_handler_filter {
  function exposed_form(&$form, &$form_state) {
    parent::exposed_form($form, $form_state);
    $options = array(
      'All' => '- Any -',
    );

    $result = db_query('SELECT DISTINCT account FROM mpx_player');
    foreach ($result as $record) {
      $options[$record->account] = rawurldecode($record->account);
    }

    $form['player_account']['#type'] = 'select';
    $form['player_account']['#options'] = $options;
    $form['player_account']['#default_value'] = 'All';

    $form['#info']['filter-account'] = array(
      'operator' => '',
      'value' => 'player_account',
      'label' => t('Player account'),
      'description' => '',
    );

  }
}
