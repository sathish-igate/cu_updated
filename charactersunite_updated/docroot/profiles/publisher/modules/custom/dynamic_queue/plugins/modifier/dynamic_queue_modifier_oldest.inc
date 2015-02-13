<?php

/**
 * @file
 * Modifier plugin for sort by oldest.
 */

$plugin = array(
  'title' => t('Dynamic Queue Modifier Oldest'),
  'handler' => array(
    'class' => 'DynamicQueueModifierOldest',
    'file' => 'dynamic_queue_modifier_oldest.inc',
  ),
);

/**
 * Class DynamicQueueModifierOldest.
 */
class DynamicQueueModifierOldest extends DynamicQueueModifierBase implements DynamicQueueModifierInterface {

  /**
   * {@inheritdoc}
   */
  public static function getType() {
    return DynamicQueueModifierBase::MODIFIER_SORT;
  }

  /**
   * {@inheritdoc}
   */
  public static function alterForm(&$form, $settings, $DynamicQueue, $op) {
    // Do nothing, as this is a sort modifer.
  }

  /**
   * {@inheritdoc}
   */
  public static function alterQuery($query, $settings) {
    // Alter $query object based on $settings variable.
    $query->propertyOrderBy('changed', 'ASC');
  }

  /**
   * {@inheritdoc}
   */
  public static function getName() {
    return t('Oldest');
  }
}
