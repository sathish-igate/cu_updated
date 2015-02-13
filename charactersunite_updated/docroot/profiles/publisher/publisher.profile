<?php

// Include version.php which sets the PUBLISHER_VERSION constant.
include_once 'version.php';

/**
 * Implements hook_form_FORM_ID_alter().
 */
function publisher_form_install_configure_form_alter(&$form, $form_state) {
  $t = get_t();

  // Reset the current status messages in case a module adds a message on
  // installation. Those messages should not be displayed here.
  drupal_get_messages('status', TRUE);

  // Add fields to the "Site Information" to be used by sitecatalyst.
  $form['#submit'][] = 'publisher_form_install_configure_submit';
  $form['site_information']['division'] = array(
    '#type' => 'textfield',
    '#title' => 'Business Division',
    '#required' => TRUE,
    '#description' => 'Ex: Cable, News, Sports, etc.',
  );
  $form['site_information']['brand'] = array(
    '#type' => 'textfield',
    '#title' => 'Brand',
    '#required' => TRUE,
    '#description' => 'Ex: burnnotice.com would enter USA Network',
  );

  // Hide the server settings, and pre-populate the site default country.
  $form['server_settings']['#collapsible'] = TRUE;
  $form['server_settings']['#collapsed'] = TRUE;
  $form['server_settings']['site_default_country']['#default_value'] = 'US';

  // Turn off update notifications.
  $form['update_notifications']['#access'] = FALSE;
  $form['update_notifications']['update_status_module']['#default_value'] = array();
}

/**
 * Implements hook_requirements().
 */
function publisher_requirements($phase) {
  $requirements = array();
  // Ensure translations don't break during installation.
  $t = get_t();

  // Report Drupal version.
  if ($phase == 'runtime') {
    $requirements['publisher'] = array(
      'title' => $t('Publisher'),
      'value' => PUBLISHER_VERSION,
      'severity' => REQUIREMENT_INFO,
    );
  }

  // Dart, DFP, MPS.
  switch ($phase) {
    case 'runtime':
      $ad_modules = array();
      if (module_exists('dart')) {
        $ad_modules[] = $t('Dart (Classic Tags)');
      }
      if (module_exists('dfp')) {
        $ad_modules[] = $t('DFP (GPT Tags)');
      }
      if (module_exists('mps')) {
        $ad_modules[] = $t('MPS');
      }

      $requirements['ad_tags'] = array(
        'title' => $t('Ad Tag Style'),
        'value' => !empty($ad_modules) ? implode(' and ', $ad_modules) : $t('No ad tag module is installed.'),
        'severity' => count($ad_modules) > 1 ? REQUIREMENT_WARNING : REQUIREMENT_INFO,
        'description' => count($ad_modules) > 1 ? $t('Pub Ads should not be enabled without either the MPS module, the DART module, or the DFP module also being enabled (but just one of those).') : '',
      );
      break;
  }

  // Pixelman.
  $pix_mps = array();
  if (module_exists('pixelman')) {
    $pix_mps[] = $t('Pixelman');
  }
  if (module_exists('mps')) {
    $pix_mps[] = $t('MPS');
  }
  $requirements['pixelman'] = array(
    'title' => $t('Pixelman'),
    'value' => count($pix_mps) === 1 ? $t('The site is configured properly for Pixelman.') : $t('The site is not configured properly for Pixelman.'),
    'severity' => count($pix_mps) === 1 ? REQUIREMENT_OK : REQUIREMENT_ERROR,
    'description' => count($pix_mps) === 1 ? '' : $t('Either the MPS or Pixelman must be enabled but not both.'),
  );

  return $requirements;
}

/**
 * Implements hook_update_projects_alter().
 *
 * We use this to stop Drupal from checking for updates for any custom Publisher
 * modules.
 */
function publisher_update_projects_alter(&$projects) {
  foreach ($projects as $project) {
    $pub_ = substr($project['name'], 0, 4) === 'pub_';
    $package_publisher = isset($project['info']['package']) && $project['info']['package'] === 'Publisher';
    if ($pub_ || $package_publisher) {
      unset($projects[$project['name']]);
    }
  }
}

/**
 * Helper function that automatically sets the language to english.
 */
function _publisher_set_language(&$install_state) {
  $install_state['parameters']['locale'] = 'en';
}

/**
 * This call exists to ensure memcache is completely flushed.
 *
 * This is needed if a reinstall is ever performed on the Acquia cloud because
 * dropping the DB makes it difficult and the schema cache will become
 * problematic (particularly in the case of modified base templates like the
 * file_entity module adding a type column on the file_managed table).
 *
 * @param string $profile
 *   The name of the profile in question. This can be used for conditional
 *   setups.
 */
function _publisher_memcache_flush($profile) {
  if (module_load_include('inc', 'memcache', 'dmemcache')) {
    dmemcache_flush();
  }
}

/**
 * Helper function that initializes blocks.
 *
 * @param string $profile
 *   The name of the profile in question. This can be used for conditional
 *   setups.
 */
function _publisher_setup_blocks($profile) {
  $default_theme = variable_get('theme_default', 'bartik');
  $admin_theme = 'pub_sauce';

  // Enable some standard blocks.
  $blocks = array(
    array(
      'module' => 'system',
      'delta' => 'main',
      'theme' => $default_theme,
      'status' => 1,
      'weight' => 0,
      'region' => 'content',
      'pages' => '',
      'cache' => -1,
    ),
    array(
      'module' => 'user',
      'delta' => 'login',
      'theme' => $default_theme,
      'status' => 1,
      'weight' => 0,
      'region' => 'sidebar_first',
      'pages' => '',
      'cache' => -1,
    ),
    array(
      'module' => 'system',
      'delta' => 'navigation',
      'theme' => $default_theme,
      'status' => 1,
      'weight' => 0,
      'region' => 'sidebar_first',
      'pages' => '',
      'cache' => -1,
    ),
    array(
      'module' => 'system',
      'delta' => 'help',
      'theme' => $default_theme,
      'status' => 1,
      'weight' => 0,
      'region' => 'help',
      'pages' => '',
      'cache' => -1,
    ),
    array(
      'module' => 'system',
      'delta' => 'main',
      'theme' => $admin_theme,
      'status' => 1,
      'weight' => 0,
      'region' => 'content',
      'pages' => '',
      'cache' => -1,
    ),
    array(
      'module' => 'system',
      'delta' => 'help',
      'theme' => $admin_theme,
      'status' => 1,
      'weight' => 0,
      'region' => 'help',
      'pages' => '',
      'cache' => -1,
    ),
    array(
      'module' => 'user',
      'delta' => 'login',
      'theme' => $admin_theme,
      'status' => 1,
      'weight' => 10,
      'region' => 'content',
      'pages' => '',
      'cache' => -1,
    ),
  );
  $query = db_insert('block')->fields(array(
    'module',
    'delta',
    'theme',
    'status',
    'weight',
    'region',
    'pages',
    'cache',
  ));
  foreach ($blocks as $block) {
    $query->values($block);
  }
  $query->execute();
}

/**
 * Helper function that creates and configures users, roles, permissions, etc.
 *
 * @param string $profile
 *   The name of the profile in question. This can be used for conditional
 *   setups.
 */
function _publisher_setup_users($profile) {
  // Only allow administrators to create new user accounts.
  variable_set('user_register', USER_REGISTER_ADMINISTRATORS_ONLY);

  // Enable default permissions for system roles.
  if (module_exists('comment')) {
    user_role_grant_permissions(DRUPAL_ANONYMOUS_RID, array(
        'access content',
        'access comments',
        'view files')
    );
    user_role_grant_permissions(DRUPAL_AUTHENTICATED_RID, array(
        'access administration pages',
        'access content',
        'administer shortcuts',
        'cancel account',
        'customize shortcut links',
        'switch shortcut sets',
        'view files')
    );
  }

  // Create a default role for site administrators, with all available
  // permissions assigned.
  $admin_role = new stdClass();
  $admin_role->name = 'administrator';
  $admin_role->weight = 2;
  user_role_save($admin_role);
  user_role_grant_permissions($admin_role->rid, array_keys(module_invoke_all('permission')));
  // Set this as the administrator role.
  variable_set('user_admin_role', $admin_role->rid);

  // Assign user 1 the "administrator" role.
  db_insert('users_roles')
    ->fields(array('uid' => 1, 'rid' => $admin_role->rid))
    ->execute();
}

/**
 * Helper function that configures menus.
 *
 * @param string $profile
 *   The name of the profile in question. This can be used for conditional
 *   setups.
 */
function _publisher_setup_menus($profile) {
  // Create a Home link in the main menu.
  $item = array(
    'link_title' => st('Home'),
    'link_path' => '<front>',
    'menu_name' => 'main-menu',
  );
  menu_link_save($item);

  // Update the menu router information.
  menu_rebuild();
}

/**
 * Helper function that configures themes.
 *
 * @param string $profile
 *   The name of the profile in question. This can be used for conditional
 *   setups.
 */
function _publisher_setup_themes($profile) {
  // Set the default admin theme - Pub Sauce.
  variable_set("admin_theme", "pub_ember");
  variable_set('node_admin_theme', '1');

  // Disable the Seven theme.
  theme_disable(array("seven"));
}

/**
 * WYSIWYG text format and profile setup.
 *
 * Helper function that handles the initial setup of the WYSIWYG text format and
 * default WYSIWYG profiles.
 *
 * @param string $profile
 *   The name of the profile in question. This can be used for conditional
 *   setups.
 */
function _publisher_setup_wysiwyg($profile) {
  // Create a WYSIWYG input filter.
  $wysiwyg_basic_format = array(
    'format' => 'wysiwyg_basic',
    'name' => 'WYSIWYG Basic',
    'cache' => '1',
    'status' => '1',
    'weight' => '-10',
    'filters' => array(
      'filter_html' => array(
        'weight' => '-50',
        'status' => '1',
        'settings' => array(
          'allowed_html' => '<p> <a> <em> <strong> <strike> <cite> <code> <ul> <ol> <li> <dl> <dt> <dd> <img> <table> <tbody> <tr> <td> <th> <tbody> <caption> <thead> <tfoot> <h1> <h2> <h3> <h4> <h5> <h6> <blockquote> <hr> <span> <br> <sup> <sub> <div> <article> <aside>',
          'filter_html_help' => 0,
          'filter_html_nofollow' => 1,
        ),
      ),
      'media_filter' => array(
        'weight' => '-46',
        'status' => '1',
        'settings' => array(),
      ),
      'filter_url' => array(
        'weight' => '-45',
        'status' => '1',
        'settings' => array(
          'filter_url_length' => '72',
        ),
      ),
      'filter_htmlcorrector' => array(
        'weight' => '-44',
        'status' => '1',
        'settings' => array(),
      ),
    ),
  );
  $wysiwyg_basic_format = (object) $wysiwyg_basic_format;
  filter_format_save($wysiwyg_basic_format);

  // Create the default WYSIWYG profile for the wysiwyg_basic filter.
  $wysiwyg_profile = array(
    'format' => 'wysiwyg_basic',
    'editor' => 'tinymce',
    'settings' => array(
      'default' => 1,
      'user_choose' => 0,
      'show_toggle' => 0,
      'theme' => 'advanced',
      'language' => 'en',
      'buttons' => array(
        'default' => array(
          'bold' => 1,
          'italic' => 1,
          'justifyleft' => 1,
          'justifycenter' => 1,
          'justifyright' => 1,
          'bullist' => 1,
          'numlist' => 1,
          'undo' => 1,
          'redo' => 1,
          'link' => 1,
          'unlink' => 1,
          'code' => 1,
          'cut' => 1,
          'copy' => 1,
          'charmap' => 1,
        ),
        'paste' => array(
          'pasteword' => 1,
        ),
        'drupal' => array(),
      ),
      'toolbar_loc' => 'top',
      'toolbar_align' => 'left',
      'path_loc' => 'bottom',
      'resizing' => 1,
      'verify_html' => 1,
      'preformatted' => 0,
      'convert_fonts_to_spans' => 1,
      'remove_linebreaks' => 0,
      'apply_source_formatting' => 1,
      'paste_auto_cleanup_on_paste' => 1,
      'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div,aside,article',
      'css_setting' => 'theme',
      'css_path' => '',
      'css_classes' => '',
    ),
  );
  db_merge('wysiwyg')
    ->key(array('format' => $wysiwyg_profile['format']))
    ->fields(array(
      'editor' => $wysiwyg_profile['editor'],
      'settings' => serialize($wysiwyg_profile['settings']),
    ))
    ->execute();


  /*
  * Create a mini WYSIWYG input filter.
  */
  $wysiwyg_mini_format = array(
    'format' => 'wysiwyg_mini',
    'name' => 'WYSIWYG Mini',
    'cache' => '1',
    'status' => '1',
    'weight' => '-10',
    'filters' => array(
      'filter_html' => array(
        'weight' => '-50',
        'status' => '1',
        'settings' => array(
          'allowed_html' => '<p> <a> <em> <strong> <strike> <cite> <code> <ul> <ol> <li> <dl> <dt> <dd> <img> <table> <tbody> <tr> <td> <th> <tbody> <caption> <thead> <tfoot> <h1> <h2> <h3> <h4> <h5> <h6> <blockquote> <hr> <span> <br> <sup> <sub> <div> <article> <aside>',
          'filter_html_help' => 0,
          'filter_html_nofollow' => 1,
        ),
      ),
      'media_filter' => array(
        'weight' => '-46',
        'status' => '1',
        'settings' => array(),
      ),
      'filter_url' => array(
        'weight' => '-45',
        'status' => '1',
        'settings' => array(
          'filter_url_length' => '72',
        ),
      ),
      'filter_htmlcorrector' => array(
        'weight' => '-44',
        'status' => '1',
        'settings' => array(),
      ),
    ),
  );
  $wysiwyg_mini_format = (object) $wysiwyg_mini_format;
  filter_format_save($wysiwyg_mini_format);

  // Create the mini WYSIWYG profile for the wysiwyg_mini filter declared above.
  $wysiwyg_mini_profile = array(
    'format' => 'wysiwyg_mini',
    'editor' => 'tinymce',
    'settings' => array(
      'default' => 1,
      'user_choose' => 0,
      'show_toggle' => 0,
      'theme' => 'advanced',
      'language' => 'en',
      'buttons' => array(
        'default' => array(
          'bold' => 1,
          'italic' => 1,
          'link' => 1,
        ),
      ),
      'toolbar_loc' => 'top',
      'toolbar_align' => 'left',
      'path_loc' => 'none',
      'resizing' => 1,
      'verify_html' => 1,
      'preformatted' => 0,
      'convert_fonts_to_spans' => 1,
      'remove_linebreaks' => 0,
      'apply_source_formatting' => 1,
      'paste_auto_cleanup_on_paste' => 1,
      'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div,aside,article',
      'css_setting' => 'theme',
      'css_path' => '',
      'css_classes' => '',
    ),
  );
  db_merge('wysiwyg')
    ->key(array('format' => $wysiwyg_mini_profile['format']))
    ->fields(array(
      'editor' => $wysiwyg_mini_profile['editor'],
      'settings' => serialize($wysiwyg_mini_profile['settings']),
    ))
    ->execute();
}

/**
 * Helper function that handles roles and permissions.
 *
 * This should only be called during the "final steps" step of installation.
 *
 * @param string $profile
 *   The name of the profile in question. This can be used for conditional
 *   setups.
 */
function _publisher_setup_permissions($profile) {
  // Get a list of all the modules installed and set their permissions.
  $modules = array_keys(system_list('module_enabled'));
  publisher_modules_installed($modules);
}

/**
 * Helper function that handles general module settings.
 *
 * @param string $profile
 *   The name of the profile in question. This can be used for conditional
 *   setups.
 */
function _publisher_setup_settings($profile) {
  // NOTE: We no longer enable a site specific module. 4/2/2013.
  // If a module exists with the same name as the current sites folder, enable
  // it.
  // $conf_path_split = explode('/', conf_path());
  // $site_shortname = array_pop($conf_path_split);

  // $present_modules = drupal_system_listing('/^' . DRUPAL_PHP_FUNCTION_PATTERN . '\.module$/', 'modules', 'name', 0);
  // if (array_key_exists($site_shortname, $present_modules)) {
  //    module_enable(array($site_shortname));
  // }

  // Set the default settings for imagefield_focus.
  $focus_settings = array(
    'focus' => '1',
    'focus_lock_ratio' => '',
    'focus_min_size' => '',
  );
  variable_set('imagefield_focus_media_settings', $focus_settings);

  // Set the default settings for node images in the nodequeue ordering form.
  $nodequeue_image_settings = array(
    'show_image' => 1,
    'image_style' => 'thumbnail',
  );
  variable_set('nodequeue_image', $nodequeue_image_settings);
}

/**
 * Implements hook_wysiwyg_editor_settings_alter().
 *
 * Even though all buttons are listed, only those that are enabled in the
 * WYSIWYG configuration will be displayed.
 */
function publisher_wysiwyg_editor_settings_alter(&$settings, $context) {
  switch ($context['profile']->editor) {
    case "ckeditor":
      // These are our desired groupings. Buttons that aren't listed here will
      // be grouped in one big group at the end.
      $preferred_groupings[] = array('Source');
      $preferred_groupings[] = array('Bold', 'Italic', 'Underline', 'Strike');
      $preferred_groupings[] = array(
        'JustifyLeft',
        'JustifyCenter',
        'JustifyRight',
        'JustifyBlock',
      );
      $preferred_groupings[] = array(
        'BulletedList',
        'NumberedList',
        'Outdent',
        'Indent',
      );
      $preferred_groupings[] = array('Undo', 'Redo');
      $preferred_groupings[] = array('Image', 'Link', 'Unlink', 'Anchor', '-');
      $preferred_groupings[] = array('TextColor', 'BGColor');
      $preferred_groupings[] = array('Superscript', 'Subscript', 'Blockquote');
      $preferred_groupings[] = array('HorizontalRule', 'break');
      $preferred_groupings[] = array(
        'Cut',
        'Copy',
        'Paste',
        'PasteText',
        'PasteFromWord',
      );
      $preferred_groupings[] = array(
        'ShowBlocks',
        'RemoveFormat',
        'SpecialChar',
        '/',
      );
      $preferred_groupings[] = array(
        'Format',
        'Font',
        'FontSize',
        'Styles',
        'Table',
      );
      $preferred_groupings[] = array('SelectAll', 'Find', 'Replace');
      $preferred_groupings[] = array('Flash', 'Smiley');
      $preferred_groupings[] = array(
        'CreateDiv',
        'Maximize',
        'SpellChecker',
        'Scayt',
      );

      // An array to hold our newly grouped buttons.
      $new_grouped_toolbar = array();

      // Compare each desired groupings to the configured buttons in the toolbar
      // and add them if they are there.
      foreach ($preferred_groupings as $button_group) {
        $matching_buttons = array_intersect($button_group, $settings['toolbar'][0]);

        if (!empty($matching_buttons)) {
          $new_grouped_toolbar[] = array_values($matching_buttons);
        }

      }

      // Find any remaining buttons that we missed.
      $new_flattened_toolbar = array();
      foreach ($new_grouped_toolbar as $key => $group) {
        $new_flattened_toolbar = array_merge($new_flattened_toolbar, $group);
      }
      $remaining_buttons = array_diff($settings['toolbar'][0], $new_flattened_toolbar);
      if (!empty($remaining_buttons)) {
        // Reset the array keys and add it to the $new_grouped_toolbar.
        $new_grouped_toolbar[] = array_values($remaining_buttons);
      }

      // Replace the toolbar with our new, grouped toolbar.
      $settings['toolbar'] = $new_grouped_toolbar;

      break;

    case "tinymce":
      // These are our desired groupings. Buttons that aren't listed here will
      // be grouped in one big group at the end.
      $preferred_groupings[] = explode(',', "bold,italic,underline,strikethrough,sup,sub");
      $preferred_groupings[] = explode(',', "bullist,numlist,outdent,indent");
      $preferred_groupings[] = explode(',', "formatselect,styleselect,removeformat");
      $preferred_groupings[] = explode(',', "justifyleft,justifycenter,justifyright,justifyfull");
      $preferred_groupings[] = explode(',', "hr,charmap,blockquote,anchorcut");
      $preferred_groupings[] = explode(',', "anchor,link,unlink,image,media");
      $preferred_groupings[] = explode(',', "cut,copy,paste,pastetext,pasteword,removeformat,paste_auto_cleanup_on_paste,cleanup");
      $preferred_groupings[] = explode(',', "iespell,code,fullscreen,undo,redo");

      $existing_buttons = explode(',', $settings['theme_advanced_buttons1'] . $settings['theme_advanced_buttons2'] . $settings['theme_advanced_buttons3']);
      $new_grouped_toolbar = array();

      // First, get a list of existing buttons that have no preferred position.
      $remaining_buttons = array();
      foreach ($existing_buttons as $button) {
        foreach ($preferred_groupings as $key => $group) {
          if (in_array($button, $group)) {
            continue(2);
          }
        }
        $remaining_buttons[] = $button;
      }

      // Compare each desired groupings to the configured buttons in the toolbar
      // and add them if they are there.
      foreach ($preferred_groupings as $button_group) {
        $matching_buttons = array_intersect($button_group, $existing_buttons);

        if (!empty($matching_buttons)) {
          $new_grouped_toolbar[] = implode(',', array_values($matching_buttons));
        }
      }

      if (!empty($remaining_buttons)) {
        $new_grouped_toolbar[] = implode(',', array_values($remaining_buttons));
      }

      $settings['theme_advanced_buttons1'] = implode(',separator,', $new_grouped_toolbar);
      $settings['theme_advanced_buttons2'] = '';
      $settings['theme_advanced_buttons3'] = '';
      break;
  }
}

/**
 * Publisher Profile Switch.
 */
function publisher_update_profiles() {
  drupal_static_reset();

  $old_profile = variable_get('install_profile', '');
  $new_profile = 'publisher';
  variable_set('install_profile', $new_profile);

  db_query("UPDATE system SET filename = REPLACE(filename, :from_directory, :to_directory) WHERE filename like :match_phrase",
    array(':from_directory' => 'profiles/all/', ':to_directory' => 'profiles/publisher/', ':match_phrase' => 'profiles/all/%'));

  // Unlike modules, profiles aren't added to the system table just because the
  // files are added to /profiles.  They are added after they are active.  We
  // need to add them before that so they are BOTH active and enabled.

  // Cache a fully-built schema.
  drupal_get_schema(NULL, TRUE);
  system_rebuild_module_data();

  db_update('system')
    ->fields(array(
      'status' => 1,
    ))
    ->condition('name', $new_profile, '=')
    ->execute();

  db_update('system')
    ->fields(array(
      'status' => 0,
      'schema_version' => 0,
    ))
    ->condition('name', $old_profile, '=')
    ->execute();

  drupal_flush_all_caches();
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function publisher_form_field_ui_field_edit_form_alter(&$form, &$form_state) {
  $directory = '';
  if (isset($form['instance']['settings']['file_directory']['#default_value'])) {
    $directory = $form['instance']['settings']['file_directory']['#default_value'];
  }

  if (strpos($directory, '[current-date:custom:Y]' . '/' . '[current-date:custom:m]') === FALSE) {
    if (strlen($directory) > 0) {
      $directory .= '/';
    }
    $directory .= '[current-date:custom:Y]' . '/' . '[current-date:custom:m]';
  }

  $description = t('Optional subdirectory within the upload destination where files will be stored.  Defaults to subdirectories grouped by years and their months.  Do not include preceding or trailing slashes.');

  $form['instance']['settings']['file_directory']['#default_value'] = $directory;
  $form['instance']['settings']['file_directory']['#description'] = $description;
  $form['instance']['settings']['file_directory']['#disabled'] = TRUE;
}

/**
 * Implements hook_module_implements_alter().
 */
function publisher_module_implements_alter(&$implementations, $hook) {
  if ($hook == 'init') {
    unset($implementations['update']);
  }
}

/**
 * Rebuild the module data and clear the cache.
 *
 * In anticipation of the profiles/all directory being removed.
 */
function publisher_update_7001() {
  registry_rebuild();
  drupal_flush_all_caches();
}

/**
 * Update the Publisher profile schema to be 0, not -1.
 *
 * @see pub_editorial_update_7003()
 */
function publisher_update_7002() {
  db_update('system')
    ->fields(array(
      'schema_version' => 0,
    ))
  ->condition('schema_version', 0, '<')
  ->condition('name', 'publisher')
  ->execute();
}

/**
 * Enable the Media bulk upload module.
 *
 * As of media 2.0-alpha4, bulk upload is a separate module.
 */
function publisher_update_7003() {
  if (module_exists('media')) {
    module_enable(array('media_bulk_upload'));
  }
}

/**
 * Enable the status_watchdog module.
 */
function publisher_update_7004() {
  module_enable(array('status_watchdog'));
}
