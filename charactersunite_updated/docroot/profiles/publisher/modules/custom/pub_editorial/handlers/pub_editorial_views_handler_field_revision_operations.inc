<?php

/**
 * @file
 * Definition of pub_editorial_views_handler_field_revision_operations.
 */

/**
 * A handler to provide proper displays for revision operations.
 *
 * @ingroup views_field_handlers
 */
class pub_editorial_views_handler_field_revision_operations extends pub_editorial_views_handler_field_operations {

  function render($values) {
    $nid = $this->get_value($values, 'node_revision_nid');
    $vid = $this->get_value($values, 'vid');
    $state = $this->get_value($values, 'state_flow_states_state');
    $node = node_load($nid);
    $links = array();

    if (node_access('update', $node) && user_access('revert revisions')) {
      $links[] = array(
        'title' => t('Edit'),
        'href' => 'node/' . $nid . '/revisions/' . $vid . '/edit',
      );
      $links[] = array(
        'title' => t('Revert'),
        'href' => 'node/' . $nid . '/revisions/' . $vid . '/revert',
      );
      $links[] = array(
        'title' => t('Schedule'),
        'href' => 'node/' . $this->get_value($values, 'node_revision_nid') . '/moderation/schedule/add',
        'query' => array('edit[revision_id]' => $this->get_value($values, 'vid')),
      );
    }
    if (node_access('delete', $node) && user_access('delete revisions')) {
      $links[] = array(
        'title' => t('Delete'),
        'href' => 'node/' . $nid . '/revisions/' . $vid . '/delete',
      );
    }

    if ($state == 'published') {
      drupal_add_library('system', 'drupal.ajax');
      ctools_include('modal');
      ctools_include('ajax');
      ctools_modal_add_js();
      $links[] = array(
        'title' => t('Share'),
        'href' => 'node/' . $nid . '/share/nojs',
        'attributes' => array(
          'class' => array('ctools-use-modal'),
        ),
      );
    }

    $output = theme('links__ctools_dropbutton', array('title' => t('operations'), 'links' => $links));

    $this->pub_editorial_css();

    return $output;
  }
}
