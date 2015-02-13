# Publisher API

This module provides a common interface for exposing Publisher7 sites through
a REST API. Some assumptions may remain from the original implementation on
NBC.com but the goal of this module is to remain as generic as possible while
providing useful scaffolding for child modules.

This module provides two major components: a services REST server and a generic
services resource handler.

## REST Server

The REST server provided by this module overrides the one provided by the services
module. The most significant override relates to the accept headers used by
Publisher sites. Your site's custom header can be configured from the Publisher API
settings page at Admin -> Structure -> Services -> Publisher.

## Services resource

The resource handler provided by this module doesn't do much on its own but routes
the services calls through an object oriented framework so that as much code as
possible can be reused.

### Defining a new services resource

There are two parts to defining a new services resource. First, your module must
implement ```hook_services_resources()```. An example follows, but basically this
is a normal implementation of the hook with the exception that each resource's first
argument should be ```resource_info``` and should contain the entity type that's
being returned as well as the resource class that will be used to handle returning
the data.

```php
/**
 * Implements hook_services_resources().
 */
function my_module_services_resources() {
  $resources = array();

  $resources['my_resource'] = array(
    'retrieve' => array(
      'file' => array(
        'type' => 'inc',
        'module' => 'pub_api',
        'name' => 'resources/pub_api_resource'
      ),
      'callback' => 'pub_api_resource_retrieve',
      'args' => array(
        array(
          'name' => 'resource_info',
          'source' => 'const',
          'value' => array(
            'type' => 'listing',
            'resource class' => 'MyResource',
          ),
        ),
        array(
          'name' => 'id',
          'optional' => FALSE,
          'source' => array('path' => 0),
          'type' => 'int',
          'description' => 'The id of the resource to get.',
        ),
      ),
      'access callback' => 'pub_api_resource_access',
      'access callback file' => array(
        'type' => 'inc',
        'module' => 'pub_api',
        'name' => 'resources/pub_api_resource'
      ),
      'access arguments' => array('view'),
      'access arguments append' => TRUE,
      'relationships' => array(
        'relatedEntity' => array(
          'file' => array(
            'type' => 'inc',
            'module' => 'pub_api',
            'name' => 'resources/pub_api_resource',
          ),
          'callback' => 'pub_api_resource_relationship',
          'args' => array(
            array(
              'name' => 'resource_info',
              'source' => 'const',
              'value' => array(
                'type' => 'listing',
                'resource class' => 'MyResource',
                'relationship callback' => 'relatedEntityCallback',
                'validate callback' => 'MyRelatedResource::validateParameter',
              ),
            ),
            array(
              'name' => 'id',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'int',
              'description' => 'The id of the resource to get related entities for.',
            ),
          ),
          'access callback' => 'pub_api_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'pub_api',
            'name' => 'resources/pub_api_resource',
          ),
          'access arguments' => array('view'),
          'access arguments append' => TRUE,
        ),
      ),
    ),
  );

  return $resources;
}
```

Note that although the definition of ```MyResource``` is part of ```my_module``` the
services hook expects to use the ```pub_api``` resource callbacks.

### Returning data

Each of your custom Publisher API resources should return data with an implementation of
[```PubAPIResource```](./resources/PubAPIResource.php). The linked class is heavily
documented with implementation examples, so please take a look at the source code when
you need to start building.

