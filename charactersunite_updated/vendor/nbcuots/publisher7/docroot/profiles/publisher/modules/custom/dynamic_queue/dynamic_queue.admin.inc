<?php

/**
 * @file
 * CRUD functions for Dynamic Queue.
 */

/**
 * Class DynamicQueueEntityUIController.
 */
class DynamicQueueEntityUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   *
   * Set up callbacks for each dynamic queue type.
   */
  public function hook_menu() {

    // Lets get the default menu items.
    $items = parent::hook_menu();

    // We do not want a generic add dynamic queue type page.
    unset($items[$this->path . '/add']);

    // Fix the menu so it appears in Content admin menu.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    $items[$this->path . '/list'] = array(
      'title' => 'List',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );

    // Fix tabs for View, Edit, Revisions, Schedule etc.
    $newpath = 'dynamic-queue/%dynamic_queue';
    $items[$newpath . '/edit'] = array(
      'title' => 'Edit',
      'page callback' => 'entity_ui_get_form',
      'page arguments' => array('dynamic_queue', 1),
      'access callback' => 'dynamic_queue_access',
      'access arguments' => array('edit', 1),
      'type' => MENU_LOCAL_TASK,
      'tab_parent' => 'dynamic-queue/%',
      'tab_root' => 'dynamic-queue/%',
      'weight' => 2,
    );
    unset($items[$this->path . '/manage/%entity_object']);

    $items[$newpath . '/clone'] = array(
      'title' => 'Clone',
      'page callback' => 'entity_ui_get_form',
      'page arguments' => array('dynamic_queue', 1, 'clone'),
      'access callback' => 'dynamic_queue_access',
      'access arguments' => array('create', 1),
      'type' => MENU_CALLBACK,
    );
    unset($items[$this->path . '/manage/%entity_object/clone']);

    $items[$newpath . '/%'] = array(
      'page callback' => 'drupal_get_form',
      'page arguments' => array(
        $this->entityType . '_operation_form',
        $this->entityType,
        1,
        2,
      ),
      'access callback' => 'dynamic_queue_access',
      'access arguments' => array('delete', 1),
      'file' => 'includes/entity.ui.inc',
    );
    unset($items[$this->path . '/manage/%entity_object/%']);

    // We need one add page per dynamic queue type.
    foreach (dynamic_queue_type_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add @entity',
        'title arguments' => array('@entity' => $type->label),
        'page callback' => 'entity_ui_get_form',
        'page arguments' => array($this->entityType, NULL, 'add'),
        'access callback' => 'entity_access',
        'access arguments' => array('create', $this->entityType),
        'type' => MENU_LOCAL_ACTION,
      );
    }

    // Menu definition for viewing a dynamic queue.
    $items['dynamic-queue/%dynamic_queue'] = array(
      'access arguments' => array('view', 1),
      'access callback' => 'dynamic_queue_access',
      'page callback' => 'dynamic_queue_render_page',
      'page arguments' => array(1),
      'title callback' => 'dynamic_queue_get_title',
      'title arguments' => array(1),
      'type' => MENU_NORMAL_ITEM,
    );

    $items['dynamic-queue/%dynamic_queue/view'] = array(
      'title' => 'View',
      'type' => MENU_DEFAULT_LOCAL_TASK,
    );

    // Menu definitions for revisions.
    $items['dynamic-queue/view/%dynamic_queue'] = array(
      'title' => 'View Dynamic Queue',
      'access arguments' => array('view', 2),
      'access callback' => 'dynamic_queue_access',
      'page callback' => 'dynamic_queue_entity_render',
      'page arguments' => array(2),
    );
    $items['dynamic-queue/%dynamic_queue/revisions'] = array(
      'access arguments' => array('edit', 1),
      'access callback' => 'dynamic_queue_access',
      'page callback' => 'dynamic_queue_revision_redirect',
      'page arguments' => array(1),
    );
    $items['dynamic-queue/%/revisions/%/view'] = array(
      'title' => 'View Dynamic Queue revision',
      'access arguments' => array('view', 1),
      'access callback' => 'dynamic_queue_access',
      'page callback' => 'dynamic_queue_entity_render',
      'page arguments' => array(1, 3),
    );
    $items['dynamic-queue/%/revisions/%/edit'] = array(
      'title' => 'Edit',
      'access arguments' => array('edit', 1),
      'access callback' => 'dynamic_queue_access',
      'page callback' => 'dynamic_queue_revision_edit',
      'page arguments' => array(1, 3),
    );
    $items['dynamic-queue/%/revisions/%/delete'] = array(
      'title' => 'Delete',
      'access arguments' => array('delete', 1),
      'access callback' => 'dynamic_queue_access',
      'page callback' => 'drupal_get_form',
      'page arguments' => array(
        'dynamic_queue_confirm_delete_revision_form',
        1,
        3,
      ),
    );
    return $items;
  }
}

/**
 * Form constructor for Dynamic Queue form.
 *
 * @see dynamic_queue_form_submit()
 */
function dynamic_queue_form($form, &$form_state, $DynamicQueueEntity, $op) {

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
    '#default_value' => $DynamicQueueEntity->title,
    '#weight' => -10,
  );

  $DynamicQueueType = dynamic_queue_type_get_types($DynamicQueueEntity->type);

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#tree' => TRUE,
  );

  $form['settings']['target_bundles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Target bundles'),
    '#options' => $DynamicQueueType->get_allowed_bundle_options(),
    '#default_value' => isset($DynamicQueueEntity->settings['target_bundles']) ? $DynamicQueueEntity->settings['target_bundles'] : array(),
    '#required' => TRUE,
  );

  // Allow plugins to modify the form.
  ctools_include('plugins');
  $sort_options = array();
  $plugins = dynamic_queue_get_modifiers();
  foreach ($plugins as $plugin) {
    $class_name = ctools_plugin_get_class($plugin, 'handler');
    $class = new $class_name();
    if ($class->getType() == DynamicQueueModifierBase::MODIFIER_SORT) {
      $sort_options[$plugin['name']] = $class->getName();
    }
    else {
      $class->alterForm($form['settings'], $DynamicQueueEntity->settings, $DynamicQueueEntity, $op);
    }
  }
  if (!empty($sort_options)) {
    $form['settings']['sort'] = array(
      '#type' => 'radios',
      '#title' => t('Sort by'),
      '#options' => $sort_options,
      '#default_value' => isset($DynamicQueueEntity->settings['sort']) ? $DynamicQueueEntity->settings['sort'] : NULL,
      '#required' => TRUE,
    );
  }

  $form['settings']['pager'] = array(
    '#type' => 'numberfield',
    '#title' => t('Items per page'),
    '#default_value' => isset($DynamicQueueEntity->settings['pager']) ? $DynamicQueueEntity->settings['pager'] : '10',
    '#min' => 1,
    '#max' => 20,
    '#description' => t('Limit the number of items per page.'),
  );

  $form['settings']['limit'] = array(
    '#type' => 'numberfield',
    '#title' => t('Limit total'),
    '#default_value' => isset($DynamicQueueEntity->settings['limit']) ? $DynamicQueueEntity->settings['limit'] : '10',
    '#min' => 0,
    '#max' => 20,
    '#description' => t('Limit the total number of items in the queue. Set 0 for no limit.'),
  );

  // Publishing options.
  $form['options'] = array(
    '#type' => 'vertical_tabs',
    '#weight' => 99,
  );

  $form['options']['publishing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Publishing Options'),
  );

  $form['options']['publishing']['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Published'),
    '#default_value' => $DynamicQueueEntity->status,
  );

  $form['options']['publishing']['revision']['is_new_revision'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create new revision'),
    '#default_value' => $DynamicQueueEntity->default_revision,
    '#id' => 'edit-revision',
  );

  if ($DynamicQueueEntity->is_new === TRUE) {
    // On new Entities, hide the checkbox and always make a new revision.
    $form['options']['publishing']['revision']['#access'] = FALSE;
    $form['default_revision'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );
  }
  else {
    $form['options']['publishing']['revision']['default_revision'] = array(
      '#type' => 'checkbox',
      '#title' => t('Set Revision as default'),
      '#default_value' => $DynamicQueueEntity->isDefaultRevision(),
      '#states' => array(
        // Hide if the option above is disabled, to avoid potential data loss.
        'invisible' => array(
          ':input[name="is_new_revision"]' => array('checked' => FALSE),
        ),
      ),
    );
  }

  field_attach_form('dynamic_queue', $DynamicQueueEntity, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save Dynamic Queue'),
      '#weight' => 20,
    ),
  );

  return $form;
}

/**
 * Form submission handler for dynamic_queue_form().
 *
 * @see dynamic_queue_form()
 */
function dynamic_queue_form_submit($form, &$form_state) {

  // Build the dynamic queue from submitted values.
  $DynamicQueueEntity = $form_state['dynamic_queue'];
  $DynamicQueueType = dynamic_queue_type_get_types($DynamicQueueEntity->type);
  $form_state['values']['settings']['entity_type'] = $DynamicQueueType->entity_type;
  entity_form_submit_build_entity('dynamic_queue', $DynamicQueueEntity, $form, $form_state);

  // Save the dynamic queue.
  $DynamicQueueEntity->save();

  // Redirect user back to administration page.
  $form_state['redirect'] = 'dynamic-queue/' . $DynamicQueueEntity->dqid;
}


/**
 * Title callback for dynamic queue.
 *
 * @param DynamicQueueEntity $dynamic_queue_entity
 *   The Dynamic Queue entity object.
 *
 * @return string
 *   The title of the Dynamic Queue entity.
 *
 * @see DynamicQueueEntityUIController::hook_menu()
 */
function dynamic_queue_get_title($dynamic_queue_entity) {
  return isset($dynamic_queue_entity->title) ? $dynamic_queue_entity->title : t('Dynamic Queue');
}

/**
 * Renders the dynamic queue.
 *
 * @param DynamicQueueEntity $dynamic_queue_entity
 *   The dynamic queue entity to render.
 * @param int $revision_id
 *   The particular revision of the dynamic queue entity to render.
 * @param string $view_mode
 *   (optional) The view mode to use when rendering.
 *
 * @return array
 *   A render array of entities in the dynamic queue.
 */
function dynamic_queue_render($dynamic_queue_entity, $revision_id = NULL, $view_mode = 'default') {
  return entity_view('dynamic_queue', array($dynamic_queue_entity), $view_mode);
}

/**
 * Retrieves entities in this dynamic queue.
 *
 * @param DynamicQueueEntity $dynamic_queue_entity
 *   The dynamic queue entity to retrieve entities for.
 * @param int $revision_id
 *   The particular revision of the dynamic queue entity.
 *
 * @return mixed
 *   An array of entities, by entity type.
 */
function dynamic_queue_retrieve_entities($dynamic_queue_entity, $revision_id = NULL) {
  // Retrieve from cache if relevant.
  $cache_id = dynamic_queue_cache_id($dynamic_queue_entity, $revision_id);
  $cache = cache_get($cache_id, 'cache');

  if ($cache && $cache->expire > REQUEST_TIME) {
    if (isset($dynamic_queue_entity->settings['pager'])) {
      pager_default_initialize($cache->data['total'], $dynamic_queue_entity->settings['pager']);
    }
    return $cache->data['result'];
  }

  if (empty($dynamic_queue_entity)) {
    return NULL;
  }

  // Set some basic values for display.
  $limit = NULL;
  if (isset($dynamic_queue_entity->settings['limit']) && $dynamic_queue_entity->settings['limit'] !== '0') {
    $limit = $dynamic_queue_entity->settings['limit'];
  }

  $display_count = 0;
  if (isset($dynamic_queue_entity->settings['pager'])) {
    if (!empty($limit)) {
      $display_count = min($dynamic_queue_entity->settings['pager'], $limit);
    }
    else {
      $display_count = $dynamic_queue_entity->settings['pager'];
    }
  }

  // Query for entities in the dynamic queue.
  $query = new DynamicQueueEntityFieldQuery();
  $query->entityCondition('entity_type', $dynamic_queue_entity->settings['entity_type']);
  $query->entityCondition('bundle', array_filter($dynamic_queue_entity->settings['target_bundles']));
  $query->addTag('dynamic_queue');
  $query->addMetaData('dynamic_queue_entity', $dynamic_queue_entity);

  // This is incredibly fun. EntityFieldQuery *supposedly* should handle this
  // for us, but in reality it is not doing so consistently. This code is drawn
  // from EntityReference_SelectionHandler_Generic_node::entityFieldQueryAlter.
  // See the @link http://drupal.org/node/1440976 Drupal 7 core issue. @endlink
  // See the @link http://drupal.org/node/777578 Drupal 9 core issue. @endlink
  if ($dynamic_queue_entity->settings['entity_type'] == 'node') {
    // We add this in case other access modules implement hook_node_grants().
    $query->addTag('node_access');
    // However if not, we must check this ourselves.
    if (!user_access('bypass node access') && !count(module_implements('node_grants'))) {
      $query->propertyCondition('status', NODE_PUBLISHED);
    }
  }

  // Allow plugins to modify the query.
  ctools_include('plugins');
  $plugins = dynamic_queue_get_modifiers();
  $sorted = FALSE;
  foreach ($plugins as $plugin) {
    $class_name = ctools_plugin_get_class($plugin, 'handler');
    $class = new $class_name();

    // Take care not to invoke sort modifiers that are disabled.
    if ($class->getType() == DynamicQueueModifierBase::MODIFIER_SORT) {
      if ($plugin['name'] == $dynamic_queue_entity->settings['sort']) {
        $class->alterQuery($query, $dynamic_queue_entity->settings);
        $sorted = TRUE;
      }
    }
    else {
      $class->alterQuery($query, $dynamic_queue_entity->settings);
    }
  }

  // Set the default sort order if no sort modifiers are enabled.
  if (!$sorted) {
    $query->propertyOrderBy('changed', 'DESC');
  }

  // Get the total before EntityFieldQuery::pager is added.
  $total_query = clone $query;
  $total_query->range(0, $limit);
  $total = $total_query->count()->execute();

  $query->pager($display_count);
  $query->range(0, $limit);

  $data = array(
    'result' => $query->execute(),
    'total' => $total,
  );

  $dynamic_queue_type = dynamic_queue_type_load($dynamic_queue_entity->type);
  cache_set($cache_id, $data, 'cache', REQUEST_TIME + $dynamic_queue_type->cache_lifetime);

  return $data['result'];
}

/**
 * Page callback: Renders the dynamic queue.
 *
 * @param DynamicQueueEntity $dynamic_queue_entity
 *   The dynamic queue entity to render.
 * @param int $revision_id
 *   The particular revision of the dynamic queue entity to render.
 *
 * @return array
 *   A render array of entities in the dynamic queue.
 */
function dynamic_queue_render_page($dynamic_queue_entity, $revision_id = NULL) {
  if (empty($dynamic_queue_entity)) {
    drupal_not_found();
    drupal_exit();
  }
  else {
    return dynamic_queue_render($dynamic_queue_entity, $revision_id);
  }
}

/**
 * View a Dynamic Queue entity.
 *
 * @param DynamicQueueEntity $dynamic_queue_entity
 *   The Dyamic Queue Entity being viewed.
 * @param int $revision_id
 *   The Revision ID of the Dynamic Queue being viewed.
 *
 * @return array
 *   A render array.
 */
function dynamic_queue_entity_render($dynamic_queue_entity, $revision_id = NULL) {
  if (is_null($revision_id)) {
    return entity_view('dynamic_queue', array($dynamic_queue_entity));
  }
  else {
    $entity = entity_revision_load('dynamic_queue', $revision_id);
    return entity_view('dynamic_queue', array($entity));
  }
}

/**
 * Redirect to the revisions page for the supplied Dynamic Queue.
 *
 * @param object $dynamic_queue
 *   The Dynamic Queue.
 */
function dynamic_queue_revision_redirect($dynamic_queue) {
  if (isset($dynamic_queue->dqid)) {
    drupal_goto('dynamic-queue/' . $dynamic_queue->dqid . '/revisions-state-flow-states', array(), 301);
  }
  else {
    drupal_not_found();
  }
}

/**
 * Queues Revision Form.
 *
 * @param object $DynamicQueueEntity
 *   The Dynamic Queue to modify.
 *
 * @param int $revision_id
 *   The revision id of the entity to edit.
 *
 * @return array|mixed
 *   The revision form.
 */
function dynamic_queue_revision_edit($DynamicQueueEntity, $revision_id) {
  $entity = entity_revision_load('dynamic_queue', $revision_id);
  return entity_ui_get_form('dynamic_queue', $entity, 'edit');
}

/**
 * Form constructor for Dynamic Queue delete revision confirmation form.
 *
 * @see dynamic_queue_confirm_delete_revision_form_submit()
 */
function dynamic_queue_confirm_delete_revision_form($form, &$form_state, $dqid, $vid) {
  $dynamic_queue = dynamic_queue_load($dqid);

  if ($dynamic_queue->vid == $vid) {
    drupal_set_message(t('This revision cannot be deleted because it is currently the primary revision for this dynamic queue'), 'error');
    drupal_goto('dynamic-queue/' . $dqid . '/revisions-state-flow-states');
  }
  else {
    $form = array(
      'dqid' => array(
        '#type' => 'value',
        '#value' => $dqid,
      ),
      'vid' => array(
        '#type' => 'value',
        '#value' => $vid,
      ),
    );
    return confirm_form($form, t('Are you sure you want to delete this revision?'), "dynamic-queue/$dqid/revisions-state-flow-states", t('This action cannot be undone.'), t('Delete revision'), t('Cancel'));
  }
}

/**
 * Form submission handler for dynamic_queue_confirm_delete_revision_form().
 *
 * @see dynamic_queue_confirm_delete_revision_form()
 */
function dynamic_queue_confirm_delete_revision_form_submit($form, &$form_state) {
  $dqid = $form_state['values']['dqid'];
  $vid = $form_state['values']['vid'];

  if (entity_revision_delete('dynamic_queue', $vid)) {
    drupal_set_message(t('The revision has been successfully deleted.'));
  }
  else {
    drupal_set_message(t('The revision could not be deleted.'), 'error');
  }

  drupal_goto('dynamic-queue/' . $dqid . '/revisions-state-flow-states');
}
