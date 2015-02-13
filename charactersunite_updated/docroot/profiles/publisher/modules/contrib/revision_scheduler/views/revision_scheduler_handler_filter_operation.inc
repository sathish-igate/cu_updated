<?php

/**
 * @file
 * Filter based on operation.
 */
class revision_scheduler_handler_filter_operation extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $revision_entity_type = FALSE;

      $this->value_title = t('Action');
      foreach (entity_get_info() as $entity_type => $info) {
        if ($this->view->base_table == $info['base table']) {
          $revision_entity_type = $entity_type;
          break;
        }
      }

      if ($revision_entity_type) {
        $revision_options = revision_scheduler_entity_revision_operation_get_info($revision_entity_type);
        $options = array();
        foreach ($revision_options as $key => $option) {
          $options[$key] = $option['label'];
        }
        $this->value_options = $options;
      }
    }
  }
}

