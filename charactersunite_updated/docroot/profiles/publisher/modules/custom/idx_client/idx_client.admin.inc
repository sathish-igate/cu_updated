<?php
/**
 * @file
 * IDX admin functionality.
 */

/**
 * Form builder for the IDX settings form.
 */
function idx_client_admin_form($form, &$form_state) {
  drupal_set_title(t('IDX Configuration Settings'));

  $form[IDX_CLIENT_API_URL_FIELD] = array(
    '#type' => 'textfield',
    '#title' => t('IDX API URL'),
    '#required' => TRUE,
    '#default_value' => variable_get(IDX_CLIENT_API_URL_FIELD, 'https://stage.idxapi.nbcuni.com/'),
  );
  $form[IDX_CLIENT_API_KEY_FIELD] = array(
    '#type' => 'textfield',
    '#title' => t('IDX API Key'),
    '#required' => TRUE,
    '#default_value' => variable_get(IDX_CLIENT_API_KEY_FIELD),
  );
  $form[IDX_CLIENT_API_BRAND_ID_FIELD] = array(
    '#type' => 'textfield',
    '#title' => t('IDX Brand Id'),
    '#required' => TRUE,
    '#default_value' => variable_get(IDX_CLIENT_API_BRAND_ID_FIELD),
  );

  $form = system_settings_form($form);

  return $form;
}
