<?php
/**
 * @file
 * Handles the admin functionality for Program Guide.
 */

/**
 * Form builder for the Program Guide configuration form.
 */
function program_guide_configuration_form($form, $form_state) {
  $form['program_guide_data_url'] = array(
    '#type' => 'textfield',
    '#title' => 'Data URL',
    '#default_value' => variable_get('program_guide_data_url', ''),
    '#description' => t('Enter the feed URL of the JSON data feed provided by the NBCU video team.'),
    '#required' => TRUE,
  );
  $form['program_guide_update_interval'] = array(
    '#type' => 'select',
    '#title' => 'Update interval',
    '#options' => drupal_map_assoc(array(1, 2, 4, 6, 8, 12, 24, 72, 168)),
    '#default_value' => variable_get('program_guide_update_interval', 8),
    '#field_prefix' => t('Check for updated program data every'),
    '#field_suffix' => t('hours'),
  );
  $form['program_guide_delete_after_interval'] = array(
    '#type' => 'select',
    '#title' => 'Delete interval',
    '#options' => drupal_map_assoc(array(0, 7, 14, 30, 60, 90)),
    '#default_value' => variable_get('program_guide_delete_after_interval', 0),
    '#field_prefix' => t('Delete programs that are'),
    '#field_suffix' => t('days old'),
  );
  $form['program_guide_delete_after_interval']['#options'][0] = t('One Zillion (aka never)');

  return system_settings_form($form);
}
