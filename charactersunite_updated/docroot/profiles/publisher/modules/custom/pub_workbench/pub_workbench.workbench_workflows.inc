<?php
/**
 * @file
 * pub_workbench.workbench_workflows.inc
 */

/**
 * Implements hook_default_workbench_workflows_events().
 */
function pub_workbench_default_workbench_workflows_events() {
  $export = array();

  $event = new stdClass();
  $event->disabled = FALSE; /* Edit this to true to make a default event disabled initially */
  $event->api_version = 1;
  $event->name = 'to_draft';
  $event->editor_title = '';
  $event->admin_title = 'Draft';
  $event->admin_description = '';
  $event->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $event->contexts = array();
  $event->relationships = array();
  $event->access = array();
  $event->weight = 1;
  $event->target_state = 'draft';
  $event->origin_states = array(
    'draft' => 'draft',
    'review' => 'review',
    'published' => 'published',
    'unpublished' => 'unpublished',
  );
  $export['to_draft'] = $event;

  $event = new stdClass();
  $event->disabled = FALSE; /* Edit this to true to make a default event disabled initially */
  $event->api_version = 1;
  $event->name = 'to_published';
  $event->editor_title = '';
  $event->admin_title = 'Published';
  $event->admin_description = '';
  $event->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $event->contexts = array();
  $event->relationships = array();
  $event->access = array();
  $event->weight = 2;
  $event->target_state = 'published';
  $event->origin_states = array(
    'draft' => 'draft',
    'review' => 'review',
    'published' => 'published',
    'unpublished' => 0,
  );
  $export['to_published'] = $event;

  $event = new stdClass();
  $event->disabled = FALSE; /* Edit this to true to make a default event disabled initially */
  $event->api_version = 1;
  $event->name = 'to_review';
  $event->editor_title = '';
  $event->admin_title = 'Review';
  $event->admin_description = '';
  $event->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $event->contexts = array();
  $event->relationships = array();
  $event->access = array();
  $event->weight = 0;
  $event->target_state = 'review';
  $event->origin_states = array(
    'draft' => 'draft',
    'review' => 0,
    'published' => 0,
    'unpublished' => 0,
  );
  $export['to_review'] = $event;

  $event = new stdClass();
  $event->disabled = FALSE; /* Edit this to true to make a default event disabled initially */
  $event->api_version = 1;
  $event->name = 'to_unpublished';
  $event->editor_title = '';
  $event->admin_title = 'Unpublished';
  $event->admin_description = '';
  $event->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $event->contexts = array();
  $event->relationships = array();
  $event->access = array();
  $event->weight = 3;
  $event->target_state = 'unpublished';
  $event->origin_states = array(
    'published' => 'published',
    'draft' => 0,
    'unpublished' => 0,
  );
  $export['to_unpublished'] = $event;

  return $export;
}

/**
 * Implements hook_default_workbench_workflows_states().
 */
function pub_workbench_default_workbench_workflows_states() {
  $export = array();

  $state = new stdClass();
  $state->disabled = FALSE; /* Edit this to true to make a default state disabled initially */
  $state->api_version = 1;
  $state->name = 'draft';
  $state->editor_title = '';
  $state->admin_title = 'Draft';
  $state->admin_description = '';
  $state->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $state->contexts = array();
  $state->relationships = array();
  $state->access = array();
  $state->weight = 1;
  $export['draft'] = $state;

  $state = new stdClass();
  $state->disabled = FALSE; /* Edit this to true to make a default state disabled initially */
  $state->api_version = 1;
  $state->name = 'published';
  $state->editor_title = '';
  $state->admin_title = 'Published';
  $state->admin_description = '';
  $state->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $state->contexts = array();
  $state->relationships = array();
  $state->access = array();
  $state->weight = 3;
  $export['published'] = $state;

  $state = new stdClass();
  $state->disabled = FALSE; /* Edit this to true to make a default state disabled initially */
  $state->api_version = 1;
  $state->name = 'review';
  $state->editor_title = '';
  $state->admin_title = 'Review';
  $state->admin_description = '';
  $state->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $state->contexts = array();
  $state->relationships = array();
  $state->access = array();
  $state->weight = 2;
  $export['review'] = $state;

  $state = new stdClass();
  $state->disabled = FALSE; /* Edit this to true to make a default state disabled initially */
  $state->api_version = 1;
  $state->name = 'unpublished';
  $state->editor_title = '';
  $state->admin_title = 'Unpublished';
  $state->admin_description = '';
  $state->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $state->contexts = array();
  $state->relationships = array();
  $state->access = array();
  $state->weight = 10;
  $export['unpublished'] = $state;

  return $export;
}

/**
 * Implements hook_default_workbench_workflows_workflows().
 */
function pub_workbench_default_workbench_workflows_workflows() {
  $export = array();

  $workflow = new stdClass();
  $workflow->disabled = FALSE; /* Edit this to true to make a default workflow disabled initially */
  $workflow->api_version = 1;
  $workflow->name = 'publisher_7_default_workflow';
  $workflow->editor_title = '';
  $workflow->admin_title = 'Publisher 7 Default Workflow';
  $workflow->admin_description = '';
  $workflow->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $workflow->contexts = array();
  $workflow->relationships = array();
  $workflow->access = array(
    'plugins' => array(),
  );
  $workflow->weight = 1;
  $workflow->category = '';
  $workflow->states = array(
    'draft' => 'draft',
    'review' => 'review',
    'published' => 'published',
    'unpublished' => 'unpublished',
  );
  $workflow->events = array(
    'to_review' => 'to_review',
    'to_draft' => 'to_draft',
    'to_published' => 'to_published',
    'to_unpublished' => 'to_unpublished',
  );
  $export['publisher_7_default_workflow'] = $workflow;

  return $export;
}
