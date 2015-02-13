<?php

/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'mps_blocks',
  'access' => 'administer mps account',

  // Define the menu item.
  'menu' => array(
    'menu item' => 'mps_blocks',
    'menu prefix' => 'admin/structure',
    'menu title' => 'MPS Blocks',
    'menu description' => 'Create and manage your MPS blocks.',
  ),

  // Specify the class that modifies export list.
  'handler' => array(
    'class' => 'mps_blocks_ui',
    'parent' => 'ctools_export_ui',
    'file' => 'mps.export.class.php',
  ),

  // Define user interface texts.
  'title singular' => t('MPS block'),
  'title plural' => t('MPS blocks'),
  'title singular proper' => t('MPS block'),
  'title plural proper' => t('MPS blocks'),

  // Define the names of the functions that provide the add/edit forms.
  'form' => array(
    'settings' => 'mps_block_form',
    'validate' => 'mps_block_form_validate',
  ),
);

/**
 * Form builder--create a block.
 */
function mps_block_form(&$form, &$form_state) {
  // Make sure that all the necessary files are included even on ajax callbacks.
  form_load_include($form_state, 'inc', 'mps', 'plugins/export_ui/mps.export_ui');
  form_load_include($form_state, 'inc', 'mps', 'mps.admin');

  // Create a default tag object.
  $block = ($form_state['op'] == 'add' ? $form_state['item'] : $form_state['item']->raw);

  // What we refer to as machine_name translates to a "slot" in MPS.  The
  // block_name is just used as a label on the Publisher side.
  $form['block_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Block Name'),
    '#required' => TRUE,
    '#maxlength' => 32,
    '#default_value' => $block->block_name,
    '#description' => t('A human-readable name for the block.'),
  );

  $form['machine_name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Slot Name'),
    '#maxlength' => 32,
    '#default_value' => $block->machine_name,
    '#machine_name' => array(
      'exists' => 'mps_block_name_exists',
      'label' => 'Slot',
      'source' => array('block_name'),
      'replace_pattern' => '[^a-z0-9]+',
      'replace' => '',
    ),
  );

  // Merge the machine_name that way it can tell new from edit.
  $form['machine_name'] += $form['info']['machine_name'];
  unset($form['info']);

  $form['#after_build'][] = 'mps_block_form_after_build';
}

/**
 * Implements hook_after_build().
 */
function mps_block_form_after_build($form, &$form_state) {
  // The default form machine_name doesn't handle empty strings as replacements,
  // so remove it from the list of assigned validation functions.
  $element_validations = $form['machine_name']['#element_validate'];
  for ($i=0; $i < count($element_validations); $i++) {
    if ($element_validations[$i] == 'form_validate_machine_name') {
      unset($form['machine_name']['#element_validate'][$i]);
    }
  }

  $form['machine_name']['#element_validate'][] = 'mps_block_machine_name_validate';

  return $form;
}

/**
 * Form validation for the mps_block form.
 */
function mps_block_form_validate(&$form, &$form_state) {
  if (preg_match('@[^a-zA-Z0-9\/\-_\.\[\]\s]+@', $form_state['values']['block_name'])) {
    form_set_error('name', t('Block Names can only include letters, numbers, hyphens, dashes, periods, brackets and spaces.'));
  }
}

/**
 * Form validation handler for the machine_name.
 *
 * @see mps_block_form_after_build()
 */
function mps_block_machine_name_validate(&$element, &$form_state) {
  // Verify that the machine name contains no disallowed characters.
  if (preg_match('@' . $element['#machine_name']['replace_pattern'] . '@', $element['#value'])) {
    if (!isset($element['#machine_name']['error'])) {
      if ($element['#machine_name']['replace'] == '') {
        form_error($element, t('The machine-readable name must contain only lowercase letters and numbers.'));
      }
    }
    else {
      form_error($element, $element['#machine_name']['error']);
    }
  }

  // Verify that the machine name is unique.
  if ($element['#default_value'] !== $element['#value']) {
    $function = $element['#machine_name']['exists'];
    if ($function($element['#value'], $element, $form_state)) {
      form_error($element, t('The machine-readable name is already in use. It must be unique.'));
    }
  }
}

/**
 * Check if the given machine name is unique in the mps_blocks table.
 */
function mps_block_name_exists($machine_name) {
  $select = db_select('mps_blocks', 'mb');
  $select->addExpression('COUNT(*)');
  $select->condition('mb.machine_name', $machine_name);

  return $select->execute()->fetchField();
}
