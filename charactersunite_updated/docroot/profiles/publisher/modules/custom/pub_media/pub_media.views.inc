<?php

/**
 * Implements hook_views_data_alter().
 */
function pub_media_views_data_alter(&$data) {
  $data['views_entity_node']['pub_media'] = array(
    'title' => t('Operations (Media)'),
    'help' => t('Displays operations links for media entities.'),
    'field' => array(
        'handler' => 'pub_media_views_handler_field_operations',
        'no group by' => TRUE,
      ),
  );
}
