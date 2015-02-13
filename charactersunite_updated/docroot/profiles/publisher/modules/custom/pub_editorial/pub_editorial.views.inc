<?php
/**
 * @file
 * The views.inc for pub_editorial.
 */


/**
 * Implements hook_views_data_alter().
 */
function pub_editorial_views_data_alter(&$data) {
  $supported_entity_types = array('node', 'file', 'comment', 'user');

  foreach ($supported_entity_types as $supported_entity_type) {
    $entity_info = entity_get_info($supported_entity_type);

    $data[$entity_info['base table']]['pub_editorial'] = array(
      'title' => t('Operations'),
      'help' => t('Displays operations links for the given entity.'),
      'field' => array(
        'handler' => 'pub_editorial_views_handler_field_operations',
        'no group by' => TRUE,
      ),
      'entity_type' => $supported_entity_type,
      'entity_key' => $entity_info['entity keys']['id'],
    );
  }

  // Handle revisions separately.
  $data['node_revision']['pub_editorial'] = array(
    'title' => t('Operations'),
    'help' => t('Displays operations links for the given revision.'),
    'field' => array(
      'handler' => 'pub_editorial_views_handler_field_revision_operations',
      'no group by' => TRUE,
    ),
  );
}
