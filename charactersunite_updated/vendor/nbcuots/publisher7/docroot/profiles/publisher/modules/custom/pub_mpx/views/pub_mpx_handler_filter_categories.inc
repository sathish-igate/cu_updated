<?php

/*
 * @file pub_mpx_views_handler_filter_categories.inc
 */

/*
 * Handler to provide an exposed filter for MPX video categories.
 */
class pub_mpx_handler_filter_categories extends views_handler_filter {

  function exposed_form(&$form, &$form_state) {
    parent::exposed_form($form, $form_state);

    $default_group = &$this->options['group_info']['default_group'];
    $options = array(
      $default_group => '- Any -',
    );

    // Get all mpx category property and database values and add to the select options.
    $field_mpx_media_categories_info = field_info_field('field_mpx_media_categories');
    $field_mpx_media_categories_table = _field_sql_storage_tablename($field_mpx_media_categories_info);
    $field_mpx_media_categories_column = _field_sql_storage_columnname('field_mpx_media_categories', 'value');

    // Grab property categories that are not overridden.
    $property_select = db_select('mpx_video', 'mpx_video');
    $property_select->fields('mpx_video', array('categories'));
    $property_select->leftJoin($field_mpx_media_categories_table, 'field_data', 'field_data.entity_type = :entity_type AND field_data.entity_id = mpx_video.fid', array(':entity_type' => 'file'));
    $property_select->isNull('field_data.' . $field_mpx_media_categories_column);
    $property_results = $property_select->execute();
    foreach ($property_results as $result) {
      $result_categories = unserialize($result->categories);
      foreach ($result_categories as $category) {
        $options[$category] = $category;
      }
    }

    // Grab all overridden categories.
    $override_results = db_select($field_mpx_media_categories_table, 'c')
      ->fields('c', array($field_mpx_media_categories_column))
      ->execute();
    foreach ($override_results as $result) {
      $options[$result->{$field_mpx_media_categories_column}] = $result->{$field_mpx_media_categories_column};
    }

    asort($options);

    $form['categories']['#type'] = 'select';
    $form['categories']['#multiple'] = $this->options['expose']['multiple'];
    $form['categories']['#options'] = $options;
    $form['categories']['#default_value'] = $default_group;
    $form['categories']['#required'] = $this->options['expose']['required'];
    $form['categories']['#description'] = $this->options['expose']['description'];

    $form['#info']['filter-categories'] = array(
      'operator' => '',
      'value' => 'categories',
      'label' => $this->options['expose']['label'],
      'description' => '',
    );
  }

  function query() {
    $this->ensure_my_table();

    // Join the field_mpx_media_categories data table.
    $field_mpx_media_categories_info = field_info_field('field_mpx_media_categories');
    $field_mpx_media_categories_table = _field_sql_storage_tablename($field_mpx_media_categories_info);
    $field_mpx_media_categories_column = _field_sql_storage_columnname('field_mpx_media_categories', 'value');
    $this->query->add_table($field_mpx_media_categories_table);

    // Set our own where group.
    $where_group_id = $this->query->set_where_group('OR');

    // When we check for a category, we have to keep overrides in mind. So it should return mpx videos that either:
    //   a) do not have an override and there is a match in the serialized property data
    //     OR
    //   b) do have an override
    // This is doing this check for each category that is selected.
    $value = reset($this->value);
    foreach ($this->value as $value) {
      $property_value = '%s:' . str_replace("'", "\\'", strlen($value) . ':"' . $value .'";%');
      $override_value = str_replace("'", "\\'", $value);
      $where_expression = '(mpx_video.categories LIKE \'' . $property_value . '\''
          . ' AND ' . $field_mpx_media_categories_table . '.' . $field_mpx_media_categories_column . ' IS NULL)'
          . ' OR ' . $field_mpx_media_categories_table . '.' . $field_mpx_media_categories_column . ' LIKE \'' . $override_value . '\'';
      $this->query->add_where_expression($where_group_id, $where_expression);
    }
  }
}
