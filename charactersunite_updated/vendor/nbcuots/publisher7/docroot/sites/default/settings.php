<?php

/**
 * @file
 * Entry point settings file, used in all environments.
 */

/**
 * Turn on error reporting. This is turned off in settings.prod.php.
 */
ini_set('display_errors', 'On');

/**
 * This variable is used for reporting, and should match the project shortname.
 */
$conf['pub_site_shortname'] = 'publisher';

/**
 * Include publisher settings.
 */
require_once __DIR__ . '/../../profiles/publisher/settings.publisher.php';


/**
 * @todo Fix memory heavy processes instead of increasing the memory usage for
 * admin pages.
 */
if (arg(0) == 'admin' || arg(0) == 'batch' || arg(0) == 'devel') {
  @ini_set('memory_limit', '256M');
}

/**
 * If we're on Acquia include their settings file.
 */
if (file_exists('/var/www/site-php')) {
  require '/var/www/site-php/nbcupublisher7/nbcupublisher7-settings.inc';
}

/**
 * Include the environment-specific or local file for the project, if it exists.
 */
if (!empty($_ENV['AH_SITE_ENVIRONMENT'])) {
  $site_env_file = __DIR__ . "/settings.{$_ENV['AH_SITE_ENVIRONMENT']}.php";
  if (file_exists($site_env_file)) {
    require_once $site_env_file;
  }
}

/**
 * Allow a override file for any environment.
 */
$override_file = __DIR__ . "/settings.local.php";
if (file_exists($override_file)) {
  require_once $override_file;
}

/**
 * Trigger the fast 404 logic.
 */
drupal_fast_404();
