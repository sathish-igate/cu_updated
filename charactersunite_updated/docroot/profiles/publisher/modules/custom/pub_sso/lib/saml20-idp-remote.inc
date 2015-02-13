<?php
/**
 * @file
 * Set up some basic configurations for the remote.  These can be updated in the
 * site-specific idp-remote files.
 */

include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
// Determine the relevant environment.
include dirname(__FILE__) . '/env.inc';

// Bring in Drupal's global $conf variable for use here.
// If we are in standalone mode, atleast it will contain
// the value set at sites/default/sso/env.inc.
global $conf;

// Set up some defaults for authsource config values.
$environment_config = array(
  'logout_referrer' => $_SERVER['SERVER_NAME'],
  'metadata.key' => $environment_info['metadata.key'],
  'metadata.name' => $environment_info['metadata_name'],
  'metadata.signonservice' => $environment_info['metadata_signonservice'],
  'metadata.logoutservice' => $environment_info['metadata_logoutservice'],
  // TODO The ideal way to get this is by bootstrapping Drupal and calling
  // pub_sso_get_cert_file().
  'certificate' => $conf['pub_sso_server'] . '.sso.crt',
  'protocol' => 'http',
);
if (isset($_SERVER['HTTPS']) && strcasecmp($_SERVER['HTTPS'], 'off') != 0) {
  $environment_config['protocol'] = 'https';
}
