<?php

/**
 * @file
 * Provides Views integration with Logo.
 */

/**
 * Implements hook_views_data().
 *
 * Expose logo data to views system.
 */
function logo_views_data() {
  $data['logo']['table']['group'] = t('Logo');

  $data['logo']['table']['base'] = array(
    'field' => 'lid',
    'title' => t('Logo'),
    'help' => t('Unique logo id'),
  );

  // Fields.
  $data['logo']['lid'] = array(
    'title' => t('Logo id'),
    'help' => t('Unique logo id.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  $data['logo']['title'] = array(
    'title' => t('Logo title'),
    'help' => t('Title of the logo.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  $data['logo']['start'] = array(
    'title' => t('Start'),
    'help' => t('Date on which to display the logo.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['logo']['end'] = array(
    'title' => t('End'),
    'help' => t('Date on which this logo should stop displaying.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['logo']['operations'] = array(
    'title' => t('Operations'),
    'help' => t('Displays operations links for the Logo entity.'),
    'field' => array(
      'handler' => 'logo_views_handler_field_operations',
      'no group by' => TRUE,
    ),
  );

  return $data;
}
