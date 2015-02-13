<?php

/**
 * @file
 * Global Publisher settings file, used in all Sites & Environments.
 */

/**
 * Override domain detection in Acquia Purge: hardcode the incoming domain.
 *
 * @see acquia_purge/DOMAINS.txt
 */
if (isset($_SERVER['HTTP_HOST']) && (!empty($_SERVER['HTTP_HOST']))) {
  $conf['acquia_purge_domains'] = array($_SERVER['HTTP_HOST']);
}

/**
 * Set up fast 404 settings.
 */
$conf['404_fast_paths_exclude'] = '/\/(?:styles)\//';
$conf['404_fast_paths'] = '/\.(?:txt|png|gif|jpe?g|css|js|ico|swf|flv|cgi|bat|pl|dll|exe|asp)$/i';
$conf['404_fast_html'] = '<html xmlns="http://www.w3.org/1999/xhtml"><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL "@path" was not found on this server.</p></body></html>';

/**
 * Deauthorize Update manager.
 */
$conf['allow_authorize_operations'] = FALSE;

/**
 * Do not change permissions during a site-install.
 */
$conf['ignore_site_directory_permissions'] = TRUE;

/**
 * Memcache settings.
 */
if (class_exists('Memcache')) {
  $conf['cache_backends'][] = 'profiles/publisher/modules/contrib/memcache/memcache.inc';
  $conf['cache_default_class'] = 'MemCacheDrupal';
  $conf['cache_class_cache_form'] = 'DrupalDatabaseCache';
}

/**
 * Fix issue where Drush doesn't get 'AH_SITE_ENVIRONMENT' environment variable.
 */
if (file_exists('/var/www/sitescripts/siteinfo.php')) {
  // Extract environment info using Acquia's own tool for it.
  require_once '/var/www/sitescripts/siteinfo.php';
  list($ah_site_name, $ah_site_group, $ah_site_env) = ah_site_info();

  if (!isset($_ENV['AH_SITE_NAME'])) {
    $_ENV['AH_SITE_NAME'] = $ah_site_name;
  }
  if (!isset($_ENV['AH_SITE_GROUP'])) {
    $_ENV['AH_SITE_GROUP'] = $ah_site_group;
  }
  if (!isset($_ENV['AH_SITE_ENVIRONMENT'])) {
    $_ENV['AH_SITE_ENVIRONMENT'] = $ah_site_env;
  }
}
// Use getenv() so we can load real environment variables from $_SERVER.
elseif ($ah_site_env = getenv('AH_SITE_ENVIRONMENT')) {
  if (!isset($_ENV['AH_SITE_ENVIRONMENT'])) {
    $_ENV['AH_SITE_ENVIRONMENT'] = $ah_site_env;
  }
}

/**
 * SSO settings.
 */
$conf['pub_sso_password_reset'] = 'https://sso.external.nbcuni.com/nbcucentral/jsp/pwchange.jsp';
// Set pub_sso_server. Allowed values are 'stage' and 'prod'
// Duplicate this setting at sites/default/sso/env.inc
// TODO: Remove the need to duplicate this setting
// Before changing this, ensure `Activate authentication via SimpleSAMLphp` in
// admin/config/people/simplesamlphp_auth is unchecked.
$conf['pub_sso_server'] = 'stage';

/**
 * PHP settings:
 *
 * To see what PHP settings are possible, including whether they can be set at
 * runtime (by using ini_set()), read the PHP documentation:
 * http://www.php.net/manual/ini.list.php
 * See drupal_environment_initialize() in includes/bootstrap.inc for required
 * runtime settings and the .htaccess file for non-runtime settings. Settings
 * defined there should not be duplicated here so as to avoid conflict issues.
 */

/**
 * Some distributions of Linux (most notably Debian) ship their PHP
 * installations with garbage collection (gc) disabled. Since Drupal depends on
 * PHP's garbage collection for clearing sessions, ensure that garbage
 * collection occurs by using the most common settings.
 */
ini_set('session.gc_probability', 1);
ini_set('session.gc_divisor', 100);

/**
 * Set session lifetime (in seconds), i.e. the time from the user's last visit
 * to the active session may be deleted by the session garbage collector. When
 * a session is deleted, authenticated users are logged out, and the contents
 * of the user's $_SESSION variable is discarded.
 */
ini_set('session.gc_maxlifetime', 200000);

/**
 * Set session cookie lifetime (in seconds), i.e. the time from the session is
 * created to the cookie expires, i.e. when the browser is expected to discard
 * the cookie. The value 0 means "until the browser is closed".
 */
ini_set('session.cookie_lifetime', 2000000);

/**
 * If you encounter a situation where users post a large amount of text, and
 * the result is stripped out upon viewing but can still be edited, Drupal's
 * output filter may not have sufficient memory to process it.  If you
 * experience this issue, you may wish to uncomment the following two lines
 * and increase the limits of these variables.  For more information, see
 * http://php.net/manual/pcre.configuration.php.
 */
# ini_set('pcre.backtrack_limit', 200000);
# ini_set('pcre.recursion_limit', 200000);

/**
 * Drupal automatically generates a unique session cookie name for each site
 * based on its full domain name. If you have multiple domains pointing at the
 * same Drupal site, you can either redirect them all to a single domain (see
 * comment in .htaccess), or uncomment the line below and specify their shared
 * base domain. Doing so assures that users remain logged in as they cross
 * between your various domains. Make sure to always start the $cookie_domain
 * with a leading dot, as per RFC 2109.
 */
# $cookie_domain = '.example.com';
