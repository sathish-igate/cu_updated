<?php

/**
 * @file
 * Definition of pub_social_views_handler_node_revision_share_link.
 */

/**
 * A handler to provide a node revision share link.
 *
 * @ingroup views_field_handlers
 */
class pub_social_views_handler_node_revision_share_link extends views_handler_field {

  function query() {
    // Do nothing -- to override the parent query.
  }

  function render($values) {
    module_load_include('inc', 'twitter', 'twitter');
    $twitter_is_shareable = array_flip(variable_get('twitter_post_types', array()));
    $facebook_is_shareable = array_flip(variable_get('facebook_post_types', array()));
    if (isset($values->node_node_revision_type)) {
      $node_type = $values->node_node_revision_type;
    }
    elseif (!isset($values->node_node_revision_type)) {
      return '';
    }

    if (isset($values->state_flow_states_state) &&
        isset($values->node_revision_nid) &&
        $values->state_flow_states_state == 'published' &&
        ((isset($twitter_is_shareable[$node_type]) && twitter_load_authenticated_accounts()) || isset($facebook_is_shareable[$node_type]))) {
      ctools_include('modal');
      ctools_include('ajax');
      ctools_modal_add_js();
      $dest = 'node/' . $values->node_revision_nid . '/share/' . 'nojs';

      return ctools_modal_text_button('Share', $dest, 'Share to Social Networks');
    }
    return '';
  }
}
