<?php

/**
 * @file
 * Common API resource class.
 */

class PubAPIException extends Exception {};

abstract class PubAPIResource {

  protected static $pageSize;

  protected $sortOrder = 'DESC';
  protected $parameters = array();
  public $cacheBin = 'cache_pub_api';
  protected $cacheLifetime;

  /**
   * Construct a new PubAPI Resource.
   *
   * Throws an exception if any of the $_GET parameters does not pass the
   * validation in $this->validateParameter().
   *
   * @param string $validate_callback
   *   An alternative method to use when validating parameters.
   *
   * @throws PubAPIException
   */
  public function __construct($validate_callback = NULL) {
    $this::$pageSize = variable_get('pub_api_page_size', 100);
    $this->cacheLifetime = variable_get('pub_api_cache_lifetime', 86400);
    foreach ($this->getKnownParameters() as $param) {

      // Avoiding direct use of $_GET params.
      $t_param = isset($_GET[$param]) ? $_GET[$param] : NULL;

      if (isset($t_param)) {
        $callback = $validate_callback ?: 'static::validateParameter';
        if (call_user_func($callback, $param, $t_param)) {
          $this->parameters[$param] = $t_param;
        }
        else {
          throw new PubAPIException(
            sprintf('Invalid %s parameter.', $param),
            406
          );
        }
      }
    }
  }

  /**
   * Attempts to fetch an API object from cache.
   *
   * @param string $type
   *   The entity type to prepare.
   * @param object $entity
   *   The entity to prepare.
   *
   * @return mixed
   *   A cached API object if found, else FALSE.
   *
   * @see PubAPIResource::cacheSet()
   */
  public function cacheGet($type, $entity) {
    $object = FALSE;
    $cache = cache_get($this->cacheKey($type, $entity), $this->cacheBin);
    if (
      !empty($cache->data) &&
      ($cache->expire == CACHE_PERMANENT || $cache->expire >= REQUEST_TIME)
    ) {
      // If the cache is not expired.
      $object = $cache->data;
    }

    return $object;
  }

  /**
   * Sets cache for an API object.
   *
   * The purpose of this function is to reduce the support queries and
   * processing that are necessary to prepare Drupal entities to be served as
   * Pub API objects.
   *
   * @param string $type
   *   The entity type being cached.
   * @param object $entity
   *   The entity the cache is for.
   * @param array $object
   *   The API object to cache.
   *
   * @see cache_set()
   */
  public function cacheSet($type, $entity, array $object) {
    $cache_expire = REQUEST_TIME + $this->cacheLifetime;
    cache_set(
      $this->cacheKey($type, $entity),
      $object,
      $this->cacheBin,
      $cache_expire
    );
  }

  /**
   * Clear cache for a given object.
   *
   * @param string $type
   *   Entity type.
   * @param object $entity
   *   Entity object.
   */
  public function cacheClear($type, $entity) {
    cache_clear_all($this->cacheKey($type, $entity), $this->cacheBin);
  }

  /**
   * Generate a cache key for cache operations.
   *
   * @param string $type
   *   The entity type.
   * @param object $entity
   *   The entity object.
   *
   * @return string
   *   The cache key for the current object.
   */
  protected function cacheKey($type, $entity) {
    $id = entity_id($type, $entity);
    $cache_name = $type . '::' . $id;
    if (isset($this->parameters['imageStyle'])) {
      $cache_name .= '::' . $this->parameters['imageStyle'];
    }
    return $cache_name;
  }

  /**
   * Retrieves multiple API objects.
   *
   * @param string $type
   *   The entity type to fetch objects for.
   * @param array $entities
   *   An array of entities to fetch objects for.
   *
   * @return array
   *   An array of API objects.
   */
  public function retrieveMultiple($type, array $entities) {
    $objects = array();

    foreach ($entities as $entity) {
      $cache = $this->cacheGet($type, $entity);
      if ($cache) {
        $objects[] = $cache;
      }
      else {
        $object = $this->prepareObject($entity);
        $this->cacheSet($type, $entity, $object);
        $objects[] = $object;
      }
    }

    return $objects;
  }

  /**
   * Retrieves a single API object.
   *
   * @param string $type
   *   The entity type to retrieve.
   * @param int $id
   *   The entity id to retrieve an API object for.
   *
   * @return object
   *   The API object for the passed in entity.
   *
   * @throws PubAPIException
   */
  public function retrieve($type, $id) {
    if (($entity = entity_load_single($type, $id))) {
      $entities = $this->retrieveMultiple($type, array($entity));
      return reset($entities);
    }

    throw new PubAPIException('Resource not found', 404);
  }

  /**
   * Returns an API index page.
   *
   * @param string $type
   *   The entity type the index is for.
   *
   * @return array|ServicesException
   *   An array of API objects or a services error.
   */
  public function index($type) {
    try {
      /** @var SelectQuery $q Query used to fetch the entities. */
      $q = $this->buildQuery();
      $this->addQueryConditions($q);
      $this->addQueryOrder($q);
    }
    catch (PubAPIException $e) {
      return services_error($e->getMessage(), $e->getCode());
    }
    catch (Exception $e) {
      return services_error(t('Unexpected error while building query.'), 500);
    }

    /** @var SelectQuery $count_query Query used to count the entities. */
    $count_query = clone $q;
    if (!$total = $count_query->countQuery()->execute()->fetchField()) {
      // If there are no entities to be found, then return early.
      return array();
    }

    $offset = isset($this->parameters['offset']) ? $this->parameters['offset'] : 0;
    $q->range($offset, $this::$pageSize);

    $ids = $q->execute()->fetchCol();

    /** @var DrupalDefaultEntityController $c */
    $c = entity_get_controller($type);
    $entities = $c->load($ids);

    $queried_entities = array();

    for ($i = 0; $i < count($ids); $i++) {
      $queried_entities[$i] = $entities[$ids[$i]];
    }

    if ($total > $this::$pageSize && ($offset + $this::$pageSize < $total)) {
      // This is not the only page of results and this is not the last page.
      $last = (floor($total / $this::$pageSize) * $this::$pageSize);
      $last_query = array(
        'offset' => $last,
      );

      $next = (($offset + $this::$pageSize) > $last) ? $last : ($offset + $this::$pageSize);
      $next_query = array(
        'offset' => $next,
      );

      $next_query += $this->parameters;
      $last_query += $this->parameters;
      drupal_add_http_header(
        'Link',
        sprintf(
          '<%s>; rel="next", <%s>; rel="last",',
          url($_GET['q'], array('absolute' => TRUE, 'query' => $next_query)),
          url($_GET['q'], array('absolute' => TRUE, 'query' => $last_query))
        )
      );
    }

    return $this->retrieveMultiple($type, $queried_entities);
  }

  /**
   * Access callback for an API endpoint.
   *
   * @param string $op
   *   The operation being performed.
   * @param string $type
   *   The entity type to check access for.
   * @param int $id
   *   The entity id to check access for.
   *
   * @return bool|ServicesException
   *   TRUE for access granted, FALSE for access denied. Returns
   *   ServicesException in case of error.
   */
  public function access($op, $type, $id) {
    if (($entity = entity_load_single($type, $id))) {
      // entity_access will return void if no access callback exists,
      // so we'll treat that as access granted.
      return (entity_access($op, $type, $entity) !== FALSE);
    }

    return services_error(t('Resource could not be found.'), 404);
  }

  /**
   * Helper function to return the sort direction for query orders.
   */
  protected function getSortDirection() {
    return $this->sortOrder;
  }

  /**
   * Return the known parameters for this resource.
   *
   * @return array
   *   The known parameters for the resource.
   *
   * A resource child class should add its parameters as follows:
   * @code
   * public function getKnownParameters() {
   *   // Combine the parent class's parameters with our resource specefic ones.
   *   return array_merge(
   *     parent::getKnownParameters(),
   *     array(
   *       'type',
   *       'size',
   *       'since',
   *     )
   *   );
   * }
   * @endcode
   */
  public function getKnownParameters() {
    return array(
      'offset',
    );
  }

  /**
   * Validates a parameter's value.
   *
   * @param string $param
   *   The parameter that's being validated.
   * @param mixed $value
   *   The value that was provided for this parameter.
   *
   * @return bool
   *   TRUE if the parameter is valid, else FALSE
   *
   * A resource child class should validate its parameters as follows:
   * @code
   * public function validateParameter($param, $value) {
   *   if ($param == 'type') {
   *     return in_array($value, array('type1,', 'type2', 'type3'));
   *   }
   *   elseif ($param == 'since') {
   *     return is_numeric($value);
   *   }
   *
   *   // Pass parent class and unhandled parameters through to the
   *   // parent class.
   *   return parent::validateParameter($param, $value);
   * }
   * @endcode
   */
  public static function validateParameter($param, $value) {
    if ($param == 'offset') {
      return is_numeric($value);
    }

    return TRUE;
  }

  /**
   * Abstract method, prepares an entity to be served via the API.
   *
   * @param object $entity
   *   The entity to prepare an API object for.
   *
   * @return mixed
   *   The API array or object to serve. Serialized arrays will be
   *   converted to objects when they are output as JSON.
   *
   * Example implementation:
   * @code
   * public function prepareObject(stdClass $entity) {
   *   return array(
   *     'id' => $entity->id,
   *     'created' => date('c', $entity->created),
   *     'things' => array(
   *       'thing1',
   *       'thing2',
   *     ),
   *   );
   * }
   * @endcode
   */
  abstract public function prepareObject(stdClass $entity);

  /**
   * Abstract method, builds a select query for the resource's index.
   *
   * @return SelectQuery
   *   The select query used for the index. We only need to select the entity ID
   *   field here since the entity will be loaded in PubAPIResource::index().
   *
   * @throws PubAPIException
   *
   * Example implementation:
   * @code
   * protected function buildQuery() {
   *   // We only need to select the entity ID field here since the entity
   *   // will be loaded in PubAPIResource::index().
   *   $q = new db_select('my_entity_table', 'e')
   *     ->fields('e', array('eid'));
   *
   *   $q->join('some_table', 's', 's.eid=e.eid');
   *
   *   return $q;
   * }
   * @endcode
   */
  abstract protected function buildQuery();

  /**
   * Adds query conditions.
   *
   * @param SelectQuery $q
   *   The select query to add conditions to.
   *
   * @throws PubAPIException
   *
   * Example implementation:
   * @code
   * protected function addQueryConditions(SelectQuery $q) {
   *   if (isset($this->parameters['since'])) {
   *     $q->condition('s.since', $this->parameters['since'], '=');
   *   }
   *
   *   if (isset($this->parameters['type'])) {
   *     $q->condition('e.type', $this->parameters['type'], '=');
   *   }
   * }
   * @endcode
   */
  abstract protected function addQueryConditions(SelectQuery $q);

  /**
   * Abstract method, adds query sorting.
   *
   * @param SelectQuery $q
   *   The select query for which to add ordering.
   *
   * @throws PubAPIException
   *
   * Example implementation:
   * @code
   * protected function addQueryOrder(SelectQuery $q) {
   *   if (isset($this->parameters['size'])) {
   *      $this->orderBy('s.size', $this->getSortDirection());
   *   }
   * }
   * @endcode
   */
  abstract protected function addQueryOrder(SelectQuery $q);

  /**
   * Gets all the active resource class names.
   *
   * @return array
   *   The list of resource classes.
   */
  public static function getResourceClasses() {
    $resources = module_invoke_all('services_resources');
    $resource_classes = array();
    foreach (element_children($resources) as $resource_name) {
      $resource = $resources[$resource_name];
      foreach ($resource as $method_name => $method_info) {
        if (!empty($method_info['args'][0]['value']['resource class'])) {
          $resource_classes[$method_info['args'][0]['value']['resource class']] = TRUE;
        }
      }
    }
    return array_keys($resource_classes);
  }

}
