<?php

/**
 * Implements hook_views_data_alter.
 */
function pub_relationships_tv_enhanced_views_data_alter(&$data) {
  $fields = field_read_fields(array('type' => 'pub_tv_relationship_field'));
  foreach ($fields as $field) {
    $table = _field_sql_storage_tablename($field);
    foreach ($field['columns'] as $column_name => $attributes) {
      $column = _field_sql_storage_columnname($field['field_name'], $column_name);
      $data[$table][$column]['relationship'] = array(
        'base' => 'node',
        'base field' => 'nid',
        'handler' => 'views_handler_relationship',
        'label' => t('TV '.ucfirst($column_name)),
      );
    }
  }
}
