<?php

/**
 * @file
 * Modifier plugin for TV Show relationship.
 */

$plugin = array(
  'title' => t('Dynamic Queue Modifier TV Show'),
  'handler' => array(
    'class' => 'DynamicQueueModifierTVShow',
    'file' => 'dynamic_queue_modifier_tv_show.inc',
  ),
);

/**
 * Class DynamicQueueModifierTVShow.
 */
class DynamicQueueModifierTVShow extends DynamicQueueModifierBase implements DynamicQueueModifierInterface {
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
    $tv_show_query = db_select('node', 'n')
      ->fields('n', array('nid', 'title'))
      ->condition('n.status', 1)
      ->condition('n.type', 'tv_show');
    $tv_show_query->addTag('node_access');
    $tv_show_results = $tv_show_query->execute();
    $tv_select = array(0 => 'Select a TV Show');
    foreach ($tv_show_results as $value) {
      $tv_select[$value->nid] = filter_xss($value->title);
    }
    $form['tv_show_select'] = array(
      '#type' => 'select',
      '#title' => t('TV Shows'),
      '#options' => $tv_select,
      '#default_value' => isset($settings['tv_show_select']) ? $settings['tv_show_select'] : '',
    );
  }

  /**
   * {@inheritdoc}
   */
  public static function alterQuery($query, $settings) {
    // Alter $query object based on $settings variable.
    $fields = field_read_fields(array('type' => 'pub_tv_relationship_field'));
    foreach ($fields as $field) {
      if ($settings['tv_show_select'] != 0) {
        $query->fieldCondition($field['field_name'], 'show', $settings['tv_show_select'], '=');
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public static function getName() {
    return t('TV Show');
  }

}
