<?php
/**
 * @file
 * Set up some basic configs.  These can be updated in the site-specific
 * config files.
 */

include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
// Determine the relevant environment.
include_once dirname(__FILE__) . '/env.inc';

// Prevent Varnish from interfering with SimpleSAMLphp.
setcookie('NO_CACHE', '1');


// Set up some defaults for config values.
$environment_config = array(
  'baseurlpath' => 'http://' . $_SERVER["HTTP_HOST"] . '/simplesaml/',
  'certdir' => DRUPAL_ROOT . '/sites/' . $environment_info['cert_directory_directory'] . '/files-private/sso_cert',

  'logging.handler' => 'syslog',
  'loggingdir' => '/tmp/',
  'logging.logfile' => 'simplesamlphp.log',
  'logging.level' => SimpleSAML_Logger::DEBUG,
  'debug' => FALSE,
  'showerrors' => TRUE,

  'store.type' => 'sql',
  'store.sql.dsn' => 'mysql:host=localhost;port=3306;dbname=',
  'store.sql.username' => '',
  'store.sql.password' => '',
  'store.sql.prefix' => 'simplesaml',

  'admin.protectindexpage' => $environment_info['admin.protectindexpage'],
  'admin.protectmetadata' => $environment_info['admin.protectmetadata'],

  'technicalcontact_name' => $environment_info['technicalcontact_name'],
  'technicalcontact_email' => $environment_info['technicalcontact_email'],

  // 'proxyanbcge.nbc.com:80'
  'proxy' => NULL,

  // This config isn't used directly in SimpleSAML.  Acquia uses it to
  // determine the appropriate credentials.
  //
  // 'ah_database_name' should be the Acquia Cloud workflow database
  // name which will store SAML session information.
  //
  // You can use any database that you have defined in your workflow.
  // Use the database "role" without the stage ("dev", "stage", or "test", etc.)
  'ah_database_name' => $environment_info['database_name'],
);

if (!empty($environment_info['auth.adminpassword'])) {
  $environment_config['auth.adminpassword'] = $environment_info['auth.adminpassword'];
}
else {
  // If we weren't supplied a password, create one to keep the UI locked down.
  $environment_config['auth.adminpassword'] = substr(md5(rand()), 0, 7);
}

if ($_ENV['AH_SITE_ENVIRONMENT'] != 'local' && $_ENV['AH_SITE_ENVIRONMENT'] != 'pull-request') {
  // Acquia environment.
  $creds = sso_db_info($environment_config['ah_database_name']);
  $environment_config['certdir'] = '/mnt/files/' . $_ENV['AH_SITE_GROUP'] . '.' . $_ENV['AH_SITE_ENVIRONMENT'] . '/sites/' . $environment_info['cert_directory_directory'] . '/files-private/sso_cert';

  $environment_config['store.sql.dsn'] = sprintf('mysql:host=%s;port=%s;dbname=%s', $creds['host'], $creds['port'], $creds['name']);
  $environment_config['store.sql.username'] = $creds['user'];
  $environment_config['store.sql.password'] = $creds['pass'];

  // Set log location, as specified by Acquia.
  $environment_config['loggingdir'] = '/mnt/tmp/' . $_ENV['AH_SITE_NAME'];
  $environment_config['logging.logfile'] = 'simplesamlphp-' . date("Ymd") . '.log';

  // Set some logging configs for a prod environment.
  if ($_ENV['AH_SITE_ENVIRONMENT'] === 'prod') {
    $environment_config['baseurlpath'] = 'https://' . $_SERVER["HTTP_HOST"] . '/simplesaml/';
    $environment_config['logging.level'] = SimpleSAML_Logger::ERR;
    $environment_config['debug'] = FALSE;
    $environment_config['showerrors'] = FALSE;
  }
}
else {
  // Local environment.
  $creds = array(
    'driver' => 'mysql',
    'host' => 'localhost',
    'port' => 3306,
    'name' => '',
    'user' => '',
    'pass' => '',
  );

  // Apply the values in settings.local.php to the DB credentials.
  if (file_exists(DRUPAL_ROOT . '/' . $environment_info['site_dir'] . '/settings.local.php')) {
    include DRUPAL_ROOT . '/' . $environment_info['site_dir'] . '/settings.local.php';

    // $database values are set in settings.local.php.
    $creds['driver'] = $databases['default']['default']['driver'];
    $creds['host'] = $databases['default']['default']['host'];
    $creds['port'] = $databases['default']['default']['port'];
    $creds['name'] = $databases['default']['default']['database'];
    $creds['user'] = $databases['default']['default']['username'];
    $creds['pass'] = $databases['default']['default']['password'];
  }

  $environment_config['store.sql.dsn'] = sprintf('%s:host=%s;port=%s;dbname=%s', $creds['driver'], $creds['host'], $creds['port'], $creds['name']);
  $environment_config['store.sql.username'] = $creds['user'];
  $environment_config['store.sql.password'] = $creds['pass'];
}

/**
 * A utility function for pulling Acquia DB information.
 */
function sso_db_info($db_name) {
  $creds_json = file_get_contents('/var/www/site-php/' . $_ENV['AH_SITE_NAME'] . '/creds.json');
  $databases = json_decode($creds_json, TRUE);
  $db = $databases['databases'][$db_name];
  $db['host'] = ($host = sso_db_current_host($db['db_cluster_id'])) ? $host : key($db['db_url_ha']);
  return $db;
}

/**
 * A utility function for determining the DB host.
 */
function sso_db_current_host($db_cluster_id) {
  require_once "/usr/share/php/Net/DNS2_wrapper.php";
  try {
    $resolver = new Net_DNS2_Resolver(array('nameservers' => array('127.0.0.1', 'dns-master')));
    $response = $resolver->query("cluster-{$db_cluster_id}.mysql", 'CNAME');
    $cached_id = $response->answer[0]->cname;
  }
  catch (Net_DNS2_Exception $e) {
    $cached_id = "";
  }
  return $cached_id;
}
