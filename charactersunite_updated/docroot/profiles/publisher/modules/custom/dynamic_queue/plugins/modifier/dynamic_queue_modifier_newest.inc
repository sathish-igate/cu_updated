<?php

/**
 * @file
 * Modifier plugin for sort by newest.
 */

$plugin = array(
  'title' => t('Dynamic Queue Modifier Newest'),
  'handler' => array(
    'class' => 'DynamicQueueModifierNewest',
    'file' => 'dynamic_queue_modifier_newest.inc',
  ),
);

/**
 * Class DynamicQueueModifierNewest.
 */
class DynamicQueueModifierNewest extends DynamicQueueModifierBase implements DynamicQueueModifierInterface {

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
    $query->propertyOrderBy('changed', 'DESC');
  }

  /**
   * {@inheritdoc}
   */
  public static function getName() {
    return t('Newest');
  }
}
