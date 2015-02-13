<?php

/*
 * @file
 *
 * Determine context information so we can include the appropriate SSO settings 
 * file.
 *
 * @see config.inc
 * @see authsources.inc
 * @see saml20-idp-remote.inc
 */

$environment_info = array(
  'site_dir' => conf_path(),
  'environment' => '',
  'parsed_server' => array(),
  'protocol' => 'http',
);

// Determine which site directory we should use.
$server = explode('.', implode('.', array_reverse(explode(':', rtrim($_SERVER['HTTP_HOST'], '.')))));
$environment_info['parsed_server'] = $server;

// Determine the environment.
if (file_exists('/var/www/site-scripts/site-info.php')) {
  $local = FALSE;

  // Extract environment info using Acquia's own tool for it.
  require_once '/var/www/site-scripts/site-info.php';
  list($ah_site_name, $ah_site_group, $ah_site_env, ) = ah_site_info();

  if (!isset($_ENV['AH_SITE_ENVIRONMENT'])) {
    $_ENV['AH_SITE_ENVIRONMENT'] = $ah_site_env;
  }
}
else {
  $local = TRUE;
}

// Allow sites to modify environment info.
if (file_exists(DRUPAL_ROOT . '/' . $environment_info['site_dir'] . '/sso/env.inc')) {
  include DRUPAL_ROOT . '/' . $environment_info['site_dir'] . '/sso/env.inc';
}
