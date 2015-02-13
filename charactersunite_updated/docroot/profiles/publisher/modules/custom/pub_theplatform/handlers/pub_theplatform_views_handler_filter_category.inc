<?php

/*
 * Filter handler to provide simple filter for thePlatform categories.
 */
class pub_theplatform_views_handler_filter_category extends views_handler_filter {
  /**
   * Provide the form for choosing a category.
   */
  public function value_form(&$form, &$form_state) {
    // Get the categories that exist in our feed.
    $theP = new pubThePlatformAPIRequest(variable_get('theplatform_feed_url', ''));
    $categories = $theP->getCategories()->addField('plcategory$fullTitle')->execute();

    // Make them options.
    $options = array('' => 'Any');
    foreach ($categories as $c) {
      $options[$c->{'plcategory$fullTitle'}] = $c->{'plcategory$fullTitle'};
    }

    $form['value'] = array(
      '#type' => 'select',
      '#title' => t('Category'),
      '#default_value' => (!empty($this->value)) ? $this->value : '',
      '#options' => $options,
    );
    if (!empty($form_state['exposed'])) {
      $identifier = $this->options['expose']['identifier'];
      if (!isset($form_state['input'][$identifier])) {
        $form_state['input'][$identifier] = $this->value;
      }
    }
  }

  /**
   * Provide simple equality operator.
   */
  public function operator_options() {
    return array(
      'is' => t('Is'),
    );
  }

  /**
   * Add this filter to the request.
   */
  public function query() {
    if (is_array($this->value)) {
      $this->value = implode(',', $this->value);
    }
    if (strlen($this->value) > 0) {
      $this->query->thePlatform->addArg('byCategories', $this->value);
    }
  }
}
