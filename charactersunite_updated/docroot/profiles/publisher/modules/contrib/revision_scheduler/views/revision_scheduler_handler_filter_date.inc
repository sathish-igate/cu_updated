<?php

/**
 * @file
 * Contains the date filter handler.
 */
class revision_scheduler_handler_filter_date extends views_handler_filter_date {
  /**
   * Add a type selector to the value form
   */
  function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);
    $form['value']['type']['#options']['simple'] = t("Simple such as '0' for when a date has not been added yet.");
  }

  function options_validate(&$form, &$form_state) {
    if ($form_state['values']['options']['value']['type'] == 'simple') {
      if (!is_numeric($form_state['values']['options']['value']['value'])) {
        form_error($form['value'], t('Enter only valid numeric values.'));
      }
    }
    else {
      parent::options_validate($form, $form_state);
    }
  }
}
