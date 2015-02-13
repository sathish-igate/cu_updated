<?php
/**
 * @file
 * Entry point settings file, used in all environments.
 *
 * THIS FILE IS VERY CAREFULLY ORCHESTRATED, AND SHOULD ONLY BE MODIFIED IN
 * EXTREME CIRCUMSTANCES.
 *
 * See docroot/.p7settings/README.settings.php.md for more information.
 */

// Set $site to the string shortname of the current multisite.
$conf['pub_site_shortname'] = 'update';

// Include the environment-agnostic file from Publisher7 core.
require_once dirname(__FILE__) . "/../../.p7settings/settings.p7core.php";

// Next, include the environment-agnostic file owned by this project.
require_once dirname(__FILE__) . "/settings.site.php";

// Next, determine the environment we're in.  Environment types (qa, acceptance,
// stage and prod) are defined in project-config.yml.

// Default to 'dev' if there's no env var set. This covers local dev.
if (empty($_ENV['AH_SITE_ENVIRONMENT'])) {
  $env = 'dev';
}
elseif (strpos($_ENV['AH_SITE_ENVIRONMENT'], 'devi') !== FALSE) {
  $env = 'di';
}
elseif (in_array($_ENV['AH_SITE_ENVIRONMENT'], array('qa1', 'qa2', 'qa3', 'qa4', 'qa5', 'hotfix-qa'))) {
  $env = 'qa';
}
elseif (in_array($_ENV['AH_SITE_ENVIRONMENT'], array('stage', 'hotfix-stage', 'tmp'))) {
  $env = 'stage';
}
elseif (in_array($_ENV['AH_SITE_ENVIRONMENT'], array('prod'))) {
  $env = 'prod';

  // This defaults to a stage URL.
  $conf['sso_password_reset'] = 'https://sso.external.nbcuni.com/nbcucentral/jsp/pwchange.jsp';
}

// Now, include the environment-specific file provided by Publisher7 core, if one exists.
$core_env_file = dirname(__FILE__) . "/../../.p7settings/settings.p7core-$env.php";
if (file_exists($core_env_file)) {
  require_once $core_env_file;
}

// Next, include the environment-specific file owned by the project, if one exists.
$site_env_file = dirname(__FILE__) . "/settings.site-$env.php";
if (file_exists($site_env_file)) {
  require_once $site_env_file;
}

// Trigger the fast 404 logic.
drupal_fast_404();

// If we're on Acquia include their settings file.
if (file_exists('/var/www/site-php/nbcupublisher7/update-settings.inc')) {
  require_once '/var/www/site-php/nbcupublisher7/update-settings.inc';
}

// Finally, include the local settings file if we're on a local machine. This
// is still included conditionally because Jenkins clones lack a settings.local.
// $local is populated by settings.p7core.php.
if ($local && file_exists(dirname(__FILE__) . "/settings.local.php")) {
  require_once dirname(__FILE__) . "/settings.local.php";
}
