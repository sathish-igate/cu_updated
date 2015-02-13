<?php
/**
 * @file
 * Set up some basic authsource configurations.  These can be updated in the
 * site-specific authsources files.
 */

include_once DRUPAL_ROOT . '/includes/bootstrap.inc';

// Determine the relevant environment.
include dirname(__FILE__) . '/env.inc';

// Set up some defaults for authsource config values.
$environment_config = array(
  'entityID' => $environment_info['entity_id'],
  'idp' => $environment_info['metadata.key'],
  // Will be determined below, within domains.inc.
  'authentication-source.key' => '',
);

// The list of authentication sources keys.
include_once DRUPAL_ROOT . '/' . conf_path() . '/sso/domains.inc';

if (array_key_exists($_SERVER['SERVER_NAME'], $domains)) {
  $environment_config['authentication-source.key'] = $domains[$_SERVER['SERVER_NAME']];
}
