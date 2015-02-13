<?php

/**
 * @file
 * Class pub_report_server_handler_filter_sitename
 */

class pub_report_server_handler_filter_sitename extends views_handler_filter {
  /**
   * {@inheritdoc}
   */
  function exposed_form(&$form, &$form_state) {
    parent::exposed_form($form, $form_state);

    $options = array(
      'All' => '- Any -',
    );
    $result = db_query('SELECT DISTINCT site_name FROM pub_report_sites');
    foreach ($result as $record) {
      $options[$record->site_name] = rawurldecode($record->site_name);
    }

    $form['site_name']['#type'] = 'select';
    $form['site_name']['#options'] = $options;
    $form['site_name']['#default_value'] = 'All';

    $form['#info']['filter-account'] = array(
      'operator' => '',
      'value' => 'site_name',
      'label' => t('Site name'),
      'description' => '',
    );

  }
}
