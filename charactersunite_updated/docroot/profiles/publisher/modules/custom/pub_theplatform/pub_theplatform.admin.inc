<?php

/**
 * @file
 * The admin functionality for pub_theplatform.
 */

/**
 * Form builder; administration form.
 */
function pub_theplatform_admin_form($form) {
  $form = array();
  $form['theplatform_feed_url'] = array(
    '#title' => t('thePlatform Site Feed URL'),
    '#description' => t("Enter the URL where thePlatform's information can be fetched from."),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('theplatform_feed_url', ''),
  );

  $form['theplatform_player_url'] = array(
    '#title' => t('thePlatform Site Player URL'),
    '#description' => t("Enter the URL for the player in thePlatform's player services."),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('theplatform_player_url', ''),
  );

  $options = array();
  foreach (views_get_all_views() as $name => $view) {
    if ($view->base_table == 'thePlatform') {
      foreach ($view->display as $display_name => $display) {
        if (isset($display->display_options['fields']['guid']) && isset($display->display_options['fields']['title'])) {
          $options[$name] = $view->human_name;
        }
      }
    }
  }
  $form['pub_theplatform_selection_view'] = array(
    '#title' => t('thePlatform Item Selection View'),
    '#description' => t('Choose a view that will be used for selecting items in the media browser.  It should be a table view, and have the GUID and Title displaying at a minimum.'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => variable_get('pub_theplatform_selection_view', 'theplatform_videos'),
  );
  $form['pub_theplatform_cache_ttl'] = array(
    '#title' => t('Cache TTL for responses from thePlatform'),
    '#description' => t('Cache lifetime in seconds.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('pub_theplatform_cache_ttl', 300),
  );

  $form['#validate'][] = 'pub_theplatform_admin_validate';
  return system_settings_form($form);
}

/**
 * Validation handler for pub_theplatform_admin_form.
 */
function pub_theplatform_admin_validate(&$form, &$form_state) {
  if (!is_numeric($form_state["values"]["pub_theplatform_cache_ttl"])) {
    form_set_error('pub_theplatform_cache_ttl', 'The TTL must be an integer.');
  }
}

/**
 * Defines the fields form.
 *
 * Administrative form that handles linking fields in the thePlatform feed to
 * the fields that are on the video file type.
 */
function pub_theplatform_fields_form() {
  $form = array();

  $form['pub_theplatform_fields'] = array(
    '#title' => 'Attribute Map',
    '#description' => t('Enter the name of the field from the feed that should be used to populate the field in Drupal.  Leave blank to disable that field for thePlatform videos.'),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#tree' => TRUE,
  );

  // Get current settings.
  $defaults = variable_get('pub_theplatform_fields', array());

  // Get a list of the fields that exist on the bundle (filetype) that we care
  // about - video. Also, arrange it for the field matching.
  foreach (field_info_instances('file', 'video') as $machine => $info) {
    if (!$info['widget']['type'] === 'text_textfield') {
      // Bypass anything that isn't a supported field type.
      continue;
    }

    $form['pub_theplatform_fields'][$machine] = array(
      '#title' => $info['label'],
      '#type' => 'textfield',
      '#default_value' => array_key_exists($machine, $defaults) ? $defaults[$machine] : '',
    );
  }

  return system_settings_form($form);
}
