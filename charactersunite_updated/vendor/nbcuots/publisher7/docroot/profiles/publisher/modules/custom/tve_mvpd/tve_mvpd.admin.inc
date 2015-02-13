<?php

/**
 * @file
 * Form callback for admin pages for the TVE MVPD module.
 *
 * @ingroup tve_mvpd
 */

/**
 * Form constructor for admin/config/services/mvpd/connection.
 *
 * @see tve_mvpd_menu()
 * @ingroup forms
 */
function tve_mvpd_admin_connection_form($form, &$form_state) {
  // Get "MVPD Admin" service URL.
  $service_url = _tve_mvpd_get_service_url();
  if ($service_url) {
    $form['tve_mvpd_service_url_info'] = array(
      '#type' => 'item',
      '#title' => t('MVPD Admin Service URL'),
      '#markup' => l($service_url, $service_url),
    );
  }
  else {
    drupal_set_message(t('MVPD service URL incorrect (or not provided).'), 'warning');
  }

  // We'll add this suffix to fields that are required, so they look as normal
  // required fields, while their values are checked manually in custom
  // validation handler. Made because we have checkbox-dependant required state.
  $required_suffix = ' <span class="form-required" title="' . t('This field is required.') . '">*</span>';

  // Advanced input mode.
  $form['tve_mvpd_advanced_mode'] = array(
    '#title' => t('Advanced settings'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('tve_mvpd_advanced_mode', 0),
    '#description' => t('For experienced users only.'),
  );

  // Raw MVPD service url.
  $form['tve_mvpd_service_raw'] = array(
    '#title' => t('Absolute MVPD Service URL') . $required_suffix,
    '#type' => 'textfield',
    '#default_value' => variable_get('tve_mvpd_service_raw', ''),
    '#description' => t('Absolute and complete (raw) URL to the MVPD service.'),
    '#states' => array(
      'invisible' => array(
        ':input#edit-tve-mvpd-advanced-mode' => array('checked' => FALSE),
      ),
    ),
  );

  $form['security'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Security'),
    '#states' => array(
      'invisible' => array(
        ':input#edit-tve-mvpd-advanced-mode' => array('checked' => FALSE),
      ),
    ),
  );

  // Authentication mechanism.
  $form['security']['tve_mvpd_security'] = array(
    '#title' => t('Endpoint authentication mechanism'),
    '#type' => 'select',
    '#options' => array(
      'api_key' => t('API Key only'),
      'sha256' => t('Key + Secret + Timestamp Hash (SHA-256)'),
      'md5' => t('Key + Secret + Timestamp Hash (MD5)'),
    ),
    '#default_value' => variable_get('tve_mvpd_security', 'api_key'),
    '#description' => t('Select authentication mechanism.'),
  );

  // API key.
  $form['security']['tve_mvpd_api_key'] = array(
    '#title' => t('API Key') . $required_suffix,
    '#type' => 'textfield',
    '#default_value' => variable_get('tve_mvpd_api_key', ''),
    '#description' => t('The value of the API key is a 24 character alphanumeric string.'),
  );

  // Secret key.
  $form['security']['tve_mvpd_api_secret'] = array(
    '#title' => t('Secret Key') . $required_suffix,
    '#type' => 'textfield',
    '#default_value' => variable_get('tve_mvpd_api_secret', ''),
    '#description' => t('The value of the secret key is a 10 character alphanumeric string.'),
    '#states' => array(
      'invisible' => array(
        ':input#edit-tve-mvpd-security' => array('value' => 'api_key'),
      ),
    ),
  );

  // MVPD service url.
  $form['tve_mvpd_service'] = array(
    '#title' => t('MVPD Service URL') . $required_suffix,
    '#type' => 'textfield',
    '#default_value' => variable_get('tve_mvpd_service', ''),
    '#description' => t('Absolute URL to the MVPD service.'),
    '#states' => array(
      'invisible' => array(
        ':input#edit-tve-mvpd-advanced-mode' => array('checked' => TRUE),
      ),
    ),
  );

  // Requestor ID.
  $form['tve_mvpd_brand_id'] = array(
    '#title' => t('Requestor ID') . $required_suffix,
    '#type' => 'textfield',
    '#default_value' => variable_get('tve_mvpd_brand_id', ''),
    '#description' => t('Specify unique requestor ID.'),
    '#states' => array(
      'invisible' => array(
        ':input#edit-tve-mvpd-advanced-mode' => array('checked' => TRUE),
      ),
    ),
  );

  // Instance (environment).
  $form['tve_mvpd_instance'] = array(
    '#title' => t('Instance') . $required_suffix,
    '#type' => 'select',
    '#options' => drupal_map_assoc(array(TVE_MVPD_INST_PROD, TVE_MVPD_INST_STAGE)),
    '#default_value' => variable_get('tve_mvpd_instance', ''),
    '#description' => t('Specify type of an instance.'),
    '#states' => array(
      'invisible' => array(
        ':input#edit-tve-mvpd-advanced-mode' => array('checked' => TRUE),
      ),
    ),
  );

  // Generic "error" message.
  $form['tve_mvpd_error_message'] = array(
    '#title' => t('Generic Error Message'),
    '#type' => 'textarea',
    '#default_value' => variable_get('tve_mvpd_error_message', TVE_MVPD_ERROR_MESSAGE),
    '#required' => TRUE,
    '#description' => t('Provide text of a generic error message.'),
  );

  // "Check connection" button.
  $form['tve_mvpd_check_connection'] = array(
    '#type' => 'button',
    '#value' => t('Check Connection'),
    '#name' => 'check_connection',
  );

  return system_settings_form($form);
}

/**
 * Form validation handler for tve_mvpd_admin_connection_form().
 */
function tve_mvpd_admin_connection_form_validate($form, &$form_state) {
  // Advanced mode.
  if (!empty($form_state['values']['tve_mvpd_advanced_mode'])) {
    $service_url = trim($form_state['values']['tve_mvpd_service_raw'], '/');
    $form_state['values']['tve_mvpd_service_url'] = $service_url;
    $api_key = trim($form_state['values']['tve_mvpd_api_key']);
    $secret_key = trim($form_state['values']['tve_mvpd_api_secret']);
    $method = $form_state['values']['tve_mvpd_security'];

    if (empty($service_url)) {
      form_set_error('tve_mvpd_service_raw', t('MVPD Service URL field is requred.'));
      return;
    }

    if (empty($api_key)) {
      form_set_error('tve_mvpd_api_key', t('API Key field is requred.'));
      return;
    }

    if (!valid_url($service_url)) {
      form_set_error('tve_mvpd_service_raw', t('Invalid MVPD Service URL'));
      return;
    }

    $query = array('api_key' => $api_key);
    if (in_array($method, array('sha256', 'md5'))) {
      if (!$secret_key) {
        form_set_error('tve_mvpd_api_secret', t('Secret Key field is requred.'));
        return;
      }
      $query['sig'] = tve_mvpd_generate_signature($api_key, $secret_key, $method);
    }

    $service_url = url($service_url, array('query' => $query));
  }
  // Simple mode.
  else {
    $service = trim($form_state['values']['tve_mvpd_service'], '/');
    if (empty($service)) {
      form_set_error('tve_mvpd_service_raw', t('MVPD Service URL field is requred.'));
      return;
    }

    if (!valid_url($service)) {
      form_set_error('tve_mvpd_service', t('Invalid MVPD Service URL'));
      return;
    }

    $brand = trim($form_state['values']['tve_mvpd_brand_id']);
    if (empty($brand)) {
      form_set_error('tve_mvpd_brand_id', t('Requestor ID field is requred.'));
      return;
    }
    $form_state['values']['tve_mvpd_brand_id'] = $brand;

    $instance = trim($form_state['values']['tve_mvpd_instance']);
    if (empty($brand)) {
      form_set_error('tve_mvpd_brand_id', t('Instance field is requred.'));
      return;
    }
    $form_state['values']['tve_mvpd_instance'] = $instance;

    $service_url = "{$service}/{$brand}/{$instance}";
    $form_state['values']['tve_mvpd_service_url'] = $service_url;
  }

  if ('check_connection' != $form_state['triggering_element']['#name']) {
    return;
  }

  $results = _tve_mvpd_get_providers_from_service($service_url);

  if (!$results) {
    form_set_error('', t('Could not retrieve MVPD data from URL %url', array(
      '%url' => $service_url,
    )));
  }
  else {
    drupal_set_message(t('Service URL %url has been requested successfully.', array(
      '%url' => $service_url,
    )));
    if (module_exists('devel')) {
      dpm($results, t('Results'));
    }
  }
}

/**
 * Form constructor for admin/config/services/mvpd.
 *
 * @see tve_mvpd_menu()
 * @ingroup forms
 */
function tve_mvpd_admin_form($form, &$form_state) {
  // Retrieve all available MVPD providers.
  $default_providers = _tve_mvpd_get_providers();
  if ($default_providers === NULL) {
    // Providers not found.
    drupal_set_message(t('Providers (MVPDs) not found. Please check connection settings to MVPD service on the "MVPD Connection" page.'), 'warning');
    return $form;
  }

  // Place featured providers on top, sorted by weight,
  // and place non-featured providers below featured, sorted by title.
  usort($default_providers, '_tve_mvpd_compare_providers');

  // Get providers with configured settings.
  $configured_providers = variable_get('tve_mvpd_configured_providers', array());

  $default_global_settings = variable_get('tve_mvpd_default_settings', array());

  // Default global settings form.
  $form['default_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default global settings'),
    '#collapsible' => FALSE,
    '#tree' => TRUE,
  );

  $form['default_settings']['mvpd_logo'] = array(
    '#type' => 'radios',
    '#title' => t('Grid Logo'),
    '#description' => t('Choose global MVPD grid logo settings between dark or light.'),
    '#options' => array(
      TVE_MVPD_LOGO_DARK => t('Dark'),
      TVE_MVPD_LOGO_LIGHT => t('Light'),
    ),
    '#default_value' => isset($default_global_settings['mvpd_logo']) ? $default_global_settings['mvpd_logo'] : TVE_MVPD_LOGO_DARK,
  );

  $form['default_settings']['mvpd_color'] = array(
    '#type' => 'radios',
    '#title' => t('Header/Footer Logo'),
    '#description' => t('Choose global MVPD header/footer logo settings between dark or light.'),
    '#options' => array(
      TVE_MVPD_COLOR_DARK => t('Dark'),
      TVE_MVPD_COLOR_LIGHT => t('Light'),
    ),
    '#default_value' => isset($default_global_settings['mvpd_color']) ? $default_global_settings['mvpd_color'] : TVE_MVPD_COLOR_LIGHT,
  );

  // "Reset" confirmation button.
  $form['default_settings']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Reset to defaults'),
    '#submit' => array('_tve_mvpd_reset_button_submit'),
  );

  // Create form elements for all providers.
  foreach ($default_providers as $default_provider) {
    // Prepare machine name for a form element.
    $mvpd_title = _tve_mvpd_get_clean_title($default_provider->field_mvpd_id);
    $messages = array(
      'overridden' => '',
      'conflict' => '',
    );

    // Prepare default values for select (radios) inputs.
    if (isset($configured_providers[$mvpd_title])) {
      $current_provider_data = $configured_providers[$mvpd_title];
      $messages['overridden'] = format_string(' (!status)', array(
        '!status' => t('Overridden'),
      ));

      // Using plain HTML because theme_html_tag adds "\n" symbol at the end,
      // which breaks layout in Chrome.
      $messages['overridden'] = '<span class="mvpd-overridden-logo">' . $messages['overridden'] . '</span>';
    }
    else {
      $current_provider_data = array(
        'mvpd_color' => TVE_MVPD_DEFAULT,
        'mvpd_logo' => TVE_MVPD_DEFAULT,
      );
    }

    // Options for select (radios) inputs.
    $options = _tve_mvpd_get_mvpd_data($default_provider, $current_provider_data);

    // Checks conflicts.
    $messages['conflict_color'] = _tve_mvpd_check_default_logos($options, $current_provider_data, $default_global_settings, 'mvpd_color');
    $messages['conflict_logo'] = _tve_mvpd_check_default_logos($options, $current_provider_data, $default_global_settings, 'mvpd_logo');
    if ($messages['conflict_color'] || $messages['conflict_logo']) {
      $messages['conflict'] = format_string(' (!status)', array(
        '!status' => t('Conflict with default settings'),
      ));

      // Using plain HTML because theme_html_tag() adds "\n" symbol at the end,
      // which breaks layout in Chrome.
      $messages['conflict'] = '<span class="mvpd-conflict-logo">' . $messages['conflict'] . '</span>';
    }

    // Insert the "Featured MVPDs" label above them, once.
    if ($default_provider->featured && !isset($featured_mvpds_label_inserted)) {
      $featured_mvpds_label_inserted = TRUE;

      $form['featured_mvpds_label'] = array(
        '#type' => 'item',
        '#title' => format_string('!label:', array(
          '!label' => t('Featured MVPDs'),
        )),
      );
    }

    // Insert the "Other MVPDs" label above them, once.
    if (!$default_provider->featured && !isset($other_mvpds_label_inserted)) {
      $other_mvpds_label_inserted = TRUE;

      $form['other_mvpds_label'] = array(
        '#type' => 'item',
        '#title' => format_string('!label:', array(
          '!label' => t('Other MVPDs'),
        )),
      );
    }

    // Personal fieldset for provider.
    $form[$mvpd_title] = array(
      '#type' => 'fieldset',
      '#title' => $default_provider->title . $messages['overridden'] . $messages['conflict'],
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#tree' => TRUE,
    );

    // "MVPD Logo" input.
    $form[$mvpd_title]['mvpd_logo'] = array(
      '#type' => 'radios',
      '#title' => t('MVPD Grid Logo Settings'),
      '#description' => t('Choose MVPD logo with alternative images. It will be used in the login window grid.') . $messages['conflict_logo'],
      '#options' => $options['mvpd_logo'],
      '#default_value' => isset($current_provider_data['mvpd_logo']) ? $current_provider_data['mvpd_logo'] : NULL,
      '#theme' => 'tve_mvpd_custom_radios',
    );

    // "MVPD Color" input.
    $form[$mvpd_title]['mvpd_color'] = array(
      '#type' => 'radios',
      '#title' => t('MVPD Header/Footer Logo Settings'),
      '#description' => t('Choose MVPD logo. It will be used in header and footer blocks.') . $messages['conflict_color'],
      '#options' => $options['mvpd_color'],
      '#default_value' => isset($current_provider_data['mvpd_color']) ? $current_provider_data['mvpd_color'] : NULL,
      '#theme' => 'tve_mvpd_custom_radios',
    );
  }

  // Submit for save all overridden MVPD logo.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  // @todo Use system_settings_form($form) or explain 'why' we don't use it.
  return $form;
}

/**
 * Submission handler for 'Reset to defaults' button element.
 *
 * @see tve_mvpd_admin_form()
 */
function _tve_mvpd_reset_button_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/config/services/mvpd-reset';
}

/**
 * Form constructor for admin/config/services/mvpd-reset.
 *
 * @see tve_mvpd_menu()
 * @ingroup forms
 */
function _tve_mvpd_reset_confirm_form($form, &$form_state) {
  return confirm_form(
    $form,
    t('Reset MVPD settings'),
    'admin/config/services/mvpd',
    t('Are you sure you want to reset all MVPD settings to defaults?'),
    t('Reset'),
    t('Back')
  );
}

/**
 * Form submission handler for _tve_mvpd_reset_confirm_form().
 */
function _tve_mvpd_reset_confirm_form_submit($form, &$form_state) {
  variable_del('tve_mvpd_configured_providers');
  drupal_set_message(t('Default MVPD settings restored.'));

  $form_state['redirect'] = 'admin/config/services/mvpd';
}

/**
 * Form submission handler for tve_mvpd_admin_form().
 */
function tve_mvpd_admin_form_submit($form, &$form_state) {
  // Default global settings.
  if (!empty($form_state['values']['default_settings'])) {
    variable_set('tve_mvpd_default_settings', $form_state['values']['default_settings']);
  }
  unset($form_state['values']['default_settings']);

  $configured_providers = array();
  foreach ($form_state['values'] as $name => $value) {
    // Collect all provider settings - each provider has its own
    // "[provider] => (array) [settings]" pair inside $form_state['values'].
    if (is_array($value) &&
      ($value['mvpd_logo'] != TVE_MVPD_DEFAULT || $value['mvpd_color'] != TVE_MVPD_DEFAULT)) {
      // Each provider has array of settings (at least two properties).
      $configured_providers[$name] = $value;
    }
  }
  variable_set('tve_mvpd_configured_providers', $configured_providers);
  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Checks MVPD data and compares with default settings.
 *
 * @param array $provider
 *   MVPD data.
 * @param array $default
 *   Default settings.
 *
 * @return array
 *   Returns cleaned data. Options for select inputs.
 */
function _tve_mvpd_get_mvpd_data($provider, &$default) {
  // "MVPD color" property.
  $mvpd_color = array(
    TVE_MVPD_DEFAULT => 'Default global settings',
  );
  if (!empty($provider->{TVE_MVPD_COLOR_DARK})) {
    // Dark color value (URL to an image).
    $mvpd_color[TVE_MVPD_COLOR_DARK] = $provider->{TVE_MVPD_COLOR_DARK};
  }

  if (!empty($provider->{TVE_MVPD_COLOR_LIGHT})) {
    // Light color value (URL to an image).
    $mvpd_color[TVE_MVPD_COLOR_LIGHT] = $provider->{TVE_MVPD_COLOR_LIGHT};
  }

  if (!isset($default['mvpd_color'], $mvpd_color[$default['mvpd_color']])) {
    // Reset default (selected) option for "MVPD color" if stored one not found.
    $default['mvpd_color'] = key($mvpd_color);
  }

  // "MVPD logo" property.
  $mvpd_logos = array(
    TVE_MVPD_DEFAULT => 'Default global settings',
  );
  if (!empty($provider->{TVE_MVPD_LOGO_DARK})) {
    // Dark logo value (URL to an image).
    $mvpd_logos[TVE_MVPD_LOGO_DARK] = $provider->{TVE_MVPD_LOGO_DARK};
  }

  if (!empty($provider->{TVE_MVPD_LOGO_LIGHT})) {
    // Light logo value (URL to an image).
    $mvpd_logos[TVE_MVPD_LOGO_LIGHT] = $provider->{TVE_MVPD_LOGO_LIGHT};
  }

  if (!isset($default['mvpd_logo'], $mvpd_logos[$default['mvpd_logo']])) {
    // Reset default (selected) option for "MVPD logo" if stored one not found.
    $default['mvpd_logo'] = key($mvpd_logos);
  }

  return array(
    'mvpd_color' => $mvpd_color,
    'mvpd_logo' => $mvpd_logos,
  );
}

/**
 * Checks default logo by logo type.
 *
 * If default logo settings don't exist return conflict text with HTML tag for
 * form field description.
 *
 * @param array $options
 *   Logo options.
 *
 * @param array $provider
 *   Information on the MVPD provider.
 *
 * @param array $settings
 *   Logo settings.
 *
 * @param string $logo_type
 *   What type of logo is being displayed.
 *
 * @return string
 *   Empty string or themed HTML to display an error.
 */
function _tve_mvpd_check_default_logos($options, $provider, $settings, $logo_type) {
  $conflict_text = '';
  if ($provider[$logo_type] == TVE_MVPD_DEFAULT && empty($options[$logo_type][$settings[$logo_type]])) {
    $conflict_text = theme('html_tag', array(
      'element' => array(
        '#tag' => 'div',
        '#value' => t("Default global logo doesn't exist here. You can choose logo for this MVPD or will use the first logo settings by default"),
        '#attributes' => array(
          'class' => array('mvpd-conflict-logo-desc'),
        ),
      ),
    ));
  }

  return $conflict_text;
}

/**
 * Compares providers by featured status, weight, or name.
 *
 * @param object $provider1
 *   The first provider.
 *
 * @param object $provider2
 *   The second provider.
 *
 * @return int
 *   1, 0, or -1 depending on provider data.
 *
 * @see tve_mvpd_admin_form()
 */
function _tve_mvpd_compare_providers($provider1, $provider2) {
  if ($provider1->featured && !$provider2->featured) {
    return -1;
  }

  if ($provider2->featured && !$provider1->featured) {
    return 1;
  }

  if (!$provider1->featured && !$provider2->featured) {
    return strnatcmp($provider1->title, $provider2->title);
  }

  if ($provider1->weight == $provider2->weight) {
    return 0;
  }

  return $provider1->weight < $provider2->weight ? -1 : 1;
}
