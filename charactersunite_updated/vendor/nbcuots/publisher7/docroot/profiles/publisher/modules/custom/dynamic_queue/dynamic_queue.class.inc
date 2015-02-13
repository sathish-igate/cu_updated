<?php

/**
 * @file
 * Provides interfaces and base classes for Dynamic Queue plugins.
 */

/**
 * Interface that all dynamic queue plugins must implement.
 */
interface DynamicQueueModifierInterface {

  /**
   * Alters the form.
   *
   * @param array $form
   *   The form array.
   * @param array $settings
   *   The settings of all plugins.
   * @param DynamicQueueEntity $DynamicQueue
   *   The Dynamic Queue entity object.
   * @param string $op
   *   The operation being performed.
   */
  public static function alterForm(&$form, $settings, $DynamicQueue, $op);

  /**
   * Alters the query.
   *
   * @param EntityFieldQuery $query
   *   The EntityFieldQuery object.
   * @param array $settings
   *   The settings of all plugins.
   */
  public static function alterQuery($query, $settings);

  /**
   * Gets the type of this modifier plugin.
   *
   * @return int
   *   Return MODIFIER_SORT if the plugin is a sort modifier.
   *   Return MODIFIER_FILTER for other types of plugins.
   */
  public static function getType();

  /**
   * Gets the name of this modifier plugin.
   *
   * @return string
   *   The name of the modifier plugin.
   *   In case of a sort modifier, this name is used as the label
   *   for the radio button.
   */
  public static function getName();

}

/**
 * Abstract base class DynamicQueueModifierBase.
 */
abstract class DynamicQueueModifierBase implements DynamicQueueModifierInterface {

  const MODIFIER_SORT = 1;
  const MODIFIER_FILTER = 2;

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
    $form['example'] = array(
      '#type' => 'textfield',
      '#title' => t('Title contains'),
      '#default_value' => isset($settings['example']) ? $settings['example'] : '',
    );
  }

  /**
   * {@inheritdoc}
   */
  public static function alterQuery($query, $settings) {
    // Alter $query object based on $settings variable.
    $query->propertyCondition('title', $settings['example'], 'CONTAINS');
  }

  /**
   * {@inheritdoc}
   */
  public static function getName() {
    return '';
  }
}
