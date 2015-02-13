<?php

/**
 * @file
 * pub_mpx_handler_filter_account.inc
 */

/**
 * Handler to provide an exposed filter for the mpx video account.
 */
class pub_mpx_handler_filter_account extends views_handler_filter {

  function exposed_form(&$form, &$form_state) {
    parent::exposed_form($form, $form_state);

    $options = array(
      'All' => '- Any -',
    );
    $result = db_query('SELECT account FROM mpx_video');
    foreach ($result as $record) {
      $options[$record->account] = rawurldecode($record->account);
    }

    $form['account']['#type'] = 'select';
    $form['account']['#options'] = $options;
    $form['account']['#default_value'] = 'All';

    $form['#info']['filter-account'] = array(
      'operator' => '',
      'value' => 'account',
      'label' => t('Source'),
      'description' => '',
    );
  }
}
