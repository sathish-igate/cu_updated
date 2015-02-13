<?php

/**
 * @file Simple EXIF/IPTC Admin.
 */
use PHPExif\Exif;

/**
 * Simple Exif field mapping form.
 */
function simple_exif_mappings($form, $form_state) {

  $default_values = variable_get('simple_exif_mappings', array());
  $mappings = _simple_exif_fields();

  // Load mappable fields.
  $fields = field_info_instances('file', 'image');

  foreach($mappings as $key => $exif_field){
    $select_fields[$key] = $exif_field['title'];
  }
  asort($select_fields);

  // Make sure _none shows up first.
  $select_fields = array('_none' => 'none') + $select_fields;

  $form['mappings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Field Mapping: Image Field -> IPTC/EXIF'),
    '#tree' => TRUE,
  );

  foreach ($fields as $field => $field_data) {
    $form['mappings'][$field] = array(
      '#type' => 'select',
      '#title' => $field_data['label'],
      '#options' => $select_fields,
      '#default_value' => (isset($default_values[$field]) ? $default_values[$field] : 'none'),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save'
  );

  return $form;
}

/**
 * Submit function for simple_exif_mappings().
 *
 * @see simple_exif_mappings().
 */
function simple_exif_mappings_submit($form, $form_state) {
  variable_set('simple_exif_mappings', $form_state['values']['mappings']);
}

