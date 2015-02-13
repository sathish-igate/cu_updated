<?php

/**
 * @file
 * Admin settings for pub_api.
 */

/**
 * Returns a settings form for pub_api.
 */
function pub_api_settings() {
  $form = array();

  $form['pub_api_accept_header'] = array(
    '#type' => 'textfield',
    '#title' => t('Accept Header'),
    '#default_value' => variable_get('pub_api_accept_header', 'application/json'),
    '#required' => TRUE,
    '#description' => t('Enter an accept header string that will be used for the API. You may use a string replacement %s to add your version string to the accept header. NOTE: currently only variants of JSON are supported for custom headers.'),
  );
  $form['pub_api_version'] = array(
    '#type' => 'textfield',
    '#title' => t('API Version'),
    '#default_value' => variable_get('pub_api_version'),
    '#description' => t('Enter the current version of your API. This can be used as a replacement variable with the accept header.'),
  );
  $form['pub_api_versions'] = array(
    '#type' => 'textfield',
    '#title' => t('API Versions'),
    '#default_value' => variable_get('pub_api_versions'),
    '#description' => t('Enter a comma separated list of API versions that you need to provide backwards compatibility for. You should include the current version (if any) in this list.'),
  );

  return system_settings_form($form);
}
