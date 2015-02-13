<?php

/**
 * @file
 * Definition of pub_theplatform_views_handler_argument_guid.
 */

/**
 * Basic argument handler to implement guid contextual filtering for
 * thePlatform.
 *
 * @ingroup views_argument_handlers
 */
class pub_theplatform_views_handler_argument_guid extends views_handler_argument_numeric {

  /**
   * Add this filter to the request.
   */
  public function query($group_by = FALSE) {
    $value = $this->value;
    if (!is_array($this->value)) {
      $value = array($this->value);
    }
    foreach ($value as $i => $rid) {
      $this->query->thePlatform->addArg('byGuid', $rid);
    }
  }
}

