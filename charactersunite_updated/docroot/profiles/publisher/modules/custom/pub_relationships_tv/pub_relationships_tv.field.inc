<?php

/**
 * @file
 *
 * Field settings for Pub TV Relationships.
 */

/**
 * Do all our ajax settings.
 */
function pub_relationships_tv_setup_ajax(&$form, &$form_state) {
  $field = & $form[TV_FIELD_NAME][LANGUAGE_NONE][0];

  // Simple array used to ignore certain cases.
  $ignored = array(
    'field_season' => FALSE,
    'field_season_ajax' => FALSE,
    'field_episode_ajax' => FALSE,
  );

  // Only add the ajax if the field is visible.
  if ($field['field_season']['#access'] !== FALSE) {
    $ignored['field_season_ajax'] = TRUE;
    $field['field_show'][LANGUAGE_NONE]['#ajax'] = array(
      'event' => 'change',
      'callback' => 'pub_relationships_tv_season_option_ajax',
      'progress' => array(
        'type' => 'throbber',
        'message' => '',
      ),
    );
  }

  // Only add the ajax if the field is visible.
  if ($field['field_episode']['#access'] === TRUE) {
    // Lets enable the Ajax right away.
    $ignored['field_episode_ajax'] = TRUE;
    $field['field_season'][LANGUAGE_NONE]['#ajax'] = array(
      'event' => 'change',
      'callback' => 'pub_relationships_tv_episode_option_ajax',
      'wrapper' => 'episode-wrapper',
      'progress' => array(
        'type' => 'throbber',
        'message' => '',
      ),
    );
  }

  // If form_state['values'] is check this is an ajax request.
  // Other wise we do our regular logic.
  if (!empty($form_state['values'])) {
    // Here we do the actual Ajax Logic.
    // Check if a value for show has already been provided.
    $selected_show = '';
    // Lets do work based on what was triggerd.
    $form_values = & $form_state['values'][TV_FIELD_NAME][LANGUAGE_NONE][0];
    $trigger = $form_state['triggering_element'];
    $triggering_element = $trigger['#field_name'];

    if ($triggering_element == 'field_show') {
      // We do all the form_value logic first.
      // I honestly do not like this.
      // The logic itself is not easy with three fields.
      if (!empty($form_values['field_show'][LANGUAGE_NONE][0]['target_id'])) {
        $selected_show = $form_values['field_show'][LANGUAGE_NONE][0]['target_id'];
        $seasons = pub_relationships_tv_return_seasons($selected_show);
        $field['field_season'][LANGUAGE_NONE]['#options'] = $seasons;
        $field['field_season']['#disabled'] = FALSE;

        $field['field_episode'][LANGUAGE_NONE]['#options'] = array('_none' => t('- None -'));
        $field['field_episode'][LANGUAGE_NONE]['#default_value'] = '_node';
        $field['field_episode']['#disabled'] = TRUE;
      }
      else {
        $field['field_season'][LANGUAGE_NONE]['#options'] = array('_none' => t('- None -'));
        $field['field_season'][LANGUAGE_NONE]['#default_value'] = '_node';
        $field['field_season']['#disabled'] = TRUE;

        $field['field_episode'][LANGUAGE_NONE]['#options'] = array('_none' => t('- None -'));
        $field['field_episode'][LANGUAGE_NONE]['#default_value'] = '_node';
        $field['field_episode']['#disabled'] = TRUE;
      }
    }
    elseif ($triggering_element == 'field_season') {
      if (!empty($form_values['field_season'][LANGUAGE_NONE][0]['target_id'])) {
        $selected_season = $form_values['field_season'][LANGUAGE_NONE][0]['target_id'];
        $episodes = pub_relationships_tv_return_episodes($selected_season);
        $field['field_episode'][LANGUAGE_NONE]['#options'] = $episodes;
        $field['field_episode']['#disabled'] = FALSE;
      }
      else {
        $field['field_episode'][LANGUAGE_NONE]['#options'] = array('_none' => t('- None -'));
        $field['field_episode'][LANGUAGE_NONE]['#default_value'] = '_node';
        $field['field_episode']['#disabled'] = TRUE;
      }
    }
  }
  else {

    if ($ignored['field_season_ajax'] === TRUE) {
      if (!empty($field['field_show'][LANGUAGE_NONE]['#default_value'][0])) {
        $selected_show = $field['field_show'][LANGUAGE_NONE]['#default_value'][0];
        if (is_numeric($selected_show)) {
          // This way the field are correct on load.
          $seasons = pub_relationships_tv_return_seasons($selected_show);
          $field['field_season'][LANGUAGE_NONE]['#options'] = $seasons;
        }
        else {
          $field['field_season']['#disabled'] = FALSE;
        }
      }
      else {
        // If there's no selected show we disabled it right away.
        $field['field_season']['#disabled'] = TRUE;
        $field['field_season'][LANGUAGE_NONE]['#options'] = array('_none' => t('- None -'));
      }
    }

    if ($ignored['field_episode_ajax'] === TRUE) {
      if (!empty($field['field_season'][LANGUAGE_NONE]['#default_value'][0])) {
        $selected_season = $field['field_season'][LANGUAGE_NONE]['#default_value'][0];
        if (is_numeric($selected_season)) {
          // This way the field are correct on load.
          $episodes = pub_relationships_tv_return_episodes($selected_season);
          $field['field_episode'][LANGUAGE_NONE]['#options'] = $episodes;
        }
        else {
          $field['field_episode']['#disabled'] = FALSE;
        }
      }
      else {
        $field['field_episode']['#disabled'] = TRUE;
        $field['field_episode'][LANGUAGE_NONE]['#options'] = array('_none' => t('- None -'));
      }
    }
  }
}

/**
 * Ajax function to correct season list.
 */
function pub_relationships_tv_season_option_ajax($form, $form_state) {
  $field = & $form['pub_relationships'][TV_FIELD_NAME][LANGUAGE_NONE][0];
  // We want to replace both the season and the episodes so we return an list
  // of ajax commands.
  $commands = array();
  $field_season = drupal_render($field['field_season']);
  $field_episode = drupal_render($field['field_episode']);
  $commands[] = ajax_command_replace('#season-wrapper', $field_season);
  $commands[] = ajax_command_replace('#episode-wrapper', $field_episode);
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Ajax function to correct episode list.
 */
function pub_relationships_tv_episode_option_ajax($form, $form_state) {
  $field = & $form['pub_relationships'][TV_FIELD_NAME][LANGUAGE_NONE][0];
  return $field['field_episode'];
}

/**
 * Helper function to return valid episodes.
 */
function pub_relationships_tv_return_episodes($selected_season) {

  $options = array('_none' => t('- None -'));

  // Get the list of episodes based on the user-entered show value.
  $query = new EntityFieldQuery('entity_type', 'field_collection_item');
  $query->entityCondition('bundle', 'field_pub_relation_tv_shows');
  $query->fieldCondition('field_season', 'target_id', $selected_season);
  $result = $query->execute();


  // Add each episode that belongs to the user-selected show to the options
  // array.
  if (isset($result['field_collection_item'])) {
    $entities_ids = array_keys($result['field_collection_item']);

    // We used to do an EntityFieldQuery but there was a problem with the
    // field revision. Also it's nicer because we get to make the bundle a
    // condition instead of checking it on PHP.
    $query = db_select('field_revision_field_pub_relation_tv_shows', 'f');
    $query->join('node_revision', 'n', 'n.nid = f.entity_id');
    $query->fields('f');
    $query->fields('n', array('nid', 'title'));
    $query->condition('field_pub_relation_tv_shows_value', array_values($entities_ids), 'IN');
    $query->condition('f.bundle', 'tv_episode');
    $query->addTag('pub_relationships_tv_return');
    $query->addTag('pub_relationships_tv_return_episodes');
    $result = $query->execute();
    foreach ($result as $record) {
      $options[$record->nid] = $record->title;
    }
  }

  return $options;
}

/**
 * Helper function to return valid Seasons.
 */
function pub_relationships_tv_return_seasons($selected_show, $include_unpublished = TRUE) {

  $options = array('_none' => t('- None -'));

  // Get the list of seasons based on the user-entered show value.
  $query = new EntityFieldQuery('entity_type', 'field_collection_item');
  $query->entityCondition('bundle', 'field_pub_relation_tv_shows');
  $query->fieldCondition('field_show', 'target_id', $selected_show);
  $result = $query->execute();

  // Add each season that belongs to the user-selected show to the options
  // array.
  if (isset($result['field_collection_item'])) {
    $entities_ids = array_keys($result['field_collection_item']);

    // We used to do an EntityFieldQuery but there was a problem with the
    // field revision. Also it's nicer because we get to make the bundle a
    // condition instead of checking it on php.
    $query = db_select('field_revision_field_pub_relation_tv_shows', 'f');
    $query->join('node_revision', 'n', 'n.nid = f.entity_id');
    $query->fields('f');
    $query->fields('n', array('nid', 'title'));
    $query->condition('field_pub_relation_tv_shows_value', array_values($entities_ids), 'IN');
    $query->condition('f.bundle', 'tv_season');
    $query->addTag('pub_relationships_tv_return');
    $query->addTag('pub_relationships_tv_return_seasons');

    // Include only published item if $include_unpublished is FALSE.
    if (!$include_unpublished) {
      $query->condition('status', NODE_PUBLISHED);
    }

    $result = $query->execute();
    foreach ($result as $record) {
      $options[$record->nid] = $record->title;
    }
  }

  return $options;
}

/**
 * Make sure only the allow values are display.
 */
function pub_relationships_tv_show_valid_fields(&$form, $bundle) {
  $field = & $form[TV_FIELD_NAME][LANGUAGE_NONE][0];
  $drop_key = 'pub_relationships_tv_content_type_' . $bundle . '_level';
  $config = variable_get($drop_key, FALSE);
  if ($config !== FALSE) {
    switch ($config) {
      case 'show':
        // We hide the season, and episode.
        // Entity reference builds out #options for each field, and by default
        // they are not filtered by show or season. We could write a new ER
        // plugin to fix things there, but this module is already deprecated
        // for pub_relationships_tv_enhanced. To prevent caching #options in
        // the form cache, we hardcode #value instead.
        $field['field_season']['#access'] = FALSE;
        $field['field_season'][LANGUAGE_NONE]['#value'] = $field['field_season'][LANGUAGE_NONE]['#default_value'];
        if ($field['field_season'][LANGUAGE_NONE]['#value']) {
          $field['field_season'][LANGUAGE_NONE]['#options'] = array(
            $field['field_season'][LANGUAGE_NONE]['#value'] => $field['field_season'][LANGUAGE_NONE]['#value'],
          );
        }
        else {
          $field['field_season'][LANGUAGE_NONE]['#options'] = $field['field_season'][LANGUAGE_NONE]['#value'];
        }

        $field['field_episode']['#access'] = FALSE;
        $field['field_episode'][LANGUAGE_NONE]['#value'] = $field['field_episode'][LANGUAGE_NONE]['#default_value'];
        if ($field['field_episode'][LANGUAGE_NONE]['#value']) {
          $field['field_episode'][LANGUAGE_NONE]['#options'] = array(
            $field['field_episode'][LANGUAGE_NONE]['#value'] => $field['field_episode'][LANGUAGE_NONE]['#value'],
          );
        }
        else {
          $field['field_episode'][LANGUAGE_NONE]['#options'] = $field['field_episode'][LANGUAGE_NONE]['#value'];
        }
        break;

      case 'season':
        // We hide episode.
        $field['field_season']['#prefix'] = '<div id="season-wrapper">';
        $field['field_season']['#suffix'] = '</div>';
        $field['field_episode']['#access'] = FALSE;
        $field['field_episode'][LANGUAGE_NONE]['#value'] = $field['field_episode'][LANGUAGE_NONE]['#default_value'];
        $field['field_episode'][LANGUAGE_NONE]['#options'] = array(
          $field['field_episode'][LANGUAGE_NONE]['#value'] => $field['field_episode'][LANGUAGE_NONE]['#value'],
        );
        break;

      case 'episode':
        $field['field_season']['#prefix'] = '<div id="season-wrapper">';
        $field['field_season']['#suffix'] = '</div>';
        $field['field_episode']['#prefix'] = '<div id="episode-wrapper">';
        $field['field_episode']['#suffix'] = '</div>';
        break;

      default:
        // We do nada.
        break;
    }
  }
}

/**
 * Implements hook_field_delete_instance().
 */
function pub_relationships_tv_field_delete_instance($instance) {
  // If our instance is remove via some other way, lets make
  // sure to delete our variable if it happens to be set.
  if (isset($instance['field_name']) && ($instance['field_name'] == TV_FIELD_NAME)) {
    // If we're the one deleted it then we don't need to do anything.
    // This is easy to tell mainly because we only pass a certain number of items to delete_instance.
    // Field config passes the entire instance. So we're going to check for field_id.
    if (!empty($instance['field_id']) && !empty($instance['bundle'])) {
      $form_key = 'pub_relationships_tv_content_type_' . $instance['bundle'];
      variable_set($form_key, 0);
    }
  }
}

/**
 * Create a field if it does not exists.
 */
function pub_relationships_tv_create_field_if_empty() {
  // Lets make sure our field does not exist before we create it.
  if (!field_info_field(TV_FIELD_NAME)) {
    $field = array(
      'field_name' => TV_FIELD_NAME,
      'type' => 'field_collection',
      'translatable' => FALSE,
      'cardinality' => 1,
    );

    field_create_field($field);

    // We need to create a show instance.
    $show_collection_instance = array(
      'field_name' => 'field_show',
      'entity_type' => 'field_collection_item',
      'bundle' => TV_FIELD_NAME,
      'label' => 'Show',
      'widget' => array(
        'type' => 'options_select',
      ),
    );

    $instance = field_info_instance('field_collection_item', 'field_show', TV_FIELD_NAME);
    if (empty($instance)) {
      field_create_instance($show_collection_instance);
    }

    // Now a season instance.
    $season_collection_instance = array(
      'field_name' => 'field_season',
      'entity_type' => 'field_collection_item',
      'bundle' => TV_FIELD_NAME,
      'label' => 'Season',
      'widget' => array(
        'type' => 'options_select',
      ),
    );

    $instance = field_info_instance('field_collection_item', 'field_season', TV_FIELD_NAME);
    if (empty($instance)) {
      field_create_instance($season_collection_instance);
    }

    field_cache_clear(TRUE);
  }

  // Now sadly we also need to create an episode field.
  $field = field_info_field('field_episode');
  if (empty($field)) {
    $field = array(
      'field_name' => 'field_episode',
      'type' => 'entityreference',
      'translatable' => FALSE,
    );

    field_create_field($field);
    field_cache_clear(TRUE);
    // We need to clear the cache again.
  }


  // We need to create a show instance.
  $episode_collection_instance = array(
    'field_name' => 'field_episode',
    'entity_type' => 'field_collection_item',
    'bundle' => TV_FIELD_NAME,
    'label' => 'Episode',
    'widget' => array(
      'type' => 'options_select',
    ),
  );

  $instance =  field_info_instance('field_collection_item', 'field_episode', TV_FIELD_NAME);
  if (empty($instance)) {
    field_create_instance($episode_collection_instance);

    field_cache_clear(TRUE);

    // Now we reload the field.
    $field = field_info_field('field_episode');
    $field['settings']['handler_settings'] = array(
      'target_bundles' => array('tv_episode'),
      'sort' => array('type' => 'none'),
    );
    field_update_field($field);
  }
}

/**
 * Create an instance for a bundle if it does not exists.
 */
function pub_relationships_tv_create_instance_if_empty($bundle) {
  // Lets make sure bundle is an actual valid bundle before creating it.
  // Also we only check node bundles as anything else we don't care.
  $content_types = node_type_get_names();
  $instances = field_info_instance('node', TV_FIELD_NAME, $bundle);
  if (empty($instances) && in_array($bundle, array_keys($content_types))) {
    // If this instance doesn't exist then we create it.
    $instance = array(
      'field_name' => TV_FIELD_NAME,
      'entity_type' => 'node',
      'bundle' => $bundle,
      'label' => 'TV Shows',
      'widget' => array(
        'type' => 'field_collection_embed',
      ),
    );

    field_create_instance($instance);
  }
}

/**
 * Remove an instance for a bundle if it exists.
 */
function pub_relationships_tv_remove_instance_if_exists($bundle) {
  // Lets make sure bundle is an actual valid bundle before creating it.
  // Also we only check node bundles as anything else we don't care.
  $content_types = node_type_get_names();
  $instances = field_info_instance('node', TV_FIELD_NAME, $bundle);
  if (!empty($instances) && in_array($bundle, array_keys($content_types))) {
    // If this instance doesn't exist then we create it.
    $instance = array(
      'field_name' => TV_FIELD_NAME,
      'entity_type' => 'node',
      'bundle' => $bundle,
      'label' => 'TV Shows',
      'widget' => array(
        'type' => 'field_collection_embed',
      ),
    );

    field_delete_instance($instance);
  }
}
