<?php

/**
 * Override for the Node Selection Handler.
 *
 * This only exists to workaround memory issues when running with a lot of Node.
 */
class PubRelationshipTVEntityReference_SelectionHandler extends EntityReference_SelectionHandler_Generic {

  /**
   * Implements EntityReferenceHandler::getInstance().
   */
  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL) {
    $target_entity_type = $field['settings']['target_type'];

    // Check if the entity type does exist and has a base table.
    $entity_info = entity_get_info($target_entity_type);
    if (empty($entity_info['base table'])) {
      return EntityReference_SelectionHandler_Broken::getInstance($field, $instance);
    }

    return new PubRelationshipTVEntityReference_SelectionHandler($field, $instance, $entity_type, $entity);
  }

  /**
   * Implements EntityReferenceHandler::getReferencableEntities().
   */
  public function getReferencableEntities($match = NULL, $match_operator = 'CONTAINS', $limit = 0) {
    $options = array();
    $entity_type = $this->field['settings']['target_type'];
    $query = db_select('node', 'n')
      ->fields('n', array('nid', 'title', 'type'));
    $query->addTag('pub_relationship_tv_entity_reference');
    $query->addMetaData('entity_type', $entity_type);

    if (!empty($this->field['settings']['handler_settings']['target_bundles'])) {
      $query->condition('type', $this->field['settings']['handler_settings']['target_bundles'], 'IN');
    }

    if ($limit > 0) {
      $query->range(0, $limit);
    }

    $this->buildEntitySelectionQuery($query, $match, $match_operator);

    $results = $query->execute();
    foreach ($results as $record) {
      $options[$record->type][$record->nid] = filter_xss($record->title);
    }

    return $options;
  }

  /**
   * Build an Entity Selection Query to get referanceble entities.
   */
  protected function buildEntitySelectionQuery($query, $match = NULL, $match_operator = 'CONTAINS') {

    // Add the sort option.
    if (!empty($this->field['settings']['handler_settings']['sort'])) {
      $sort_settings = $this->field['settings']['handler_settings']['sort'];
      if ($sort_settings['type'] == 'property') {
        $query->orderBy($sort_settings['property'], $sort_settings['direction']);
      }
    }

    return $query;
  }


  /**
   * Implements PubRelationshipTVEntityReference_SelectionHandler::settingsForm().
   */
  public static function settingsForm($field, $instance) {
    $form = parent::settingsForm($field, $instance);

    // Do not allow this one to sort by fields.
    if (!empty($form['sort']['type']['#options']['field'])) {
      unset($form['sort']['type']['#options']['field']);
    }

    return $form;
  }
}
