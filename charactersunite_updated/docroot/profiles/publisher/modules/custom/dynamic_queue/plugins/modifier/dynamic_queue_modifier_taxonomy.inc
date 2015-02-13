<?php

/**
 * @file
 * Modifier plugin for filtering by taxonomy.
 */

$plugin = array(
  'title' => t('Dynamic Queue Modifier Taxonomy'),
  'handler' => array(
    'class' => 'DynamicQueueModifierTaxonomy',
    'file' => 'dynamic_queue_modifier_taxonomy.inc',
  ),
);

/**
 * Class DynamicQueueModifierTaxonomy.
 */
class DynamicQueueModifierTaxonomy extends DynamicQueueModifierBase implements DynamicQueueModifierInterface {
  /**
   * {@inheritdoc}
   */
  public static function getType() {
    return DynamicQueueModifierBase::MODIFIER_FILTER;
  }

  /**
   * {@inheritdoc}
   */
  public static function alterForm(&$form, $settings, $DynamicQueue, $op) {
    $dynamic_queue_type = dynamic_queue_type_load($DynamicQueue->type);

    $form['#attached']['css'][] = drupal_get_path('module', 'dynamic_queue') . '/css/dynamic_queue.css';
    $form['terms'] = array();

    $fields = array();
    if (isset($dynamic_queue_type->settings['taxonomy']['fields'])) {
      $taxonomy_fields = $dynamic_queue_type->settings['taxonomy']['fields'];
      foreach ($taxonomy_fields as $setting) {
        $fields = array_merge($fields, array_filter($setting));
      }
    }

    $target_bundles = $dynamic_queue_type->settings['allowed_bundles']['target_bundles'];
    $bundles = array();
    $bundles = array_merge($bundles, array_filter($target_bundles));
    $fields = self::getFilterFieldsByBundles($fields, $bundles, $dynamic_queue_type->entity_type);

    $dynamic_queue_terms = array();
    if (isset($DynamicQueue->settings['terms'])) {
      $dynamic_queue_terms = $DynamicQueue->settings['terms'];
    }

    // Grab information about the bundles, so we can determine the fields that
    // use them and their labels.
    $field_bundle_map = field_info_field_map();
    $bundle_info = entity_get_info($dynamic_queue_type->entity_type);

    foreach ($fields as $field_name => $relevant_field) {
      $options = self::getTermsForField($field_name);

      // Get the bundles that use this field and the bundles' labels.
      $bundle_labels_list = '';
      if (isset($field_bundle_map[$field_name]['bundles'][$dynamic_queue_type->entity_type])) {
        $field_bundles = $field_bundle_map[$field_name]['bundles'][$dynamic_queue_type->entity_type];
        $bundle_labels = array();
        foreach ($field_bundles as $bundle_name) {
          if (isset($bundle_info['bundles'][$bundle_name])) {
            $bundle_labels[] = $bundle_info['bundles'][$bundle_name]['label'];
          }
        }

        if (count($bundle_labels) > 0) {
          $bundle_labels_list = ' (' . implode(', ', $bundle_labels) . ')';
        }
      }

      // If this field isn't relevant to the target bundles, disable it.
      if ($relevant_field) {
        if (isset($dynamic_queue_terms[$field_name])) {
          $default_values = array_values($dynamic_queue_terms[$field_name]);
        }
        else {
          $default_values = array();
        }

        $form['terms'][$field_name] = array(
          '#title' => t('Taxonomy filter for <i>!field_name</i>!field_bundles', array('!field_name' => $field_name, '!field_bundles' => $bundle_labels_list)),
          '#type' => 'select',
          '#multiple' => TRUE,
          '#options' => $options,
          '#default_value' => $default_values,
          '#size' => min(8, count($options)),
          '#attributes' => array(
            'class' => array('dynamic-queue-taxonomy-term-list'),
          ),
        );
      }
      else {
        $form['terms'][$field_name] = array(
          '#title' => t('Taxonomy filter for <i>!field_name</i>!field_bundles', array('!field_name' => $field_name, '!field_bundles' => $bundle_labels_list)),
          '#type' => 'select',
          '#options' => $options,
          '#disabled' => TRUE,
          '#description' => t("This field isn't applicable to your chosen target bundles."),
          '#attributes' => array(
            'class' => array('dynamic-queue-taxonomy-term-list'),
          ),
        );
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public static function alterQuery($query, $settings) {
    if (!isset($settings['terms'])) {
      return $query;
    }

    $terms = array_filter($settings['terms']);
    foreach ($terms as $filtered_field => $selected_terms) {
      if (count($selected_terms) > 0) {
        $query->fieldCondition($filtered_field, 'tid', $selected_terms, 'IN');
      }
    }

    return $query;
  }

  /**
   * {@inheritdoc}
   */
  public static function getName() {
    return t('Taxonomy');
  }

  /**
   * Get the relevant taxonomy terms for a given field.
   *
   * @param string $field_name
   *   The field to retrieve taxonomy terms for.
   *
   * @return array
   *   A list of terms.
   */
  protected static function getTermsForField($field_name) {
    $field_info = field_info_field($field_name);

    if ($field_info['module'] == 'taxonomy') {

      $terms = array();
      $taxonomy_terms = taxonomy_allowed_values($field_info);
      foreach ($taxonomy_terms as $tid => $term_title) {
        $terms[$tid] = $term_title;
      }
    }

    return $terms;
  }

  /**
   * Determine which taxonomy fields are relevant for the bundles chosen.
   *
   * @param array $chosen_fields
   *   A list of fields to search on.
   * @param array $bundles
   *   A list of bundles to search.
   * @param string $entity_type
   *   The entity type for the bundles.
   *
   * @return array
   *   A list of chosen fields that are found in the supplied bundles.
   */
  protected static function getFilterFieldsByBundles($chosen_fields, $bundles, $entity_type) {
    $fields = array();
    // Assign defaults.
    foreach ($chosen_fields as $field) {
      $fields[$field] = FALSE;
    }

    $bundle_fields = array();
    foreach ($bundles as $bundle_name) {
      $bundle_fields = array_merge($bundle_fields, array_keys(field_info_instances($entity_type, $bundle_name)));
    }

    $active_fields = array_intersect($chosen_fields, $bundle_fields);
    foreach ($active_fields as $field) {
      $fields[$field] = TRUE;
    }

    // Sort so inactive fields appear later in list.
    arsort($fields);
    return $fields;
  }
}
