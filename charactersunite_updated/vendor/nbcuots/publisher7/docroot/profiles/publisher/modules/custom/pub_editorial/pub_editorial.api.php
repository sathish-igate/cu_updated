<?php

/**
 * @file
 * API documentation file.
 */

/**
 * Alters the list of links in the pub_editorial operations views field.
 *
 * @param array $links
 *   An array of links to render using theme_links.
 */
function hook_pub_editorial_operations_links_alter(&$links) {
  $node = menu_get_object();
  $links[] = array(
    'title' => t('Clone'),
    'href' => 'node/' . $node->nid . '/clone/' . clone_token_to_arg(),
    'query' => drupal_get_destination(),
  );
}
