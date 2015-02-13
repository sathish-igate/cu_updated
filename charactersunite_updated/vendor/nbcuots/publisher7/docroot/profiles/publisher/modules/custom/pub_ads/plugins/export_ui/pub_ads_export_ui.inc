<?php

/**
 * @file
 * Ctools Export UI plugin for Pub Ads.
 */

/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'pub_ads_paths',
  'access' => 'administer site configuration',

  // Define the menu item.
  'menu' => array(
    'menu item' => 'pub-ads',
    'menu prefix' => 'admin/structure',
    'menu title' => 'Publisher Ads Side Files',
    'menu description' => 'Administer Pub Ads side Files.',
  ),
  'handler' => array(
    'class' => 'pub_ads_files_ui',
    'parent' => 'ctools_export_ui',
  ),
  'title singular' => t('side file'),
  'title plural' => t('side files'),
  'title singular proper' => t('Side file'),
  'title plural proper' => t('Side files'),
  // Define the names of the functions that provide the add/edit forms.
  'form' => array(
    'settings' => 'pub_ads_form',
    'submit' => 'pub_ads_form_submit',
  ),
);

/**
 * Form constructor for creating an ad tag.
 *
 * @see pub_ads_form_submit()
 */
function pub_ads_form(&$form, &$form_state) {
  $pub_file = $form_state['item'];
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('A human readable name for this ad path tag.'),
    '#required' => TRUE,
    '#maxlength' => 128,
    '#default_value' => $pub_file->name,
  );
  $form['machine_name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Machine Name'),
    '#maxlength' => 32,
    '#description' => t('Only use letters, numbers and underscores.'),
    '#machine_name' => array(
      'exists' => 'pub_ads_file_name_exists',
      'source' => array('name'),
    ),
  );

  // Merge the machine_name that way it can tell new from edit.
  $form['machine_name'] += $form['info']['machine_name'];
  unset($form['info']);

  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path'),
    '#description' => t('The resolvable path for this ad file.'),
    '#required' => TRUE,
    '#maxlength' => 128,
    '#default_value' => $pub_file->path,
  );

  $form['file_type'] = array(
    '#type' => 'select',
    '#title' => t('Response type'),
    '#options' => array(
      'html' => 'text/html',
      'js' => 'text/javascript',
      'json' => 'application/json',
    ),
    '#description' => t('The content type header for this response.'),
    '#required' => TRUE,
    '#default_value' => $pub_file->file_type,
  );

  $form['content'] = array(
    '#type' => 'textarea',
    '#title' => t('Content'),
    '#description' => t('The content of this path.'),
    '#required' => TRUE,
    '#default_value' => $pub_file->content,
  );
}

/**
 * Submit function for our settings form.
 *
 * @see pub_ads_form()
 */
function pub_ads_form_submit($form, &$form_state) {
  ctools_export_load_object_reset('pub_ads_paths');
  variable_set('menu_rebuild_needed', TRUE);
}

/**
 * Make sure we do not add duplicate machine_name.
 */
function pub_ads_file_name_exists($machine_name) {
  return pub_ads_path_load($machine_name);
}
