<?php

/**
 * @file
 * Class API and helper for DynamicQueueEntityType.
 */

/**
 * Class DynamicQueueEntityType.
 */
class DynamicQueueEntityType extends Entity {
  public $label;
  public $type;
  public $entity_type = 'node';
  public $is_new = FALSE;
  public $cache_lifetime = 86400;

  /**
   * Returns the default label for the DynamicQueueType.
   *
   * @return string
   *   The label of this Dynamic Queue Entity Type.
   */
  protected function defaultLabel() {
    return $this->label;
  }

  /**
   * Creates a DynamicQueueEntityType object.
   *
   * @param array $values
   *   An array of values that define the Dyanamic Queue type.
   *
   * @return DynamicQueueEntityType
   *   The Dynamic Queue type entity object.
   */
  public function create(array $values = array()) {
    $values += array(
      'label' => '',
    );
    return parent::create($values);
  }

  /**
   * Saves the DynamicQueueEntityType object.
   */
  public function save() {
    if (is_numeric($this->type)) {
      throw new Exception('Type cannot be numeric');
    }
    parent::save();
  }

  /**
   * Gets a list of bundle options allowed for this DynamicQueueEntityType.
   *
   * This is typically used to populate a select box or a list of checkboxes.
   *
   * @return array
   *   Array of allowed bundles.
   */
  public function get_allowed_bundle_options() {
    // Get all bundles.
    $entity_info = entity_get_info();
    $bundles = array();
    foreach ($entity_info[$this->entity_type]['bundles'] as $bundle_name => $bundle_info) {
      $bundles[$bundle_name] = $bundle_info['label'];
    }

    // Filter and show only allowed bundles.
    $allowed = array_filter($this->settings['allowed_bundles']['target_bundles']);
    if (count($allowed)) {
      $bundles = array_intersect_key($bundles, $allowed);
    }

    return $bundles;
  }
}

/**
 * Loads a DynamicQueueEntityType object by type name.
 *
 * @param string $type
 *   The name of the dynamic queue type to load.
 *
 * @return DynamicQueueEntityType[]
 *   An array containing the DynamicQueueEntityType object.
 *
 * @see dynamic_queue_type_get_types()
 */
function dynamic_queue_type_load($type) {
  return dynamic_queue_type_get_types($type);
}

/**
 * Loads a DynamicQueueEntityType from the db by name.
 *
 * @param string $name
 *   (optional) Name of the dynamic queue type to load.
 *   If not specified returns all dynamic queue types.
 *
 * @return DynamicQueueEntityType[]
 *   An array of DynamicQueueEntityType objects.
 *
 * @see dynamic_queue_type_load()
 */
function dynamic_queue_type_get_types($name = NULL) {
  $types = entity_load_multiple_by_name('dynamic_queue_type', isset($name) ? array($name) : FALSE);
  return isset($name) ? reset($types) : $types;
}

/**
 * Form constructor for dynamic_queue_type_form().
 *
 * @see dynamic_queue_type_form_submit()
 * @see dynamic_queue_type_form_validate()
 */
function dynamic_queue_type_form($form, $form_state, $DynamicQueueEntityType, $op = 'edit') {

  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $DynamicQueueEntityType->label,
    '#description' => t('The human-readable name of this dynamic queue type. This text will be displayed as part of the list on the Add new dynamic queue page. It is recommended that this name begin with a capital letter and contain only letters, numbers, and spaces. This name must be unique.'),
  );

  $form['type'] = array(
    '#type' => 'machine_name',
    '#title' => t('machine_name'),
    '#maxlength' => 32,
    '#default_value' => $DynamicQueueEntityType->type,
    '#machine_name' => array(
      'exists' => 'dynamic_queue_type_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this dynamic queue type. It must only contain lowercase letters, numbers, and underscores. This name will be used for constructing the URL of the Add new dynamic queue page, in which underscores will be converted into hyphens.'),
  );

  // Get valid target entity types.
  $entity_info = entity_get_info();
  unset($entity_info['dynamic_queue'], $entity_info['dynamic_queue_type']);

  $entity_types = array();
  foreach ($entity_info as $entity_type => $info) {
    $entity_types[$entity_type] = $info['label'];
  }
  $form['entity_type'] = array(
    '#title' => t('Entity type'),
    '#type' => 'select',
    '#options' => $entity_types,
    '#default_value' => $DynamicQueueEntityType->entity_type,
    '#required' => TRUE,
    '#disabled' => $DynamicQueueEntityType->is_new ? FALSE : TRUE,
    '#ajax' => array(
      'callback' => 'dynamic_queue_type_entity_type_callback',
    ),
  );

  $period = drupal_map_assoc(array(
      60,
      180,
      300,
      600,
      900,
      1800,
      2700,
      3600,
      10800,
      21600,
      32400,
      43200,
      86400,
    ),
    'format_interval');
  $form['cache_lifetime'] = array(
    '#title' => t('Cache lifetime'),
    '#type' => 'select',
    '#options' => $period,
    '#default_value' => $DynamicQueueEntityType->cache_lifetime,
    '#description' => t('Cached Dynamic Queues will not be re-created until at least this much time has elapsed.'),
  );

  $form['settings'] = array(
    '#type' => 'vertical_tabs',
    '#tree' => TRUE,
  );

  $entity_type = !empty($form_state['values']['entity_type']) ? $form_state['values']['entity_type'] : $DynamicQueueEntityType->entity_type;
  $bundles = array();
  foreach ($entity_info[$entity_type]['bundles'] as $bundle_name => $bundle_info) {
    $bundles[$bundle_name] = $bundle_info['label'];
  }

  $form['settings']['allowed_bundles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Allowed bundles'),
    '#collapsible' => TRUE,
  );

  $form['settings']['allowed_bundles']['target_bundles'] = array(
    '#type' => 'checkboxes',
    '#title' => $entity_type == 'node' ? t('Content types') : t('Bundles'),
    '#prefix' => '<div id="dynamic-queue-target-bundles">',
    '#suffix' => '</div>',
    '#options' => $bundles,
    '#default_value' => !empty($DynamicQueueEntityType->settings['allowed_bundles']['target_bundles']) ? $DynamicQueueEntityType->settings['allowed_bundles']['target_bundles'] : array(),
    '#multiple' => TRUE,
    '#description' => t('The bundles of the entity type that can be referenced. Optional, leave empty for all bundles.'),
  );

  // Display fields by their taxonomy vocabularies.
  $form['settings']['taxonomy'] = array(
    '#type' => 'fieldset',
    '#title' => t('Taxonomy filters'),
    '#collapsible' => TRUE,
  );
  $form['settings']['taxonomy']['fields'] = array(
    '#prefix' => '<div id="dynamic-queue-taxonomy-fields">',
    '#suffix' => '</div>',
  );

  $fields_by_vocabulary = dynamic_queue_get_taxonomy_fields_by_vocabulary($entity_type, $bundles);

  if (count($fields_by_vocabulary) > 0) {
    $field_taxonomy_description = t('Choose the fields that will be filterable by their respective taxonomies.');
  }
  else {
    $field_taxonomy_description = t("This entity type doesn't have any fields to filter on by taxonomy.");
  }
  $form['settings']['taxonomy']['fields']['description'] = array(
    '#markup' => '<p>' . $field_taxonomy_description . '</p>',
  );

  foreach ($fields_by_vocabulary as $vocabulary_machine_name => $fields) {
    $vocab = taxonomy_vocabulary_machine_name_load($vocabulary_machine_name);

    if (!$DynamicQueueEntityType->is_new && isset($DynamicQueueEntityType->settings['taxonomy']['fields'])) {
      $settings_taxonomy_fields = $DynamicQueueEntityType->settings['taxonomy']['fields'];

      $default_values = array();
      // Grab the previously selected fields for these taxonomies.
      foreach ($settings_taxonomy_fields as $taxonomy_fields) {
        $default_values = array_merge($default_values, array_filter($taxonomy_fields));
      }
    }
    else {
      $default_values = array();
    }

    $form['settings']['taxonomy']['fields'][$vocabulary_machine_name] = array(
      '#type' => 'checkboxes',
      '#title' => $vocab->name,
      '#options' => $fields,
      '#default_value' => $default_values,
    );
  }

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 20,
  );

  return $form;
}

/**
 * AJAX callback to rebuild the target_bundles options.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The form_state array.
 *
 * @return array
 *   A render array representing the target bundles dropdown.
 *
 * @see dynamic_queue_type_form()
 */
function dynamic_queue_type_entity_type_callback($form, $form_state) {
  $commands = array();
  $commands[] = ajax_command_replace('#dynamic-queue-target-bundles', drupal_render($form['settings']['allowed_bundles']['target_bundles']));
  $commands[] = ajax_command_replace('#dynamic-queue-taxonomy-fields', drupal_render($form['settings']['taxonomy']['fields']));
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Form validation handler for dynamic_queue_type_form().
 *
 * @see dynamic_queue_type_form()
 * @see dynamic_queue_type_form_submit()
 */
function dynamic_queue_type_form_validate($form, &$form_state) {
  if (is_numeric($form_state['values']['type'])) {
    if (is_numeric($form_state['values']['label'])) {
      form_set_error('label', t('Name cannot be a number. It is recommended that this name begin with a capital letter and contain only letters, numbers, and spaces.'));
    }
    else {
      form_set_error('type', t('Machine name cannot be a number. It must contain lowercase letters and optionally numbers and underscores.'));
    }
  }
}

/**
 * Form submission handler for dynamic_queue_type_form().
 *
 * @see dynamic_queue_type_form()
 * @see dynamic_queue_type_form_validate()
 */
function dynamic_queue_type_form_submit(&$form, &$form_state) {
  // Remove unwanted data before saving.
  unset($form_state['values']['settings']['settings__active_tab']);

  // Create the object and save.
  $DynamicQueueEntityType = entity_ui_form_submit_build_entity($form, $form_state);
  $DynamicQueueEntityType->save();

  $form_state['redirect'] = 'admin/structure/dynamic-queue';
}

/**
 * Gets taxonomy fields for dynamic queue filter.
 *
 * @param string $entity_type
 *   The target entity type for the dynamic queue.
 * @param array $bundles
 *   The target bundles for the dynamic queue.
 *
 * @return array
 *   An array of taxonomy fields keyed by taxonomy machine name.
 */
function dynamic_queue_get_taxonomy_fields_by_vocabulary($entity_type, $bundles) {
  $vocabularies = taxonomy_vocabulary_get_names();
  $taxonomy_fields = array();

  foreach ($bundles as $bundle_name => $bundle) {
    $fields = field_info_instances($entity_type, $bundle_name);

    foreach ($fields as $field_name => $field) {
      $field_info = field_info_field($field_name);

      if (isset($field_info['module']) && $field_info['module'] == 'taxonomy') {
        $vocabulary = $field_info['settings']['allowed_values'][0]['vocabulary'];

        if (isset($vocabularies[$vocabulary]->vid)) {
          // Only include in the list if the vocabulary has some actual terms.
          $number_of_terms = db_query('SELECT count(*) FROM taxonomy_term_data WHERE vid = :vid', array(':vid' => $vocabularies[$vocabulary]->vid))->fetchField();

          if ($number_of_terms > 0) {
            if (!isset($taxonomy_fields[$vocabulary])) {
              $taxonomy_fields[$vocabulary] = array();
            }

            $taxonomy_fields[$vocabulary][$field_name] = $field_name;
          }
        }
      }
    }
  }

  return $taxonomy_fields;
}
