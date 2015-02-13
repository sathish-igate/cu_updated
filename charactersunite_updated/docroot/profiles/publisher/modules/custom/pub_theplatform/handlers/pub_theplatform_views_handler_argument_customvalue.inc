<?php

/**
 * @file
 * Definition of pub_theplatform_views_handler_argument_customvalue.
 */

/**
 * Basic argument handler to implement custom value contextual filtering for
 * thePlatform.
 *
 * @ingroup views_argument_handlers
 */
class pub_theplatform_views_handler_argument_customvalue extends views_handler_argument_string {
  /**
   * Add this filter to the request.
   */
  public function query($group_by = FALSE) {
    $value = isset($this->options['default_argument_options']['argument']) ? $this->options['default_argument_options']['argument'] : 'true';

    list(, $field) = explode('_', $this->options['id'], 2);

    $this->query->thePlatform->addArg('byCustomValue', '{' . $field . '}{' . $value . '}');
  }
}

