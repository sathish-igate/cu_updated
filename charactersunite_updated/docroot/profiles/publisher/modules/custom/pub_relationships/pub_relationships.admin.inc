<?php

/**
 * @file
 *
 * Admin configuration for Publisher Relationships module.
 */

/**
 *
 */
function pub_relationships_config() {
  $form = array();

  // If this module is enabled without of any of the other modules
  // then this is really pointless. Just display a warning and return.
  if (!module_exists('pub_relationships_tv') && !module_exists('pub_relationships_movie')) {
    drupal_set_message(t('You must enabled Publisher TV Relationships or Publisher Movie Relationships to use this form.'), 'warning');
    return $form;
  }

  // We set up the Verticle tabs for the sub-modules.
  $form['wrapper'] = array(
    '#type' => 'vertical_tabs',
    '#attached' => array(
      'css' => array(
        drupal_get_path('module', 'pub_relationships') . '/pub_relationships-admin.css',
      ),
    ),
    '#attributes' => array(
      'class' => array('pub-relationships'),
    ),
  );

  return system_settings_form($form);
}
