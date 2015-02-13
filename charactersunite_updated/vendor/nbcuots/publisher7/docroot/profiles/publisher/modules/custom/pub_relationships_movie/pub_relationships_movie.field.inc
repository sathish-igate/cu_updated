<?php

/**
 * @file
 *
 * Field settings for Pub Movie Relationships.
 */

/**
 * Implements hook_field_delete_instance().
 */
function pub_relationships_movie_field_delete_instance($instance) {
  // If our instance is remove via some other way, lets make
  // sure to delete our variable if it happens to be set.
  if (isset($instance['field_name']) && ($instance['field_name'] == MOVIE_FIELD_NAME)) {
    $config = variable_get('pub_relationships_movie_content', array());
    // If we're the one deleted it then we don't need to do anything.
    // This is easy to tell mainly because we only pass a certain number of items to delete_instance.
    // Field config passes the entire instance. So we're going to check for field_id.
    if (!empty($config) && !empty($instance['field_id']) && !empty($instance['bundle'])) {
      $bundle = $instance['bundle'];
      // Set it back to 0.
      $config[$bundle] = 0;
      variable_set('pub_relationships_movie_content', $config);
    }
  }
}

/**
 * Create a field if it does not exists.
 */
function pub_relationships_movie_create_field_if_empty() {
  // Lets make sure our field does not exist before we create it.
  if (!field_info_field(MOVIE_FIELD_NAME)) {
    $field = array(
      'field_name' => MOVIE_FIELD_NAME,
      'type' => 'field_collection',
      'translatable' => FALSE,
      'cardinality' => 1,
    );
    field_create_field($field);

    // After we create our field lets also add the fields to the collection.
    // This will never be the case, but we just have to be sure.
    if (!field_info_field('field_pub_relation_movie_ref')) {
      $collection_field = array(
        'field_name' => 'field_pub_relation_movie_ref',
        'type' => 'entityreference',
        'translatable' => FALSE,
        'settings' => array(
          'target_type' => 'node',
          'handler' => 'base',
          'handler_settings' => array(
            'target_bundles' => array(
              'movie' => 'movie'
            ),
            'sort' => array(
              'type' => 'none',
            ),
          ),
        ),
      );

      field_create_field($collection_field);

      $collection_instance = array(
        'field_name' => 'field_pub_relation_movie_ref',
        'entity_type' => 'field_collection_item',
        'bundle' => MOVIE_FIELD_NAME,
        'label' => 'Movie',
        'widget' => array(
          'type' => 'options_select',
        ),
      );

      field_create_instance($collection_instance);
    }
  }
}

/**
 * Create an instance for a bundle if it does not exists.
 */
function pub_relationships_movie_create_instance_if_empty($bundle) {
  // Lets make sure bundle is an actual valid bundle before creating it.
  // Also we only check node bundles as anything else we don't care.
  $content_types = node_type_get_names();
  $instances = field_info_instance('node', MOVIE_FIELD_NAME, $bundle);
  if (empty($instances) && in_array($bundle, array_keys($content_types))) {
    // If this instance doesn't exist then we create it.
    $instance = array(
      'field_name' => MOVIE_FIELD_NAME,
      'entity_type' => 'node',
      'bundle' => $bundle,
      'label' => 'Movies',
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
function pub_relationships_movie_remove_instance_if_exists($bundle) {
  // Lets make sure bundle is an actual valid bundle before creating it.
  // Also we only check node bundles as anything else we don't care.
  $content_types = node_type_get_names();
  $instances = field_info_instance('node', MOVIE_FIELD_NAME, $bundle);
  if (!empty($instances) && in_array($bundle, array_keys($content_types))) {
    // If this instance doesn't exist then we create it.
    $instance = array(
      'field_name' => MOVIE_FIELD_NAME,
      'entity_type' => 'node',
      'bundle' => $bundle,
      'label' => 'Movie',
      'widget' => array(
        'type' => 'field_collection_embed',
      ),
    );

    field_delete_instance($instance);
  }
}
