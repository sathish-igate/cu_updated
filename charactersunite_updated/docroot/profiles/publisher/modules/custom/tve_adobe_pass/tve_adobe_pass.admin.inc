<?php

/**
 * @file
 * Form callback for admin page for the TVE Adobe Pass module.
 *
 * @ingroup tve_adobe_pass
 */

/**
 * Form builder callback for Adobe Pass settings form.
 */
function tve_adobe_pass_admin_form($form, &$form_state) {
  // Main settings.
  $form['tve_adobe_pass_accessenabler_loc'] = array(
    '#title' => t('Access Enabler Location'),
    '#type' => 'textfield',
    '#default_value' => variable_get('tve_adobe_pass_accessenabler_loc', TVE_ADOBE_PASS_ACCESS_ENABLER),
    '#required' => TRUE,
    '#access' => user_access('administer adobe pass config variables'),
    '#description' => t('Specify URL to Access Enabler (swf).'),
  );

  $form['tve_adobe_pass_timeout_length'] = array(
    '#title' => t('Request Timeout'),
    '#type' => 'textfield',
    '#default_value' => variable_get('tve_adobe_pass_timeout_length', TVE_ADOBE_PASS_TIMEOUT),
    '#required' => TRUE,
    '#access' => user_access('administer adobe pass config variables'),
    '#description' => t('Specify request timeout in milliseconds.'),
  );

  $form['tve_adobe_pass_flash_ver'] = array(
    '#title' => t('Adobe Flash Version'),
    '#type' => 'textfield',
    '#default_value' => variable_get('tve_adobe_pass_flash_ver', TVE_ADOBE_PASS_FLASH_VER),
    '#access' => user_access('administer adobe pass config variables'),
    '#description' => t('Specify version of the Adobe Flash.'),
  );

  $form['tve_adobe_pass_requestor_id'] = array(
    '#title' => t('Requestor ID'),
    '#type' => 'textfield',
    '#default_value' => variable_get('tve_adobe_pass_requestor_id'),
    '#required' => TRUE,
    '#access' => user_access('administer adobe pass config variables'),
    '#description' => t('Provide unique requestor id.'),
  );

  $form['tve_adobe_pass_resource_id'] = array(
    '#title' => t('Resource ID'),
    '#type' => 'textfield',
    '#default_value' => variable_get('tve_adobe_pass_resource_id'),
    '#required' => TRUE,
    '#access' => user_access('administer adobe pass config variables'),
    '#description' => t('Provide unique resource id.'),
  );

  // Additional settings - error/notice messages, Logging.
  $form['tve_adobe_pass_default_messages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Authorization Status Messages'),
  );

  $form['tve_adobe_pass_default_messages']['tve_adobe_pass_message_auth_err'] = array(
    '#title' => t('User not Authorized Error'),
    '#type' => 'textfield',
    '#default_value' => variable_get('tve_adobe_pass_message_auth_err', TVE_ADOBE_PASS_MESSAGE_AUTH_ERR),
    '#required' => TRUE,
    '#description' => t('Provide text for "User not Authorized" error message.'),
  );

  $form['tve_adobe_pass_default_messages']['tve_adobe_pass_message_internal_err'] = array(
    '#title' => t('Internal Authorization Error'),
    '#type' => 'textfield',
    '#default_value' => variable_get('tve_adobe_pass_message_internal_err', TVE_ADOBE_PASS_MESSAGE_INTERNAL_ERR),
    '#required' => TRUE,
    '#description' => t('Provide text for "Internal Authorization" error message.'),
  );

  $form['tve_adobe_pass_default_messages']['tve_adobe_pass_message_generic_err'] = array(
    '#title' => t('Generic Authorization Error'),
    '#type' => 'textfield',
    '#default_value' => variable_get('tve_adobe_pass_message_generic_err', TVE_ADOBE_PASS_MESSAGE_GENERIC_ERR),
    '#required' => TRUE,
    '#description' => t('Provide text for "Generic Authorization" error message.'),
  );

  $form['tve_adobe_pass_logging'] = array(
    '#title' => t('Log error messages'),
    '#type' => 'checkbox',
    '#description' => t('Enable error logging (watchdog and file).'),
    '#default_value' => variable_get('tve_adobe_pass_logging', 0),
    '#access' => user_access('administer adobe pass config variables'),
  );

  $form['tve_adobe_pass_config_service_path'] = array(
    '#title' => t('Adobe Pass Config Service Path'),
    '#type' => 'textfield',
    '#default_value' => variable_get('tve_adobe_pass_config_service_path', TVE_ADOBE_PASS_CONFIG_PATH),
    '#required' => TRUE,
    '#description' => t('Absolute URL to the Adobe Pass config service.'),
  );

  // Add the "Test configuration" button.
  $form['actions']['test_connection'] = array(
    '#type' => 'submit',
    '#value' => t('Test configuration'),
    '#submit' => array('tve_adobe_pass_admin_form_submit_test_configuration'),
  );

  return system_settings_form($form);
}

/**
 * Additional form submit callback for Adobe Pass settings form.
 *
 * Tests the Adobe Pass configurations.
 */
function tve_adobe_pass_admin_form_submit_test_configuration($form, &$form_state) {
  $configurations = $form_state['values'];

  $accessenabler_loc = $configurations['tve_adobe_pass_accessenabler_loc'];
  $response = drupal_http_request($accessenabler_loc);

  if (empty($response->data)) {
    drupal_set_message(t('Access Enabler Location is invalid.'), 'error');
    return;
  }

  $service_url = $configurations['tve_adobe_pass_config_service_path'] . $configurations['tve_adobe_pass_requestor_id'] . '.json';
  $response = drupal_http_request($service_url);

  $config = array();
  if (isset($response->data) && !isset($response->error)) {
    $config = drupal_json_decode($response->data);
  }

  if (!$config) {
    drupal_set_message(t('Requestor ID is invalid.'), 'error');
    return;
  }

  $whitelisted_domains = isset($config['requestor']['domains']['domain']) ? $config['requestor']['domains']['domain'] : array();
  if (!$whitelisted_domains || !_tve_adobe_pass_validate_domain($_SERVER['HTTP_HOST'], $whitelisted_domains)) {
    drupal_set_message(t('Current domain has not been whitelisted in Adobe.'), 'error');
    return;
  }

  drupal_set_message(t('All the configurations are valid.'), 'status');
}

/**
 * Validates the current site domain.
 *
 * Domains are validated against the white listed domains in the Adobe config.
 *
 * @param string $current_domain
 *   The domain to validate.
 *
 * @param array $white_listed_domains
 *   The domains with which to validate against.
 *
 * @return bool
 *   TRUE if domain is white listed.
 */
function _tve_adobe_pass_validate_domain($current_domain, $white_listed_domains) {
  foreach ($white_listed_domains as $value) {
    if (strpos($current_domain, $value['value']) !== FALSE) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
 * Page callback for the "admin/config/services/adobe-pass/error-logs" path.
 */
function tve_adobe_pass_admin_page_error_logs() {
  $variables = array(
    'heading' => t('Adobe Pass error log files:'),
  );

  $files = file_scan_directory(_tve_adobe_pass_error_log_get_dir(), '/.*\.csv/');
  foreach ($files as $file) {
    $variables['links'][] = array(
      'title' => $file->filename,
      'href' => file_create_url($file->uri),
    );
  }

  return theme('links', $variables);
}

/**
 * Confirmation form builder.
 */
function tve_adobe_pass_admin_page_error_logs_cleanup_confirm($form, &$form_state) {
  return confirm_form(
    $form,
    t('Cleanup Adobe Pass error log files'),
    'admin/config/services/adobe-pass/error-logs',
    t('Are you sure you want to delete all Adobe Pass error log files?'),
    t('Yes'),
    t('No')
  );
}

/**
 * Confirmation form submit function.
 *
 * Deletes the error log files.
 */
function tve_adobe_pass_admin_page_error_logs_cleanup_confirm_submit($form, &$form_state) {
  $files = file_scan_directory(_tve_adobe_pass_error_log_get_dir(), '/.*\.csv/');
  foreach ($files as $file) {
    if (file_unmanaged_delete($file->uri)) {
      drupal_set_message(t('File !file deleted successfully.', array('!file' => $file->filename)));
    }
    else {
      drupal_set_message(t('File !file could not be deleted.', array('!file' => $file->filename)), 'error');
    }
  }

  $form_state['redirect'] = 'admin/config/services/adobe-pass/error-logs';
}
