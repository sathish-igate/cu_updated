<?php

/**
 * @file
 * Functionality needed by the Entity Tracker admin pages.
 */

/**
 * System form for Entity Tracker configuration settings.
 */
function entity_tracker_configuration_form($form, &$form_state) {
  $roles = array();
  $user_filters = user_filters();

  if (isset($user_filters['role']['options'])) {
    // Turn on tracking for all roles by default.
    $roles = $user_filters['role']['options'];
    unset($roles['[any]']);
  }

  $options = array_map('check_plain', $roles);
  $default_values = variable_get('entity_tracker_roles', array());

  $form['entity_tracker_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => 'Track entity modifications for the following roles:',
    '#options' => $options,
    '#default_value' => $default_values,
  );

  return system_settings_form($form);
}

/**
 * System form for Entity Tracker report settings.
 */
function entity_tracker_report_form($form, &$form_state) {
  $form['from'] = array(
    '#title' => t('From'),
    '#type' => 'date_popup',
    '#date_year_range' => '-0:+1',
    '#default_value' => time(),
    '#date_label_position' => 'within',
    '#date_format' => 'm/d/Y',
  );

  $form['to'] = array(
    '#title' => t('To'),
    '#type' => 'date_popup',
    '#date_year_range' => '-0:+1',
    '#default_value' => time(),
    '#date_label_position' => 'within',
    '#date_format' => 'm/d/Y',
  );

  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Apply'),
    ),
  );

  return $form;
}

/**
 * Form submission handler for entity_tracker_report_form().
 *
 * @see entity_tracker_report_form()
 */
function entity_tracker_report_form_submit($form, &$form_state) {
  $query = db_select('entity_tracker', 't');
  $query->join('users', 'u', 't.uid = u.uid');
  $query->fields('t', array('entity_id', 'uid', 'title', 'timestamp'))
    ->fields('u', array('name'));

  $from = $form_state['values']['from'];
  if (!empty($from)) {
    $dt = DateTime::createFromFormat('Y-m-d H:i:s', $from . ' 00:00:00');
    $query->condition('t.timestamp', $dt->getTimestamp(), '>=');
  }

  $to = $form_state['values']['to'];
  if (!empty($to)) {
    $dt = DateTime::createFromFormat('Y-m-d H:i:s', $to . ' 23:59:59');
    $query->condition('t.timestamp', $dt->getTimestamp(), '<=');
  }

  $query->orderBy('t.timestamp', 'DESC');
  $result = $query->execute()->fetchAllAssoc('entity_id');

  $nodes = array();
  foreach ($result as $record) {
    $entity = entity_load_single('node', $record->entity_id);
    if (!is_object($entity)) {
      continue;
    }

    $nodes[$record->entity_id]['entity'] = $entity;

    $info = new stdClass();
    $info->title = $entity->title;
    $info->status = $entity->status;
    $info->current_state = $entity->current_state;
    $info->revisions = node_revision_list(node_load($record->entity_id));

    $nodes[$record->entity_id]['info'] = $info;
    $nodes[$record->entity_id]['actions'] = array();
  }

  if (count($nodes) < 1) {
    dpm("No results matched that query.");
    return;
  }

  // Retrieve the action information.
  $query = db_select('entity_tracker', 't');
  $query->join('users', 'u', 't.uid = u.uid');
  $query->fields('t', array('entity_tracker_id', 'entity_id', 'vid', 'uid', 'action', 'timestamp'))
      ->fields('u', array('name'));
  $query->condition('entity_id', array_keys($nodes), 'IN');

  if (!empty($from)) {
    $dt = DateTime::createFromFormat('Y-m-d H:i:s', $from . ' 00:00:00');
    $query->condition('t.timestamp', $dt->getTimestamp(), '>=');
  }
  if (!empty($to)) {
    $dt = DateTime::createFromFormat('Y-m-d H:i:s', $to . ' 23:59:59');
    $query->condition('t.timestamp', $dt->getTimestamp(), '<=');
  }

  $query->orderBy('t.entity_id, t.vid, t.timestamp');
  $result = $query->execute()->fetchAllAssoc('entity_tracker_id');
  foreach ($result as $record) {
    $action = new stdClass();
    $action->action = $record->action;
    $action->uid = $record->uid;
    $action->vid = $record->vid;
    $action->name = $record->name;
    $action->timestamp = $record->timestamp;

    $nodes[$record->entity_id]['actions'][] = $action;
  }

  // Retrieve "Assigned to."
  $query = db_select('node', 'n');
  $query->join('state_flow_states', 's', 'n.vid = s.revision_id');
  $query->join('state_flow_history', 'h', 's.hid = h.hid');
  $query->join('field_data_field_workbench_assigned', 'a', "h.hid = a.entity_id AND a.entity_type = 'state_flow_history_entity' AND a.deleted = 0");
  $query->join('users', 'u', 'a.field_workbench_assigned_target_id = u.uid');

  $query->fields('n', array('nid'));
  $query->fields('u', array('name'));

  $query->condition('nid', array_keys($nodes), 'IN');
  $result = $query->execute()->fetchAllAssoc('nid');

  foreach ($result as $record) {
    $nodes[$record->nid]['info']->assigned_to = $record->name;
  }

  dpm($nodes);
}
