<?php

/**
 * Implements hook_migrate_api().
 */
function pub_relationships_tv_enhanced_migrate_api() {
  $api = array(
    'api' => 2,
    'field handlers' => array(
      'MigratePubRelationshipsHandler',
    ),
  );
  return $api;
}

/**
 * Primary value passed to this field is the Show relationship.
 *
 * Subfields are used to specify: 'season', 'episode'.
 *
 * @code
 *   // The Show should be passed in as the primary value.
 *   $this->addFieldMapping('field_show_season_episode', 'show');
 *   $this->addFieldMapping('field_show_season_episode:season', 'season');
 *   $this->addFieldMapping('field_show_season_episode:episode', 'episode');
 * @endcode
 */
class MigratePubRelationshipsHandler extends MigrateFieldHandler {

  /**
   * Migration handler constructor.
   */
  public function __construct() {
    $this->registerTypes(array('pub_tv_relationship_field'));
  }

  /**
   * Define Available fields for the Migration.
   */
  public function fields($type) {
    return array(
      'season' => t('Season'),
      'episode' => t('Episode'),
    );
  }

  /**
   * Prepare the Pub TV Relationship fields.
   */
  public function prepare($entity, array $field_info, array $instance, array $values) {
    $arguments = array();
    if (isset($values['arguments'])) {
      $arguments = array_filter($values['arguments']);
      unset($values['arguments']);
    }
    $language = $this->getFieldLanguage($entity, $field_info, $arguments);

    // Setup the standard Field API array for saving.
    $delta = 0;
    foreach ($values as $value) {
      $return[$language][$delta] = array(
        'show' => $value,
        'season' => 0,
        'episode' => 0,
      );
      if (isset($arguments['season'])) {
        if (is_array($arguments['season'])) {
          $return[$language][$delta]['season'] = $arguments['season'][$delta];
        }
        else {
          $return[$language][$delta]['season'] = $arguments['season'];
        }
      }
      if (isset($arguments['episode'])) {
        if (is_array($arguments['episode'])) {
          $return[$language][$delta]['episode'] = $arguments['episode'][$delta];
        }
        else {
          $return[$language][$delta]['episode'] = $arguments['episode'];
        }
      }
      $delta++;
    }

    return isset($return) ? $return : NULL;
  }
}
