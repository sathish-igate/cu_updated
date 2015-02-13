<?php

$multisites = array(
  'charactersunite' => 'charactersunite.com'
);

$envs = array('qa', 'stage', 'acc', 'test', 'load', 'dev', 'prod');

foreach ($multisites as $sitename => $domain) {
  foreach ($envs as $env) {
    $sites["$sitename.$env.nbcupublisher7.publisher7.com"] = $sitename;
  }
  $sites['local.' . $sitename] = $sitename;
  $sites['loc.' . $sitename . '.com'] = $sitename;
  $sites['local.' . $sitename . '.com'] = $sitename;
  $sites[$sitename . '.local'] = $sitename;
  $sites['local.publisher.' . $sitename] = $sitename;
  $sites['publisher.' . $sitename . '.local'] = $sitename;
  $sites[$sitename] = $sitename;
  $sites['dev.' . $domain] = $sitename;

  // $domain may have been empty; if so, do not add it.
  if (!empty($domain)) {
    $sites[$domain] = $sitename;
    $sites['local.' . $domain] = $sitename;
  }
}

// Allow users to define their own $sites aliases with a sites.local.php, if desired.
if (file_exists(__DIR__ . '/sites.local.php')) {
  require_once __DIR__ . '/sites.local.php';
}
