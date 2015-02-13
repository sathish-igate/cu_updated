<?php

if (!isset($drush_major_version)) {
  $drush_version_components = explode('.', DRUSH_VERSION);
  $drush_major_version = $drush_version_components[0];
}
// Site nbcuunite, environment acceptance
$aliases['acceptance'] = array(
  'root' => '/var/www/html/nbcuunite.acceptance/docroot',
  'ac-site' => 'nbcuunite',
  'ac-env' => 'acceptance',
  'ac-realm' => 'prod',
  'uri' => 'nbcuuniteacc.prod.acquia-sites.com',
  'remote-host' => 'staging-4868.prod.hosting.acquia.com',
  'remote-user' => 'nbcuunite.acceptance',
  'path-aliases' => array(
    '%drush-script' => 'drush' . $drush_major_version,
  )
);
$aliases['acceptance.livedev'] = array(
  'parent' => '@nbcuunite.acceptance',
  'root' => '/mnt/gfs/nbcuunite.acceptance/livedev/docroot',
);

if (!isset($drush_major_version)) {
  $drush_version_components = explode('.', DRUSH_VERSION);
  $drush_major_version = $drush_version_components[0];
}
// Site nbcuunite, environment dev
$aliases['dev'] = array(
  'root' => '/var/www/html/nbcuunite.dev/docroot',
  'ac-site' => 'nbcuunite',
  'ac-env' => 'dev',
  'ac-realm' => 'prod',
  'uri' => 'nbcuunitedev.prod.acquia-sites.com',
  'remote-host' => 'staging-4009.prod.hosting.acquia.com',
  'remote-user' => 'nbcuunite.dev',
  'path-aliases' => array(
    '%drush-script' => 'drush' . $drush_major_version,
  )
);
$aliases['dev.livedev'] = array(
  'parent' => '@nbcuunite.dev',
  'root' => '/mnt/gfs/nbcuunite.dev/livedev/docroot',
);

if (!isset($drush_major_version)) {
  $drush_version_components = explode('.', DRUSH_VERSION);
  $drush_major_version = $drush_version_components[0];
}
// Site nbcuunite, environment prod
$aliases['prod'] = array(
  'root' => '/var/www/html/nbcuunite.prod/docroot',
  'ac-site' => 'nbcuunite',
  'ac-env' => 'prod',
  'ac-realm' => 'prod',
  'uri' => 'nbcuunite.prod.acquia-sites.com',
  'remote-host' => 'web-5968.prod.hosting.acquia.com',
  'remote-user' => 'nbcuunite.prod',
  'path-aliases' => array(
    '%drush-script' => 'drush' . $drush_major_version,
  )
);
$aliases['prod.livedev'] = array(
  'parent' => '@nbcuunite.prod',
  'root' => '/mnt/gfs/nbcuunite.prod/livedev/docroot',
);

if (!isset($drush_major_version)) {
  $drush_version_components = explode('.', DRUSH_VERSION);
  $drush_major_version = $drush_version_components[0];
}
// Site nbcuunite, environment test
$aliases['test'] = array(
  'root' => '/var/www/html/nbcuunite.test/docroot',
  'ac-site' => 'nbcuunite',
  'ac-env' => 'test',
  'ac-realm' => 'prod',
  'uri' => 'nbcuunitestg.prod.acquia-sites.com',
  'remote-host' => 'staging-4009.prod.hosting.acquia.com',
  'remote-user' => 'nbcuunite.test',
  'path-aliases' => array(
    '%drush-script' => 'drush' . $drush_major_version,
  )
);
$aliases['test.livedev'] = array(
  'parent' => '@nbcuunite.test',
  'root' => '/mnt/gfs/nbcuunite.test/livedev/docroot',
);
