<?php

/**
 * @file
 * Default revision list view for Dynamic Queue.
 */

/**
 * Implements hook_views_default_views().
 */
function dynamic_queue_workbench_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'dynamic_queue_revision_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'dynamic_queue_revision';
  $view->human_name = 'Dynamic Queue revision list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Dynamic Queue revision list';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer dynamic queues';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'state-flow--is-published--[state] state-[state]';
  $handler->display->display_options['style_options']['columns'] = array(
    'dqid' => 'dqid',
    'vid' => 'vid',
    'title' => 'title',
    'state' => 'state',
    'timestamp' => 'timestamp',
    'active' => 'active',
    'history_list' => 'history_list',
    'edit_link' => 'edit_link',
    'state_flow_events_form' => 'state_flow_events_form',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'dqid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'vid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'state' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'active' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'history_list' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'state_flow_events_form' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No revisions available.';
  $handler->display->display_options['empty']['area']['format'] = 'wysiwyg_mini';
  /* Relationship: State Flow States: State Flow History Entity */
  $handler->display->display_options['relationships']['hid']['id'] = 'hid';
  $handler->display->display_options['relationships']['hid']['table'] = 'state_flow_states';
  $handler->display->display_options['relationships']['hid']['field'] = 'hid';
  /* Field: Dynamic Queue Revisions: Dynamic queue ID */
  $handler->display->display_options['fields']['dqid']['id'] = 'dqid';
  $handler->display->display_options['fields']['dqid']['table'] = 'dynamic_queue_revision';
  $handler->display->display_options['fields']['dqid']['field'] = 'dqid';
  $handler->display->display_options['fields']['dqid']['exclude'] = TRUE;
  /* Field: Dynamic Queue Revisions: Vid */
  $handler->display->display_options['fields']['vid']['id'] = 'vid';
  $handler->display->display_options['fields']['vid']['table'] = 'dynamic_queue_revision';
  $handler->display->display_options['fields']['vid']['field'] = 'vid';
  $handler->display->display_options['fields']['vid']['element_label_colon'] = FALSE;
  /* Field: Dynamic Queue Revisions: Label */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'dynamic_queue_revision';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Title';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: State Flow History Record: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'state_flow_history';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['relationship'] = 'hid';
  $handler->display->display_options['fields']['state']['label'] = 'Status';
  $handler->display->display_options['fields']['state']['element_label_colon'] = FALSE;
  /* Field: State Flow States: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'state_flow_states';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Last updated';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'edit_date';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'html5_tools_iso8601';
  /* Field: State Flow States: Active */
  $handler->display->display_options['fields']['active']['id'] = 'active';
  $handler->display->display_options['fields']['active']['table'] = 'state_flow_states';
  $handler->display->display_options['fields']['active']['field'] = 'active';
  $handler->display->display_options['fields']['active']['exclude'] = TRUE;
  $handler->display->display_options['fields']['active']['not'] = 0;
  /* Field: State Flow States: History list */
  $handler->display->display_options['fields']['history_list']['id'] = 'history_list';
  $handler->display->display_options['fields']['history_list']['table'] = 'state_flow_states';
  $handler->display->display_options['fields']['history_list']['field'] = 'history_list';
  $handler->display->display_options['fields']['history_list']['label'] = 'History';
  $handler->display->display_options['fields']['history_list']['element_label_colon'] = FALSE;
  /* Field: Dynamic Queue Revisions: Operation Links (Revision) */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'dynamic_queue_revision';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['label'] = 'Operations';
  $handler->display->display_options['fields']['edit_link']['element_label_colon'] = FALSE;
  /* Field: State Flow States: state flow events form */
  $handler->display->display_options['fields']['state_flow_events_form']['id'] = 'state_flow_events_form';
  $handler->display->display_options['fields']['state_flow_events_form']['table'] = 'state_flow_states';
  $handler->display->display_options['fields']['state_flow_events_form']['field'] = 'state_flow_events_form';
  $handler->display->display_options['fields']['state_flow_events_form']['active_revision_handling'] = 'active';
  /* Sort criterion: State Flow States: Timestamp */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'state_flow_states';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Contextual filter: Dynamic Queue Revisions: Dynamic queue ID */
  $handler->display->display_options['arguments']['dqid']['id'] = 'dqid';
  $handler->display->display_options['arguments']['dqid']['table'] = 'dynamic_queue_revision';
  $handler->display->display_options['arguments']['dqid']['field'] = 'dqid';
  $handler->display->display_options['arguments']['dqid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['dqid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['dqid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['dqid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['dqid']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'dynamic-queue/%/revisions-state-flow-states';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Revisions';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $views['dynamic_queue_revision_list'] = $view;

  return $views;
}
