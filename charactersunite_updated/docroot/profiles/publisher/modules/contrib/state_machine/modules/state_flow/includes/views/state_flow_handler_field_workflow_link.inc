<?php

/**
 * @file
 * Legacy Views handler. This might be removed.
 */

/**
 * Views field handler to display a link to the workflow page for the node.
 *
 * @todo, this handler is currently not referenced in state_flow.views.inc
 */
class state_flow_handler_field_workflow_link extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function query() {
    // Override this method.
  }

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    if (($node = node_load($values->nid)) && state_flow_menu_node_access($node)) {
      return l(t('Workflow'), 'node/' . $values->nid . '/workflow');
    }
  }
}
