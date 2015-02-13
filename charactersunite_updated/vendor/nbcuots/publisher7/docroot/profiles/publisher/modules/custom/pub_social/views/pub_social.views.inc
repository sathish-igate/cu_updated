<?php

/**
 * Implements hook_views_data_alter().
 */
function pub_social_views_data_alter(&$data) {
  $data['node_revision']['pub_social_share_link'] = array(
    'title' => t('Publisher Share Link'),
    'help' => t('Displays a link to share content.'),
    'field' => array(
      'handler' => 'pub_social_views_handler_node_revision_share_link',
      'no group by' => TRUE,
    ),
  );
}

/**
 * Implements hook_views_handlers().
 */
function pub_social_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'pub_social') . '/views/handlers',
    ),
    'handlers' => array(
      'pub_social_views_handler_node_revision_share_link' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}
