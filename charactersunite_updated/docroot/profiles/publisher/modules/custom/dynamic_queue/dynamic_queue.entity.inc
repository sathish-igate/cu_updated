<?php

/**
 * @file
 * Contains class DynamicQueueEntity.
 */

/**
 * Dynamic Queue Entity.
 */
class DynamicQueueEntity extends Entity {
  public $title;
  public $type;
  public $description;
  public $is_new = FALSE;
  public $status = 1;
  public $default_revision = TRUE;
  public $settings;

  /**
   * Constructs an instance of this class.
   *
   * @param array $values
   *   Array containing default values of properties.
   */
  public function __construct($values = array()) {
    // If this is new then set the type first.
    if (isset($values['is_new'])) {
      // Since the entity API does not pass in the type,
      // we are grabbing it from the URL.
      $type = arg(4);
      if (is_string($type)) {
        $this->type = isset($values['type']) ? $values['type'] : $type;
      }
    }
    parent::__construct($values, 'dynamic_queue');
  }

  /**
   * Returns the default Dynamic Queue label which is the title property.
   *
   * @return string
   *   The default label.
   */
  protected function defaultLabel() {
    return $this->title;
  }

  /**
   * Returns the default URI Path for Dynamic Queue administration.
   *
   * @return array
   *   Array containing the default URI specified by the key 'path'.
   */
  protected function defaultUri() {
    return array('path' => 'dynamic-queue/' . $this->identifier());
  }

  /**
   * Saves the Dynamic Queue entity.
   */
  public function save() {
    parent::save();
  }

}

/**
 * DynamicQueueEntityController.
 */
class DynamicQueueEntityController extends EntityAPIController {

  /**
   * {@inheritdoc}
   */
  public function view($entities, $view_mode = 'default', $langcode = NULL, $page = NULL) {
    $content = parent::view($entities, $view_mode, $langcode, $page);

    foreach ($entities as $dynamic_queue) {
      $dynamic_queue_bundle = $content['dynamic_queue'][$dynamic_queue->dqid]['#bundle'];
      $dynamic_queue_view_mode = $content['dynamic_queue'][$dynamic_queue->dqid]['#view_mode'];
      $extra_fields = field_extra_fields_get_display('dynamic_queue', $dynamic_queue_bundle, $dynamic_queue_view_mode);
      $retrieved_entities = dynamic_queue_retrieve_entities($dynamic_queue, $dynamic_queue->vid);

      // Extract the ids of the result.
      $info = entity_get_info();
      $entity_ids = array();
      foreach ($retrieved_entities as $entity_type => $entities) {
        foreach ($entities as $key => $value) {
          $entity_ids[] = $value->{$info[$entity_type]['entity keys']['id']};
        }
      }

      // Render the entities.
      $entities = entity_load('node', $entity_ids);
      $entity_list_view_mode = variable_get('dynamic_queue_' . $dynamic_queue_bundle . '_' . $dynamic_queue_view_mode . '_entity_list_view_mode', 'default');
      $content['dynamic_queue'][$dynamic_queue->dqid]['entity_list_view'] = entity_view('node', $entities, $entity_list_view_mode);
      $content['dynamic_queue'][$dynamic_queue->dqid]['page'] = array('#theme' => 'pager');

      if (isset($extra_fields['entity_list']['weight'])) {
        $content['dynamic_queue'][$dynamic_queue->dqid]['entity_list_view']['#weight'] = $extra_fields['entity_list']['weight'];
      }
    }

    return $content;
  }
}

/**
 * Loads multiple Dynamic Queue entities based on certain conditions.
 *
 * @param array $dynamic_queue_ids
 *   An array of Dynamic Queue IDs.
 * @param array $conditions
 *   An array of conditions to match against the {dynamic_queue} table.
 * @param bool $reset
 *   A boolean indicating that the internal cache should be reset.
 *
 * @return DynamicQueueEntity[]
 *   An array of Dynamic Queue objects, indexed by dqid.
 *
 * @see entity_load()
 * @see dynamic_queue_load()
 */
function dynamic_queue_load_multiple($dynamic_queue_ids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('dynamic_queue', $dynamic_queue_ids, $conditions, $reset);
}
