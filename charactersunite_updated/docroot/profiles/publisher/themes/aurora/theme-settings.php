<?php
/**
 * Implements hook_form_system_theme_settings_alter() function.
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function aurora_form_system_theme_settings_alter(&$form, &$form_state, $form_id = NULL) {
  // Work-around for a core bug affecting admin themes. See issue #943212.
  // From the always awesome Zen
  if (isset($form_id)) {
   return;
  }
  drupal_add_css(drupal_get_path('theme', 'aurora') . '/css/settings.css');

  //////////////////////////////
  // Chrome Frame
  //////////////////////////////

  $form['chromeframe'] = array(
  '#type' => 'fieldset',
  '#title' => t('Chrome Frame'),
  '#description' => t('Google\'s Chrome Frame is an open source project for Internet Explorer 6, 7, 8, and 9 that allows those version of Internet Explorer to <a href="!link target="_blank">harness the power of Google Chrome\'s engine</a>.', array('!link' => 'https://www.youtube.com/watch?v=sjW0Bchdj-w&feature=player_embedded"')),
  '#weight' => -100,
  '#attributes' => array('class' => array('aurora-row-left')),
  '#prefix' => '<span class="aurora-settigns-row">',
  '#parents' => array('vtb'),
  );

  $form['chromeframe']['aurora_enable_chrome_frame'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Chrome Frame'),
    '#default_value' => theme_get_setting('aurora_enable_chrome_frame'),
    '#ajax' => array(
      'callback' => 'aurora_chromeframe_options',
      'wrapper' => 'cf-settings',
      'method' => 'replace'
    ),

   );

  $form['chromeframe']['aurora_min_ie_support'] = array(
    '#type' => 'select',
    '#title' => t('Minimum supported Internet Explorer version'),
    '#options' => array(
      10 => t('Internet Explorer 10'),
      9 => t('Internet Explorer 9'),
      8 => t('Internet Explorer 8'),
      7 => t('Internet Explorer 7'),
      6 => t('Internet Explorer 6'),
    ),
    '#default_value' => theme_get_setting('aurora_min_ie_support'),
    '#description' => t('The minimum version number of Internet Explorer that you actively support. The Chrome Frame prompt will display for any version below this version number.'),
    '#prefix' => '<span id="cf-settings">',
    '#suffix' => '</span>',
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
     ),
  );

  if (theme_get_setting('aurora_enable_chrome_frame') || $form_state['rebuild']) {
   if ($form_state['rebuild']) {
     if ($form_state['triggering_element']['#name'] == 'aurora_enable_chrome_frame') {
       if ($form_state['triggering_element']['#value'] == 1) {

         $form['chromeframe']['aurora_min_ie_support']['#disabled'] = false;
       }
       else {
         $form['chromeframe']['aurora_min_ie_support']['#disabled'] = true;
       }
     }
   }
   else {
     $form['chromeframe']['aurora_min_ie_support']['#disabled'] = false;
   }
  }
  else {
   $form['chromeframe']['aurora_min_ie_support']['#disabled'] = true;
  }

  //////////////////////////////
  // Miscelaneous
  //////////////////////////////

  $form['misc'] = array(
   '#type' => 'fieldset',
   '#title' => t('Miscelaneous'),
   '#description' => t('Various little bits and bobs for your theme.'),
   '#weight' => -99,
   '#attributes' => array('class' => array('aurora-row-right')),
   '#suffix' => '</span>',
  );

  $form['misc']['aurora_remove_core_css'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove Core CSS'),
    '#default_value' => theme_get_setting('aurora_remove_core_css'),
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
    ),
    '#description' => t('Removes all Core provided CSS files.'),
  );

  $form['misc']['aurora_html_tags'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prune HTML Tags'),
    '#default_value' => theme_get_setting('aurora_html_tags'),
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
    ),
    '#description' => t('Prunes your <pre>style</pre>, <pre>link</pre>, and <pre>script</pre> tags as <a href="!link" target="_blank"> suggested by Nathan Smith</a>.', array('!link' => 'http://sonspring.com/journal/html5-in-drupal-7#_pruning')),
  );

  $form['misc']['aurora_typekit_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Typekit Kit ID'),
    '#default_value' => theme_get_setting('aurora_typekit_id'),
    '#size' => 7,
    '#maxlength' => 7,
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
    ),
    '#description' => t('If you are using <a href="!link" target="_blank">Typekit</a> to serve webfonts, put your Typekit Kit ID here', array('!link' => 'https://typekit.com/')),
  );


  //////////////////////////////
  // JavaScript
  //////////////////////////////
  $form['javascript'] = array(
    '#type' => 'fieldset',
    '#title' => t('JavaScript'),
    '#weight' => -98,
    '#description' => t('A pile of JavaScript options for you to use and abuse. <div class="messages warning"><strong>WARNING:</strong> Some of these options may wind up breaking existing JavaScript. Use with caution.</div>'),
  );

  $form['javascript']['aurora_footer_js'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move JavaScript to the Bottom'),
    '#default_value' => theme_get_setting('aurora_footer_js'),
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
    ),
    '#description' => t('Will move all JavaScript to the bottom of your page. This can be overridden on an individual basis by setting the <pre>\'force header\' => true</pre> option in <pre>drupal_add_js</pre> or by using <pre>hook_js_alter</pre> to add the option to other JavaScript files.'),
    '#ajax' => array(
      'callback' => 'aurora_js_footer',
      'wrapper' => 'jsh-settings',
      'method' => 'replace'
    ),
  );

  $form['javascript']['aurora_libraries_head'] = array(
    '#type' => 'checkbox',
    '#title' => t('Keep Libraries in the Head'),
    '#default_value' => theme_get_setting('aurora_libraries_head'),
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
    ),
    '#prefix' => '<span id="jsh-settings">',
    '#suffix' => '</span>',
    '#description' => t('If you have JavaScript inline in the body of your document, such as if you are displaying ads, you may need to keep Drupal JS Libraries in the head instead of moving them to the footer. This will keep Drupal libraries in the head while moving all other JavaScript to the footer.'),
  );

  if (theme_get_setting('aurora_footer_js') || $form_state['rebuild']) {
   if ($form_state['rebuild']) {
     if ($form_state['triggering_element']['#name'] == 'aurora_footer_js') {
       if ($form_state['triggering_element']['#value'] == 1) {

         $form['javascript']['aurora_libraries_head']['#disabled'] = false;
       }
       else {
         $form['javascript']['aurora_libraries_head']['#disabled'] = true;
       }
     }
   }
   else {
     $form['javascript']['aurora_libraries_head']['#disabled'] = false;
   }
  }
  else {
   $form['javascript']['aurora_libraries_head']['#disabled'] = true;
  }

  //////////////////////////////
  // Development
  //////////////////////////////

  $form['development'] = array(
    '#type' => 'fieldset',
    '#title' => t('Development'),
    '#description' => t('Theme like you\'ve never themed before! <div class="messages warning"><strong>WARNING:</strong> These options incur huge performance penalties and <em>must</em> be turned off on production websites.</div>'),
    '#weight' => 52
  );

  $form['development']['aurora_rebuild_registry'] = array(
    '#type' => 'checkbox',
    '#title' => t('Rebuild Theme Registry on Reload'),
    '#default_value' => theme_get_setting('aurora_rebuild_registry'),
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
    ),
    '#description' => t('<a href="!link" target="_blank">Rebuild the theme registry</a> during project development.', array('!link' => 'http://drupal.org/node/173880#theme-registry')),
  );

  // $form['development']['aurora_uncompressed_jquery'] = array(
  //   '#type' => 'checkbox',
  //   '#title' => t('Use uncompressed jQuery'),
  //   '#default_value' => theme_get_setting('aurora_uncompressed_jquery'),
  //   '#description' => t('If you are loading your jQuery from a CDN, selecting this will use the uncompressed version of jQuery. Do not use on production sites.'),
  // );

  $form['development']['aurora_livereload'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable LiveReload'),
    '#default_value' => theme_get_setting('aurora_livereload'),
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
    ),
    '#description' => t('Enable <a href="!link" target="_blank">LiveReload</a> to refresh your browser without you needing to. Awesome for designing in browser.', array('!link' => 'http://livereload.com/')),
    '#weight' => 200,
  );

  $form['development']['aurora_viewport_width'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Viewport Width Indicator'),
    '#default_value' => theme_get_setting('aurora_viewport_width'),
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
    ),
    '#description' => t('Displays an indicator of the viewport. Tap/click to toggle between <em>em</em> and <em>px</em>/'),
    '#weight' => 225,
  );

  $options = array('attributes' => array('target' => '_blank'));
  $form['development']['aurora_modernizr_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Modernizr Indicator'),
    '#default_value' => theme_get_setting('aurora_modernizr_debug'),
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
    ),
    '#description' => t('Displays an indicator of !modernizr detected features. Tap/click to toggle display of all of the available features. Install the !module for full Modernizr support.', array('!modernizr' => l('Modernizr', 'http://modernizr.com/', $options), '!module' => l('Modernizr Drupal module', 'http://drupal.org/project/modernizr', $options))),
    '#weight' => 250,
  );

  //////////////////////////////
  // Experimental Options
  //////////////////////////////
  $form['experimental'] = array(
    '#type' => 'fieldset',
    '#title' => t('Experimental'),
    '#description' => t('You like bleeding? We\'ve got your bleeding edge! <div class="messages warning"><strong>WARNING:</strong> Abandon hope all ye who enter here! These options are <em>very</em> experimental and may break things, use with caution.</div>'),
    '#weight' => 53
  );

  $form['experimental']['aurora_custom_js_handling'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Experimental JavaScript Handling'),
    '#default_value' => theme_get_setting('aurora_custom_js_handling'),
    '#ajax' => array(
      'callback' => 'aurora_ajax_settings_save'
    ),
    '#description' => t('Enable experimental JavaScript handling, including defer, async, and browser specific JavaScript.'),
  );

  //////////////////////////////
  // Theme Settings Update
  //////////////////////////////
  unset($form['theme_settings']['toggle_main_menu']);
  unset($form['theme_settings']['toggle_secondary_menu']);
  $form['theme_settings']['toggle_breadcrumbs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Breadcrumbs'),
    '#default_value' => theme_get_setting('toggle_breadcrumbs'),
  );

  $form['theme_settings']['toggle_logo']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');
  $form['theme_settings']['toggle_name']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');
  $form['theme_settings']['toggle_slogan']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');
  $form['theme_settings']['toggle_node_user_picture']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');
  $form['theme_settings']['toggle_comment_user_picture']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');
  $form['theme_settings']['toggle_comment_user_verification']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');
  $form['theme_settings']['toggle_favicon']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');
  $form['theme_settings']['toggle_breadcrumbs']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');

  //////////////////////////////
  // Logo and Favicon
  //////////////////////////////
  $form['logo']['#weight'] = 10;
  $form['logo']['#attributes']['class'][] = 'aurora-row-left';
  $form['logo']['#prefix'] = '<span class="aurora-settigns-row">';
  $form['logo']['default_logo']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');

  $form['favicon']['#weight'] = 11;
  $form['favicon']['#attributes']['class'][] = 'aurora-row-right';
  $form['favicon']['#suffix'] = '</span>';
  $form['favicon']['default_favicon']['#ajax'] = array('callback' => 'aurora_ajax_settings_save');
}

function aurora_chromeframe_options($form, $form_state) {
  $theme = $form_state['build_info']['args'][0];
  $theme_settings = variable_get('theme_' . $theme . '_settings', array());

  $theme_settings['aurora_enable_chrome_frame'] = $form_state['input']['aurora_enable_chrome_frame'];
  variable_set('theme_' . $theme . '_settings', $theme_settings);

  if ($form_state['input']['aurora_enable_chrome_frame'] == 1) {
    $form['chromeframe']['aurora_min_ie_support']['#disabled'] = false;
    return drupal_render($form['chromeframe']['aurora_min_ie_support']);
  }
  else {
    $form['chromeframe']['aurora_min_ie_support']['#disabled'] = true;
    return drupal_render($form['chromeframe']['aurora_min_ie_support']);
  }
  return '';
}

function aurora_js_footer($form, $form_state) {
  $theme = $form_state['build_info']['args'][0];
  $theme_settings = variable_get('theme_' . $theme . '_settings', array());

  $theme_settings['aurora_footer_js'] = $form_state['input']['aurora_footer_js'];
  variable_set('theme_' . $theme . '_settings', $theme_settings);

  if ($form_state['input']['aurora_footer_js'] == 1) {
    $form['javascript']['aurora_libraries_head']['#disabled'] = false;
    return drupal_render($form['javascript']['aurora_libraries_head']);
  }
  else {
    $form['javascript']['aurora_libraries_head']['#disabled'] = true;
    return drupal_render($form['javascript']['aurora_libraries_head']);
  }
  return '';
}

function aurora_ajax_settings_save($form, $form_state) {
  $theme = $form_state['build_info']['args'][0];
  $theme_settings = variable_get('theme_' . $theme . '_settings', array());
  $trigger = $form_state['triggering_element'] ['#name'];

  $theme_settings[$trigger] = $form_state['input'][$trigger];

  if (empty($theme_settings[$trigger])) {
    $theme_settings[$trigger] = 0;
  }
  variable_set('theme_' . $theme . '_settings', $theme_settings);
}
