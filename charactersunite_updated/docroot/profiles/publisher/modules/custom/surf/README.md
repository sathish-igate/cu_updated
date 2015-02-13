# Surf

##How to Implement

If you would like to change the surf init configuration you can implement ```hook_surf_settings_alter()```

Example:

```php
/**
 * Implements hook_surf_settings_alter().
 */
function example_surf_settings_alter($settings) {

  $settings['responsive'] = TRUE;
  $settings['smallDisplay'] = 400;


  // This is probably the most important setting. This represents the div id where
  // you would like the surf content to be injected. If you change this to something
  // else make sure you have a ```<div id="surf-content">``` that matches this.
  $settings['element'] = 'surf-content';
}
```

Once you've done that you'll also want to add your JS file after our Surf
session work. Sadly Drupal isn't great at letting you manage JS order.

You can always look at the Surf Example module for directions.

First thing you must declare a library:
```php
/**
 * Implements hook_library().
 */
function pub_surf_example_library() {

  $libraries['surf.example'] = array(
    'title' => 'NBCU Pub Surf',
    'website' => 'http://surfexample-prod.com/',
    'version' => '1.0',
    'js' => array(
      drupal_get_path('module', 'pub_surf_example') . '/pub_surf_example.js' => array(
        'type' => 'file',
        'group' => JS_LIBRARY,
        'scope' => 'footer',
      ),
    ),
    'dependencies' => array(
      array('surf', 'jquery.tmpl'),
      array('surf', 'surf.session'),
    ),
  );

  return $libraries;
}
```

Next you must set your library up as the default lib.
```php

// settings.php settings.
$conf['surf_default_library_module'] = 'pub_surf_example';
$conf['surf_default_library_name'] = 'surf.example';

// Be sure to change these settings per environment.
$conf['surf_src_url'] = 'https://stage.surf.nbcuni.com/rdk/surf.js.php';
$conf['surf_rdk_url'] = '/rdk/';
$conf['surf_config_key'] = 'pubcore';
```

This module also handles SURF Session handling. This can all be manage via the
```Drupal.surf.session``` object. The session info is stored in local Storage
for most browsers if local storage is not available it will fall back to cookie
storage.

```js
// Returns the current logged in user.
// null if there is no user.
user = Drupal.surf.session.get();

// If you want the full user object you can do:
user = Drupal.surf.session.load();
```

We also added one custom event for when the session data is loaded:

```js
/// Listen for Drupal.surf.events.sessionReady
SURF.event.bind(Drupal.surf.events.sessionReady, function(e, user) {
 // user shows the entire loaded user object.
 // You can now set up your default block settings for logged in user or
 // non-logged in user.
});
```

