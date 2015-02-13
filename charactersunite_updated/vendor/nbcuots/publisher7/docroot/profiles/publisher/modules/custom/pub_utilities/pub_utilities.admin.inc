<?php

/**
 * Form builder for the admin function.
 */
function pub_utilities_admin_settings() {
  $form['settings'] = array(
    '#type' => 'vertical_tabs',
  );

  // Default tag settings.
  $form['pub_utilities_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Publisher Utilities Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#group' => 'settings',
  );
  $form['pub_utilities_settings']['pub_utilities_git_bin'] = array(
    '#type' => 'textfield',
    '#title' => t('Server path to the git binary'),
    '#description' => t('On most servers this should be populated automatically, but on some servers you must specify the location of the git bin. Ex. /usr/local/bin/git'),
    '#default_value' => variable_get('pub_utilities_git_bin', ''),
  );
  $form['pub_utilities_settings']['pub_utilities_drush_bin'] = array(
    '#type' => 'textfield',
    '#title' => t('Server path to the drush binary'),
    '#description' => t('On most servers this should be populated automatically, but on some servers you must specify the location of the drush bin. Ex. /usr/local/bin/drush'),
    '#default_value' => variable_get('pub_utilities_drush_bin', ''),
  );
  $form['pub_utilities_settings']['pub_utilities_github_org_name'] = array(
    '#type' => 'textfield',
    '#title' => t('NBCUOTS GitHub Orginization Name'),
    '#description' => t('Enter the orginization on GitHub that owns main Publisher Core repositories.'),
    '#default_value' => variable_get('pub_utilities_github_org_name', ''),
  );
  $form['pub_utilities_settings']['pub_utilities_github_pubcore_repo_name'] = array(
    '#type' => 'textfield',
    '#title' => t('NBCUOTS GitHub Publisher Core Repository Name'),
    '#description' => t('Enter the name of Publisher Core repository on GitHub.'),
    '#default_value' => variable_get('pub_utilities_github_pubcore_repo_name', ''),
  );

  $form['pub_utilities_advanced_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#group' => 'settings',
  );
  $form['pub_utilities_advanced_settings']['pub_utilities_debug_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable debug mode.'),
    '#description' => t('Display debugging messages when running utilities.'),
    '#default_value' => variable_get('pub_utilities_debug_mode', '0'),
  );

  return system_settings_form($form);
}
