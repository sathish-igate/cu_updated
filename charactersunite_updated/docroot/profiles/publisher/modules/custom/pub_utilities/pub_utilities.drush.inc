<?php

/**
 * Implements hook_drush_help().
 */
function pub_utilities_drush_help($section) {
  switch ($section) {
    case 'meta:pub_utilities:title':
      return dt("Publisher utilities");
  }
}

/**
 * Implements hook_drush_command().
 */
function pub_utilities_drush_command() {

  $items['pub-build'] = array(
    'description' => 'Create a build using the specified tag/branch of Publisher7 core and the specified tag/branch of the specified Acquia server.',
    'arguments' => array(
      'site' => 'The shortname of the site being built. This should be equivalent to the name of the directory in the sites folder.',
      'site_repository' => 'The repository on github to use. Defaults to NBCUOTS/Publisher7.',
      'site_tag_or_branch' => 'The tag or branch to use for the build.',
      'core_repository' => 'The repository on github to use for Publisher7 core. Defaults to NBCUOTS/Publisher7.',
      'core_tag_or_branch' => 'The tag or branch on the core repository to use for the build. Defaults to transition-master.',
      'destination' => 'The Acquia server on which to put the build. This value should correspond to a key in the destination array in the [sitename].aliases.drushrc.php file. Defaults to releases.'
    ),
    'examples' => array(
      "drush @syfy.local pub-build syfy NBCUOTS/Publisher7_syfy 1.2.0 NBCUOTS/Publisher7 transition-master releases'" => 'Build NBCUTOS\'s Syfy (tag:1.2.0) with Publisher7 (branch:transition-master) to the releases server on Acquia.',
      "drush @syfy.local pb syfy bleen/Publisher7_syfy US1234'" => 'Build bleen\'s syfy US1234 branch with Publisher7 (transition-master) to releases server.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'aliases' => array('pb'),
  );

  $items['pub-build-qa'] = array(
    'description' => 'Create a QA build using the specified tag/branch from the specified github repository to the specified Acquia server. Typically this is used only by the core publisher team.',
    'arguments' => array(
      'repository' => 'The repository on github to use. Defaults to NBCUOTS/Publisher7.',
      'tag_or_branch' => 'The tag or branch to use for the build. Defaults to transition-master.',
      'destination' => 'The Acquia server on which to put the build. This value should correspond to a key in the destination array in the [sitename].aliases.drushrc.php file. Defaults to qa5.'
    ),
    'examples' => array(
      "drush pub-build-qa NBCUOTS/Publisher7 transition-master qa5'" => 'Build Publisher7 transition-master to qa5.',
      "drush pbqa bleen/Publisher7 US1234 qa2'" => 'Build bleen\'s Publisher7 US1234 branch to qa2.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'aliases' => array('pbqa'),
  );

  $items['pub-build-clear-files'] = array(
    'description' => 'Clear the files used during the build process. Often this fixes unexplained behaviors but it will make builds take longer.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'aliases' => array('pbcf'),
  );

  return $items;
}

/**
 * Build an instance of Publisher.
 *
 * @param string $site
 *   The site to build.
 * @param string $site_source
 *   The site source.
 * @param string $site_tag_or_branch
 *   The git tag or branch used to build the site.
 * @param string $core_source
 *   The source used for core.
 * @param string $core_tag_or_branch
 *   The git tag or branch used for core.
 * @param string $destination
 *   The destination environment for this instance.
 *
 * @return mixed
 *   An error message.
 */
function drush_pub_utilities_pub_build($site, $site_source, $site_tag_or_branch, $core_source = 'NBCUOTS/Publisher7', $core_tag_or_branch = 'transition-master', $destination = 'releases') {
  $alias = drush_get_context('alias');

  if (empty($alias['site'])) {
    drush_print('This drush command requires that you use the appropriate drush alias.');
  }
  else {
    // Confirm what's being built:
    $args = array(
      '!site' => $site,
      '!site_source' => $site_source,
      '!site_tag_or_branch' => $site_tag_or_branch,
      '!core_source' => $core_source,
      '!core_tag_or_branch' => $core_tag_or_branch,
    );
    if (!drush_confirm(dt("Building !site. !site_tag_or_branch tag/branch of !site_source, and !core_tag_or_branch tag/branch of !core_source. Do you want to continue?", $args))) {
      return drush_user_abort();
    }
    // Get the git repo urls for each of the repositories.
    $source_site_git_repo_url = 'https://' . variable_get('github_credentials', '') . '@github.com/' . $site_source . '.git';
    $source_core_git_repo_url = 'https://' . variable_get('github_credentials', '') . '@github.com/' . $core_source . '.git';
    $destination_git_repo_url = _pub_utilities_get_destination_repo($destination, $alias);

    // Create necessary directories.
    $path_files_private = variable_get('file_private_path', '');
    $path_site_clone = 'pub_releases/drush/' . $alias['site'] . '/' . $site_source;
    $path_core_clone = 'pub_releases/drush/' . $alias['site'] . '/' . $core_source;
    $path_destination_clone = 'pub_releases/drush/' . $alias['site'] . '/' . $destination;
    _pub_utilities_drush_exec($path_files_private, 'mkdir -p -m 775 ' . $path_site_clone);
    _pub_utilities_drush_exec($path_files_private, 'mkdir -p -m 775 ' . $path_core_clone);
    _pub_utilities_drush_exec($path_files_private, 'mkdir -p -m 775 ' . $path_destination_clone);

    // Clone the source repositories and the destination repository.
    _pub_utilities_clone_repo($path_files_private . '/' . $path_site_clone, $source_site_git_repo_url, $site_tag_or_branch);
    _pub_utilities_clone_repo($path_files_private . '/' . $path_core_clone, $source_core_git_repo_url, $core_tag_or_branch);
    _pub_utilities_clone_repo($path_files_private . '/' . $path_destination_clone, $destination_git_repo_url, 'master');

    // Use rsync to move all the code to the proper location.
    _pub_utilities_sync_core($path_files_private, $path_core_clone, $path_destination_clone, $alias);
    _pub_utilities_drush_exec($path_files_private, 'rsync -aq --exclude ".git/" --delete --force ' . $path_site_clone . '/ ' . $path_destination_clone . '/docroot/sites/' . $site);
    drush_log(dt('Synced the site code'), 'success');

    // Tag and release.
    $tag = $core_tag_or_branch . '_' . $site_tag_or_branch;
    _pub_utilities_tag($path_files_private . '/' . $path_destination_clone, $tag);
  }
}

/**
 * Build an instance of Publisher on the QA environments.
 *
 * @param string $source
 *   The location of the tag or branch.
 * @param string $tag_or_branch
 *   The tag or branch itself.
 * @param string $destination
 *   The destination environment for this instance.
 *
 * @return mixed
 *   An error message.
 */
function drush_pub_utilities_pub_build_qa($source = 'NBCUOTS/Publisher7', $tag_or_branch = 'transition-master', $destination = 'qa5') {
  $alias = drush_get_context('alias');

  if (empty($alias['site'])) {
    drush_print('This drush command requires that you use the appropriate drush alias.');
  }
  else {
    // Confirm what's being built:
    $args = array(
      '!source' => $source,
      '!tag_or_branch' => $tag_or_branch,
      '!destination' => $destination,
    );
    if (!drush_confirm(dt("Building !tag_or_branch tag/branch of !source to !destination. Do you want to continue?", $args))) {
      return drush_user_abort();
    }
    // Get the git repo urls for each of the repositories.
    $source_git_repo_url = 'https://' . variable_get('github_credentials', '') . '@github.com/' . $source . '.git';
    $destination_git_repo_url = _pub_utilities_get_destination_repo($destination, $alias);

    // Create necessary directories.
    $path_files_private = variable_get('file_private_path', '');
    $path_source_clone = 'pub_releases/drush/' . $alias['site'] . '/' . $source;
    $path_destination_clone = 'pub_releases/drush/' . $alias['site'] . '/' . $destination;
    _pub_utilities_drush_exec($path_files_private, 'mkdir -p -m 775 ' . $path_source_clone);
    _pub_utilities_drush_exec($path_files_private, 'mkdir -p -m 775 ' . $path_destination_clone);

    // Clone the source and destination repository.
    _pub_utilities_clone_repo($path_files_private . '/' . $path_source_clone, $source_git_repo_url, $tag_or_branch);
    _pub_utilities_clone_repo($path_files_private . '/' . $path_destination_clone, $destination_git_repo_url, 'master');

    // Use rsync from source to destination.
    _pub_utilities_sync_core($path_files_private, $path_source_clone, $path_destination_clone, $alias);

    // Tag and release.
    $tag = 'pub7_' . $tag_or_branch;
    _pub_utilities_tag($path_files_private . '/' . $path_destination_clone, $tag);
  }
}

/**
 * Clears the files left over from a build.
 */
function drush_pub_utilities_pub_build_clear_files() {
  $path_files_private = variable_get('file_private_path', '');
  _pub_utilities_drush_exec($path_files_private, 'rm -rf pub_releases');
  drush_log(dt('Build files have been cleared'), 'success');
}

/**
 * Ensure that the root of executed commands is the docroot of the current site.
 *
 * Wrapper function for drush_shell_cd_and_exec() that ensures the root of all
 * commands is the docroot of the current site.
 *
 * @param string $effective_wd
 *   The working directory, relative to docroot in which to run the command.
 *
 * @param string $cmd
 *   The shell command to run.
 *
 * @see_also drush_shell_cd_and_exec().
 */
function _pub_utilities_drush_exec($effective_wd, $cmd) {
  $docroot = drush_get_context('DRUSH_SELECTED_DRUPAL_ROOT');
  $wd = $docroot . '/' . $effective_wd;

  return drush_shell_cd_and_exec($wd, $cmd);
}

/**
 * Get the destination repository URL.
 *
 * @param string $destination_name
 *   The name of the destination. This should match a key in the $destinations
 *   array in the alias.drushrc file being used.
 *
 * @param array $alias
 *   An array of the alias information retrieved from
 *   drush_get_context('alias').
 *
 * @return mixed
 *   string | NULL
 */
function _pub_utilities_get_destination_repo($destination_name, $alias) {
  $destinations = publisher_utilities_destinations($alias['site']);

  if (isset($destinations[$destination_name])) {
    return $destinations[$destination_name];
  }
  else {
    $error = dt('Sorry, !destination is not a valid destination name.', array('!destination' => $destination_name));
    drush_set_error('pub_build_invalid_destination', $error);
  }
}

/**
 * Clone or pull a repository into the given directory.
 *
 * Clone a repository to the given directory. If it exists already, then pull
 * instead.
 *
 * @param string $path
 *   The directory in which to clone our repository.
 *
 * @param string $git_repo_url
 *   The URL to the repo to clone.
 *
 * @param string $tag_or_branch
 *   The branch or tag to checkout.
 */
function _pub_utilities_clone_repo($path, $git_repo_url, $tag_or_branch = 'transition-master') {
  if (file_exists($path . '/.git')) {
    _pub_utilities_drush_exec($path, 'git fetch origin');
  }
  else {
    drush_print(dt('This may take a few minutes...'));
    _pub_utilities_drush_exec($path, 'git clone ' . $git_repo_url . ' .');
  }

  // Make sure we got all the tags.
  _pub_utilities_drush_exec($path, 'git fetch origin --tags');

  if (_pub_utilities_drush_tag_exists($path, $tag_or_branch)) {
    // If tag exists, checkout that tag.
    _pub_utilities_drush_exec($path, 'git checkout -f ' . $tag_or_branch);
  }
  elseif (_pub_utilities_drush_branch_exists($path, $tag_or_branch, 'origin')) {
    // If remote branch exists, force checkout the branch (and create if it
    // doesn't exist), with the remote branch as a starting point.
    _pub_utilities_drush_exec($path, 'git checkout -B ' . $tag_or_branch . ' origin/' . $tag_or_branch);
  }
  else {
    // Neither the tag nor branch exists, something went wrong!
    $error = dt('Sorry, !tag_or_branch is not a valid tag or branch in !git_repo_url.', array('!tag_or_branch' => $tag_or_branch, '!git_repo_url' => $git_repo_url));
    drush_set_error('pub_build_invalid_tag_or_branch', $error);
    drush_die(dt('Invalid tag or branch.'));
  }

  _pub_utilities_drush_exec($path, 'git clean -df');

  drush_log(dt('Cloned the ' . $git_repo_url . ' repository'), 'success');
}

/**
 * Rsync the code from a source clone to a destination clone.
 *
 * @param string $path_files_private
 *   Path (relative to docroot) to the private files directory.
 *
 * @param string $path_source_clone
 *   Path (relative to private files directory) to the source clone.
 *
 * @param string $path_destination_clone
 *   Path (relative to private files directory) to the destination clone.
 *
 * @param array $alias
 *   An array of the alias information retrieved from
 *   drush_get_context('alias').
 */
function _pub_utilities_sync_core($path_files_private, $path_source_clone, $path_destination_clone, $alias) {
  _pub_utilities_drush_exec($path_files_private, 'rsync -aq --exclude ".git/" --exclude "/sites/' . $alias['site'] . '" --delete --force ' . $path_source_clone . '/ ' . $path_destination_clone);
  _pub_utilities_drush_exec($path_files_private . '/' . $path_destination_clone, 'cat .gitignore_releases >> .gitignore');
  drush_log(dt('Synced the core code'), 'success');
}

/**
 * Tag and push changes to the destination repository.
 *
 * @param string $path
 *   The directory in which to tag our repository.
 *
 * @param string $tag
 *   The tag name to use.
 */
function _pub_utilities_tag($path, $tag) {
  _pub_utilities_drush_exec($path, 'git add -A');
  _pub_utilities_drush_exec($path, 'git commit -m "Creating new tag based on ' . $tag . '"');
  $tag_exists = _pub_utilities_drush_tag_exists($path, $tag);
  $new_tag = $tag_exists ? $tag . '_' . date('Y-m-d_H-i-s') : $tag;
  _pub_utilities_drush_exec($path, 'git tag ' . $new_tag);
  _pub_utilities_drush_exec($path, 'git push origin');
  _pub_utilities_drush_exec($path, 'git push origin ' . $new_tag);
  drush_log(dt('Created a new tag (' . $new_tag . ') and pushed it upstream'), 'success');
}

/**
 * Check if a tag exists in a git repository.
 *
 * @param string $path
 *   The directory in which to check for the tag.
 * @param string $tag
 *   The tag we want to check.
 *
 * @return bool
 *   TRUE on success or FALSE on failure.
 */
function _pub_utilities_drush_tag_exists($path, $tag) {
  $tag_exists = _pub_utilities_drush_exec($path, 'git show-ref --verify --quiet refs/tags/' . $tag);
  if ($tag_exists) {
    drush_log(dt('Tag !tag exists', array('!tag' => $tag)), 'success');
  }
  else {
    drush_log(dt('Tag !tag does not exist', array('!tag' => $tag)), 'warning');
  }
  return $tag_exists;
}

/**
 * Check if a branch exists in a git repository.
 *
 * @param string $path
 *   The directory in which to check for the branch.
 * @param string $branch
 *   The branch we want to check.
 * @param string $remote
 *   The remote we want to check, if not supplied, will check local repo.
 *
 * @return bool
 *   TRUE on success or FALSE on failure.
 */
function _pub_utilities_drush_branch_exists($path, $branch, $remote = NULL) {
  $ref = 'refs/' . ($remote ? 'remotes/' . $remote : 'heads') . '/' . $branch;
  $branch_exists = _pub_utilities_drush_exec($path, 'git show-ref --verify --quiet ' . $ref);
  if ($branch_exists) {
    drush_log(dt('Branch !branch exists', array('!branch' => $branch)), 'success');
  }
  else {
    drush_log(dt('Branch !branch does not exist', array('!branch' => $branch)), 'warning');
  }
  return $branch_exists;
}
