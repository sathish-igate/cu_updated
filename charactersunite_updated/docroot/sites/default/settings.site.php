<?php
/**
 * @file
 * Global settings file, used in all environments.
 *
 * See README.settings.php.md for information about how this should be used.
 */

/**
 * Override domain detection in Acquia Purge: hardcode the incoming domain.
 *
 * @see acquia_purge/DOMAINS.txt
 */
if (isset($_SERVER['HTTP_HOST']) && (!empty($_SERVER['HTTP_HOST']))) {
  $conf['acquia_purge_domains'] = array($_SERVER['HTTP_HOST']);
}
