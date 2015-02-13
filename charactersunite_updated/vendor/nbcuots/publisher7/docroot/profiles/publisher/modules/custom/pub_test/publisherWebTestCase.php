<?php

class PublisherWebTestCase extends DrupalWebTestCase {

  /**
   * The profile to install as a basis for testing.
   *
   * @var string
   */
  protected $profile = 'publisher';


  /**
   * Create a user with a role.
   *
   * @param String $role
   *
   * @return bool|false|object|stdClass
   */
  protected function drupalCreateUserWithRole($role) {
    $rid = FALSE;
    $role = user_role_load_by_name($role);

    // Create a role with the given permission set, if any.
    if ($role !== FALSE) {
      $rid = $role->rid;
    }

    if (!$rid) {
      return FALSE;
    }

    // Create a user assigned to that role.
    $edit = array();
    $edit['name'] = $this->randomName();
    $edit['mail'] = $edit['name'] . '@example.com';
    $edit['pass'] = user_password();
    $edit['status'] = 1;
    if ($rid) {
      $edit['roles'] = array($rid => $rid);
    }

    $account = user_save(drupal_anonymous_user(), $edit);

    $this->assertTrue(!empty($account->uid), t('User created with name %name and pass %pass', array('%name' => $edit['name'], '%pass' => $edit['pass'])), t('User login'));
    if (empty($account->uid)) {
      return FALSE;
    }

    // Add the raw password so that we can log in as this user.
    $account->pass_raw = $edit['pass'];
    return $account;
  }

  /**
   * Login with the Publisher profile.
   *
   * This DrupalWebTestCase method in order to be able to login using email.
   *
   * @param stdClass $account
   *
   * @see DrupalWebTestCase::drupalLogin
   */
  protected function drupalLogin(stdClass $account) {
    if ($this->loggedInUser) {
      $this->drupalLogout();
    }

    $edit = array(
      'name' => $account->mail,
      'pass' => $account->pass_raw,
    );
    $this->drupalPost('user', $edit, t('Log in'));

    // If a "log out" link appears on the page, it is almost certainly because
    // the login was successful.
    $pass = $this->assertLink(t('Log out'), 0, t('User %name successfully logged in.', array('%name' => $account->name)), t('User login'));

    if ($pass) {
      $this->loggedInUser = $account;
    }
  }

  /**
   * Alters DrupalWebTestCase::setUp() to fix some issue.
   *
   * allow profiles modules to install
   * dependencies.
   *
   * Sets up a Drupal site for running functional and integration tests.
   *
   * Generates a random database prefix and installs Drupal with the specified
   * installation profile in DrupalWebTestCase::$profile into the
   * prefixed database. Afterwards, installs any additional modules specified by
   * the test.
   *
   * After installation all caches are flushed and several configuration values
   * are reset to the values of the parent site executing the test, since the
   * default values may be incompatible with the environment in which tests are
   * being executed.
   *
   * @param ...
   *   List of modules to enable for the duration of the test. This can be
   *   either a single array or a variable number of string arguments.
   *
   * @return NULL
   *
   * @see DrupalWebTestCase::prepareDatabasePrefix()
   * @see DrupalWebTestCase::changeDatabasePrefix()
   * @see DrupalWebTestCase::prepareEnvironment()
   */
  protected function setUp() {
    global $user, $language, $conf;

    // Create the database prefix for this test.
    $this->prepareDatabasePrefix();

    // Prepare the environment for running tests.
    $this->prepareEnvironment();
    if (!$this->setupEnvironment) {
      return FALSE;
    }

    // Reset all statics and variables to perform tests in a clean environment.
    $conf = array();
    drupal_static_reset();

    // Change the database prefix.
    // All static variables need to be reset before the database prefix is
    // changed, since DrupalCacheArray implementations attempt to
    // write back to persistent caches when they are destructed.
    $this->changeDatabasePrefix();
    if (!$this->setupDatabasePrefix) {
      return FALSE;
    }

    // Preset the 'install_profile' system variable, so the first call into
    // system_rebuild_module_data() (in drupal_install_system()) will register
    // the test's profile as a module. Without this, the installation profile of
    // the parent site (executing the test) is registered, and the testprofile
    // 's hook_install() and other hook implementations are never invoked.
    $conf['install_profile'] = $this->profile;

    // Perform the actual Drupal installation.
    include_once DRUPAL_ROOT . '/includes/install.inc';
    drupal_install_system();

    $this->preloadRegistry();

    // Set path variables.
    variable_set('file_public_path', $this->public_files_directory);
    variable_set('file_private_path', $this->private_files_directory);
    variable_set('file_temporary_path', $this->temp_files_directory);

    // Set the 'simpletest_parent_profile' variable to add the parent profile's
    // search path to the child site's search paths.
    // @see drupal_system_listing()
    // @todo This may need to be primed like 'install_profile' above.
    variable_set('simpletest_parent_profile', $this->originalProfile);

    // Include the testing profile.
    variable_set('install_profile', $this->profile);
    $profile_details = install_profile_info($this->profile, 'en');

    // Install the modules specified by the testing profile.
    // Publisher: Modified from FALSE to TRUE as the second param and add the
    // user module. Also enable the user module first just like the regular
    // installer does.
    module_enable(array('user'), FALSE);
    module_enable($profile_details['dependencies'], TRUE);

    // Install modules needed for this test. This could have been passed in as
    // either a single array argument or a variable number of string arguments.
    // @todo Remove this compatibility layer in Drupal 8, and only accept
    // $modules as a single array argument.
    $modules = func_get_args();
    if (isset($modules[0]) && is_array($modules[0])) {
      $modules = $modules[0];
    }
    if ($modules) {
      $success = module_enable($modules, TRUE);
      $this->assertTrue($success, t('Enabled modules: %modules', array('%modules' => implode(', ', $modules))));
    }

    // Run the profile tasks.
    $install_profile_module_exists = db_query("SELECT 1 FROM {system} WHERE type = 'module' AND name = :name", array(
      ':name' => $this->profile,
    ))->fetchField();
    if ($install_profile_module_exists) {
      module_enable(array($this->profile), FALSE);
    }

    // Reset/rebuild all data structures after enabling the modules.
    $this->resetAll();

    // Run cron once in that environment, as install.php does at the end of
    // the installation process.
    drupal_cron_run();

    // Ensure that the session is not written to the new environment and replace
    // the global $user session with uid 1 from the new test site.
    drupal_save_session(FALSE);
    // Login as uid 1.
    $user = user_load(1);

    // Restore necessary variables.
    variable_set('install_task', 'done');
    variable_set('clean_url', $this->originalCleanUrl);
    variable_set('site_mail', 'simpletest@example.com');
    variable_set('date_default_timezone', date_default_timezone_get());

    // Set up English language.
    unset($conf['language_default']);
    $language = language_default();

    // Use the test mail class instead of the default mail handler class.
    variable_set('mail_system', array('default-system' => 'TestingMailSystem'));

    drupal_set_time_limit($this->timeLimit);
    $this->setup = TRUE;
  }
}
