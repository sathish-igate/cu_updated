<?php

/**
 * Batch operation for cloning a repository.
 */
function pub_qa_releases_clone_repo($repo_name, $repo_path, $tag_or_branch, &$context) {
  $git = variable_get('pub_utilities_git_bin', '');
  $tag_or_branch = empty($tag_or_branch) ? 'transition-master' : $tag_or_branch;

  // Change to the pub7 directory for the publisher core repo.
  _pub_qa_releases_batch_chdir($repo_name);

  // If the repo already exists, fetch from origin, otherwise clone it.
  if (is_dir('.git')) {
    _pub_utilities_exec($git . ' fetch origin', t('The !repo repository could not be updated.', array('!repo' => $repo_name)));
  }
  else {
    _pub_utilities_exec($git . ' clone ' . $repo_path . ' ./', t('The !repo repository could not be cloned.', array('!repo' => $repo_name)));
    if (isset($_ENV['AH_SITE_ENVIRONMENT']) && $_ENV['AH_SITE_ENVIRONMENT'] != 'local') {
      _pub_utilities_exec($git . ' config user.email "pub_releases@otstv.publisher.nbcuni.com"');
      _pub_utilities_exec($git . ' config user.name "Publisher Releases"');
    }
  }

  // Checkout the correct tag or branch.
  _pub_utilities_exec($git . ' checkout -f ' . $tag_or_branch);

  // If this is a branch, merge from origin into this branch.
  if (!_pub_utilities_tag_exists($tag_or_branch)) {
    _pub_utilities_exec($git . ' merge origin/' . $tag_or_branch);
  }

  // Just in case, clean the current directory of untracked files.
  _pub_utilities_exec($git . ' clean -df');

  // Update the batch context.
  $context['results'][] = t('Checked out the !repo repository. !tag_or_branch', array('!tag_or_branch' => '(' . $tag_or_branch . ')', '!repo' => $repo_name));
  $context['message'] = t('Checked out the !repo repository. !tag_or_branch', array('!tag_or_branch' => '(' . $tag_or_branch . ')', '!repo' => $repo_name));
}

/**
 * Batch operation for mushing the source code from two repositories into one.
 */
function pub_qa_releases_sync_code($pubcore_repo_name, $destination_repo_name, &$context) {
  $path = _pub_qa_releases_path() . 'pub7/';

  // Use rsync to move the code inot the destiation repository.
  _pub_utilities_exec('rsync -aq --exclude ".git/" --exclude "/sites/' . $site_name . '" --delete --force ' . $path . $pubcore_repo_name . '/ ' . $path . $destination_repo_name);

  // Append the contents of .gitignore_releases to .gitignore so that we can
  // override the ignore rules used for development on the cloud-based servers.
  _pub_qa_releases_batch_chdir($destination_repo_name);
  _pub_utilities_exec('cat .gitignore_releases >> .gitignore', t('Could not append .gitignore_releases to .gitignore.'));

  // Update the batch context.
  $context['results'][] = t('Synced the code from the Publisher Core source into the destination source');
  $context['message'] = t('Synced the code from the Publisher Core source into the destination source');
}

/**
 * Batch operation for creating a new tag in the unified repository.
 */
function pub_qa_releases_create_tag($repo_name, $pubcore_tag_or_branch, &$context) {
  $git = variable_get('pub_utilities_git_bin', '');
  $new_tag = 'pub7_' . $pubcore_tag_or_branch;

  // Change to the appropriate directory for the publisher core repo.
  _pub_qa_releases_batch_chdir($repo_name);

  // Stage and commit all files (including modified files, new files and deleted
  // files).
  _pub_utilities_exec($git . ' add -A');
  _pub_utilities_exec($git . ' commit -m "Creating new tag based on ' . $pubcore_tag_or_branch . '"', t('Could not commit changes to the !repo repository.', array('!repo' => $repo_name)));

  // Creating a new tag. If the tag already exists, append the date.
  $tag_exists = _pub_utilities_tag_exists($new_tag);
  $new_tag = $tag_exists ? $new_tag . '_' . date('Y-m-d_H-i-s') : $new_tag;
  _pub_utilities_exec($git . ' tag ' . $new_tag);

  // Push the new tag to origin.
  _pub_utilities_exec($git . ' push origin', t('Could not push changes to the !repo repository.', array('!repo' => $repo_name)));
  _pub_utilities_exec($git . ' push origin ' . $new_tag, t('Could not push the !new_tag tag to the !repo repository.', array('!new_tag' => $new_tag, '!repo' => $repo_name)));

  // Update the batch context.
  $context['results'][] = t('Created release tag');
  $context['message'] = t('Created the !tag release tag on !repo', array('!tag' => $new_tag, '!repo' => $repo_name));
}

/**
 * Batch operation for deleting all build files.
 */
function pub_qa_releases_clear_files() {
  $files = _pub_qa_releases_path();
  _pub_utilities_exec('rm -rf ' . $files);
}

/**
 * Build batch complete callback function.
 */
function pub_qa_releases_build_batch_complete($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('The release has been successfully built.'));
  }
  else {
    drupal_set_message(t('The release failed.'), 'error');
  }
}

/**
 * Clear batch complete callback function.
 */
function pub_qa_releases_clear_batch_complete($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('All build files have been deleted. This will make the next release build take longer but it will not effect any sites on any environments.'));
  }
  else {
    drupal_set_message(t('The build files could not be deleted.'), 'error');
  }
}

/**
 * Helper function that returns the files path for pub releases.
 *
 * Helper function that returns the correct files path.  All the git clones
 * should live here for the various release operations.
 *
 * @return string
 *   path to pub_releases in the private files directory.
 */
function _pub_qa_releases_path() {
  return _pub_utilities_get_private_files_path() . '/pub_releases/';
}

/**
 * Helper function for changing directory on the command line.
 *
 * Helper function for changing directory on the command line. If the directory
 * does not exist, it will be created.
 *
 * @param string $path
 *   The path relative to files/pub_releases/site_name/
 *
 * @return string
 *   The current working directory.
 */
function _pub_qa_releases_batch_chdir($path) {
  // Create the releases directory in the files directory.
  $files = _pub_qa_releases_path() . 'pub7/';
  $full_path = $files . $path;

  return _pub_utilities_chdir($full_path);
}
