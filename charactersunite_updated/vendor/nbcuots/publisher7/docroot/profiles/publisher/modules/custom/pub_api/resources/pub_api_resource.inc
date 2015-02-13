<?php

/**
 * @file
 * Common API handlers for Publisher API resources.
 */

/**
 * Retrieves a single API resource.
 *
 * @param array $resource_info
 *   Array of resource info containing:
 *     'type' - the entity type to fetch.
 *     'resource class' - the resource class to use to fetch the object.
 * @param int $id
 *   The entity ID to return info for.
 *
 * @return object
 *   The API object for the passed in entity.
 */
function pub_api_resource_retrieve($resource_info, $id) {
  $validate_callback = isset($resource_info['validate callback']) ?
    $resource_info['validate callback'] : NULL;
  $resource_class = _pub_api_get_resource_class(
    $resource_info['resource class'],
    $validate_callback
  );
  try {
    return $resource_class->retrieve($resource_info['type'], $id);
  }
  catch (PubAPIException $e) {
    return services_error($e->getMessage(), $e->getCode());
  }
}

/**
 * Retrieves multiple API resources.
 *
 * @param array $resource_info
 *   Array of resource info containing:
 *     'type' - the entity type to fetch.
 *     'resource class' - the resource class to use to fetch the object.
 *
 * @return array|ServicesException
 *   An array of API objects for the passed in resource and entity type. It
 *   returns a services error in case of failure.
 */
function pub_api_resource_index($resource_info) {
  $validate_callback = isset($resource_info['validate callback']) ?
    $resource_info['validate callback'] : NULL;
  $resource_class = _pub_api_get_resource_class(
    $resource_info['resource class'],
    $validate_callback
  );
  return $resource_class->index($resource_info['type']);
}

/**
 * Retrieves related resources to an entity.
 *
 * @param array $resource_info
 *   Array of resource info containing:
 *     'type' - the entity type to fetch.
 *     'resource class' - the resource class to use to fetch the object.
 *     'relationship callback' - the relationship class's method to execute.
 * @param int $id
 *   The entity ID to return info for.
 *
 * @return array
 *   Array of related API objects.
 */
function pub_api_resource_relationship($resource_info, $id) {
  $validate_callback = isset($resource_info['validate callback']) ?
    $resource_info['validate callback'] : NULL;
  $resource_class = _pub_api_get_resource_class(
    $resource_info['resource class'],
    $validate_callback
  );
  return $resource_class->{$resource_info['relationship callback']}($id);
}

/**
 * Access callback for the endpoint.
 *
 * @param string $op
 *   Operation being checked.
 * @param array $args
 *   Array containing:
 *     0 => array $resource_info:
 *       'type' - the entity type to fetch.
 *       'resource class' - the resource class to use to fetch the object.
 *     1 => int $id. ID of the entity to be checked for access.
 *
 * @return bool|ServicesException
 *   TRUE for access granted, FALSE for access denied. Returns ServicesException
 *   in case of error.
 */
function pub_api_resource_access($op, $args = array()) {
  if (!is_array($args[0]) || !isset($args[1])) {
    return services_error(t('Invalid arguments'), 406);
  }

  $resource_info = $args[0];

  // Map the entity ID for different data structure scenarios.
  $id = $args[1];
  if (is_array($id)) {
    $id = $id[0];
  }
  elseif (is_object($id) && isset($id->nid)) {
    $id = $id->nid;
  }

  $validate_callback = isset($resource_info['validate callback']) ?
    $resource_info['validate callback'] : NULL;
  $resource_class = _pub_api_get_resource_class(
    $resource_info['resource class'],
    $validate_callback
  );
  return $resource_class->access($op, $resource_info['type'], $id);
}

/**
 * Helper function to keep a static cache of resource objects.
 *
 * @param string $resource_class
 *   Name of the the resource class.
 * @param string $validate_callback
 *   Name of the validate callback method to use.
 *
 * @return PubAPIResource|ServicesException
 *   Resource object that implements PubAPIResource.
 */
function _pub_api_get_resource_class($resource_class, $validate_callback = NULL) {
  $classes = &drupal_static(__FUNCTION__);

  $key = $resource_class . ($validate_callback ? '::' . $validate_callback : '');

  if (!isset($classes[$key])) {
    try {
      $classes[$key] = new $resource_class($validate_callback);
    }
    catch (PubAPIException $e) {
      return services_error($e->getMessage(), $e->getCode());
    }
  }

  return $classes[$key];
}
