<?php
/**
 * @file
 * Contains functions to alter Drupal's markup for the Aurora theme.
 *
 *        _d^^^^^^^^^b_
 *     .d''           ``b.
 *   .p'  @          @   `q.       NOTHING TO DO HERE
 *  .d'    ----------     `b.
 * .d'                     `b.
 * ::                       ::
 * ::                       ::
 * ::                       ::
 * `p.                     .q'
 *  `p.                   .q'
 *    `b.               .d'\
 *     / ^q...........p^    \
 *    /       ''''bbbbbbb    \
 *   /  __    __ \bbbbbbbb   /
 *    \_bbbbbbbb__\________/
 *       bb   bbbbbbbbbbbbbbb
 *                bb|bbbbbbb  ***
 *                 b|bbbbb   ******
 *       _______    |        **000***
 *     /         \  |         **00000**
 *   __|__________\/            ***   **
 *  /  |                         *      *
 * |    \
 * |      \__
 *  \
 *   \__
 *
 * The Aurora theme is a base theme designed to be easily extended by sub
 * themes. You should not modify this or any other file in the Aurora theme
 * folder. Instead, you should create a sub-theme and make your changes there.
 * In fact, if you're reading this, you may already off on the wrong foot.
 *
 * See the project page for more information:
 *   http://drupal.org/project/aurora
 */

// We set a specific group for jquery, so our CDN work actually works.
define('JS_JQUERY', -10000);
define('JS_DRUPAL', -9000);

require_once dirname(__FILE__) . '/includes/common.inc';
require_once dirname(__FILE__) . '/includes/scripts.inc';


// Auto-rebuild the theme registry during theme development.
if (theme_get_setting('aurora_rebuild_registry') && !defined('MAINTENANCE_MODE')) {
  // Rebuild .info data.
  system_rebuild_theme_data();
  // Rebuild theme registry.
  drupal_theme_rebuild();
}

//////////////////////////////
// Absolutely Amazing Omega Sideport
//////////////////////////////

/**
  * Implements hook_theme_registry_alter
  */
function aurora_theme_registry_alter(&$registry) {
  // Override template_process_html() in order to add support for all of the Awesome.
  // Again, huge, amazing ups to the wizard Sebastian Siemssen (fubhy) for showing me how to do this.
  if (($index = array_search('template_process_html', $registry['html']['process functions'], TRUE)) !== FALSE) {
    array_splice($registry['html']['process functions'], $index, 1, 'aurora_template_process_html_override');
  }
  // Commented out Maintance page registry handlers until further testing.
//  if (($index = array_search('template_process_maintenance_page', $registry['maintenance_page']['process functions'], TRUE)) !== FALSE) {
//    array_splice($registry['maintenance_page']['process functions'], $index, 1, 'aurora_template_process_maintenance_page_override');
//  }
}

function aurora_preprocess_maintenance_page(&$vars, $hook) {
  // When a variable is manipulated or added in preprocess_html or
  // preprocess_page, that same work is probably needed for the maintenance page
  // as well, so we can just re-use those functions to do that work here.
  aurora_preprocess_html($vars);
}

function aurora_process_maintenance_page(&$vars, $hook) {
  // When a variable is manipulated or added in preprocess_html or
  // preprocess_page, that same work is probably needed for the maintenance page
  // as well, so we can just re-use those functions to do that work here.
  aurora_process_html($vars);
}

/**
  * Overrides template_process_html() in order to provide support for awesome new stuffzors!
  *
  * Huge, amazing ups to the wizard Sebastian Siemssen (fubhy) for showing me how to do this.
  */
function aurora_template_process_html_override(&$variables) {
  // Render page_top and page_bottom into top level variables.
  $variables['page_top'] = drupal_render($variables['page']['page_top']);
  $variables['page_bottom'] = drupal_render($variables['page']['page_bottom']);
  // Place the rendered HTML for the page body into a top level variable.
  $variables['page'] = $variables['page']['#children'];


  $variables['head'] = drupal_get_html_head();
  $variables['css'] = drupal_add_css();
  $variables['styles']  = drupal_get_css();

  if (theme_get_setting('aurora_custom_js_handling')) {
    $variables['page_bottom'] .= aurora_get_js('footer');
    $variables['scripts'] = aurora_get_js('header');
  }
  elseif (theme_get_setting('aurora_footer_js')) {
    $variables['page_bottom'] .= aurora_get_js_old('footer');
    $variables['scripts'] = aurora_get_js_old('header');
  }
  else {
    $variables['scripts'] = drupal_get_js();
    $variables['page_bottom'] .= drupal_get_js('footer');
  }
}

function aurora_template_process_maintenance_page_override(&$vars) {
  $vars['scripts'] = aurora_get_js();
  $vars['page_bottom'] = aurora_get_js('footer');
  $vars['css'] = drupal_add_css();
  $vars['styles'] = drupal_get_css();
  $vars['head'] = drupal_get_html_head();
}

/**
 * Implements hook_element_info_alter().
 */
function aurora_element_info_alter(&$elements) {
  // if (theme_get_setting('aurora_toggle_extension_css') && theme_get_setting('aurora_media_queries_inline') && variable_get('preprocess_css', FALSE) && (!defined('MAINTENANCE_MODE') || MAINTENANCE_MODE != 'update')) {
  //   array_unshift($elements['styles']['#pre_render'], 'aurora_css_preprocessor');
  // }

  $elements['scripts'] = array(
    '#items' => array(),
    '#pre_render' => array('aurora_pre_render_scripts'),
    '#group_callback' => 'aurora_group_js',
    '#aggregate_callback' => 'aurora_aggregate_js',
    '#type' => 'scripts'
  );
}

//////////////////////////////
// HTML5 Project Sideport
//////////////////////////////

/**
 * Implements hook_preprocess_html()
 */
function aurora_preprocess_html(&$vars) {
  // Viewport!
  $viewport = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width, initial-scale=1',
    ),
  );
  drupal_add_html_head($viewport, 'viewport');

  if (theme_get_setting('aurora_enable_chrome_frame')) {
    // Force IE to use most up-to-date render engine.
    $xua = array(
      '#tag' => 'meta',
      '#attributes' => array(
        'http-equiv' => 'X-UA-Compatible',
        'content' => 'IE=edge,chrome=1',
      ),
    );
    drupal_add_html_head($xua, 'x-ua-compatible');

    // Chrome Frome
    $chromeframe['wrapper'] = '<!--[if lt IE ' . theme_get_setting('aurora_min_ie_support') . ' ]>';

    // Chrome Frame
    $chromeframe['redirect'] = 'http://browsehappy.com/';
    $chromeframe['url'] = 'http://www.google.com/chromeframe/?redirect=true';

    $chromeframe['include']['element'] = array(
      '#tag' => 'script',
      '#attributes' => array(
        'src' => '//ajax.googleapis.com/ajax/libs/chrome-frame/1.0.3/CFInstall.min.js',
      ),
    );
    $chromeframe['launch']['element'] = array(
      '#tag' => 'script',
      '#attributes' => array(),
      '#value' => 'window.attachEvent("onload",function(){CFInstall.check({mode:"overlay"});})',
    );

    $vars['chromeframe_array'] = $chromeframe;
  }

  //////////////////////////////
  // HTML5 Base Theme Forwardport
  //
  // Backports the following changes made to Drupal 8:
  // - #1077566: Convert html.tpl.php to HTML5.
  //////////////////////////////
  // Initializes attributes which are specific to the html and body elements.
  $vars['html_attributes_array'] = array();
  $vars['body_attributes_array'] = array();

  // HTML element attributes.
  $vars['html_attributes_array']['lang'] = $GLOBALS['language']->language;
  $vars['html_attributes_array']['dir'] = $GLOBALS['language']->direction ? 'rtl' : 'ltr';

  // Update RDF Namespacing
  if (module_exists('rdf')) {
    // Adds RDF namespace prefix bindings in the form of an RDFa 1.1 prefix
    // attribute inside the html element.
    $prefixes = array();
    foreach (rdf_get_namespaces() as $prefix => $uri) {
      $vars['html_attributes_array']['prefix'][] = $prefix . ': ' . $uri . "\n";
    }
  }

  //////////////////////////////
  // LiveReload Integration
  //////////////////////////////
  if (theme_get_setting('aurora_livereload')) {
    drupal_add_js("document.write('<script src=\"http://' + (location.host || 'localhost').split(':')[0] + ':35729/livereload.js?snipver=1\"></' + 'script>')", array('type' => 'inline', 'scope' => 'footer', 'weight' => 9999));
  }

  //////////////////////////////
  // RWD Debug Integration
  //////////////////////////////
  if (theme_get_setting('aurora_viewport_width') || theme_get_setting('aurora_modernizr_debug')) {
    drupal_add_css(drupal_get_path('theme', 'aurora') . '/css/debug.css');
    drupal_add_js(drupal_get_path('theme', 'aurora') . '/js/debug.js');
  }

  //////////////////////////////
  // Add in TypeKit Code.
  //////////////////////////////
  if (theme_get_setting('aurora_typekit_id')) {
    drupal_add_js('(function(){var e={kitId:"' . theme_get_setting('aurora_typekit_id') . '",scriptTimeout:3e3},t=document.getElementsByTagName("html")[0];t.className+=" wf-loading";var n=setTimeout(function(){t.className=t.className.replace(/(\s|^)wf-loading(\s|$)/g," "),t.className+=" wf-inactive"},e.scriptTimeout),r=document.createElement("script"),i=!1;r.src="//use.typekit.net/"+e.kitId+".js",r.type="text/javascript",r.async="true",r.onload=r.onreadystatechange=function(){var t=this.readyState;if(i||t&&t!="complete"&&t!="loaded")return;i=!0,clearTimeout(n);try{Typekit.load(e)}catch(r){}};var s=document.getElementsByTagName("script")[0];s.parentNode.insertBefore(r,s)})()', array('type' => 'inline', 'force header' => true));
  }

}

/**
 * Implements hook_process_html().
 */
function aurora_process_html(&$vars) {
  //////////////////////////////
  // Chrome Frame
  //////////////////////////////
  if (theme_get_setting('aurora_enable_chrome_frame')) {
    $cf_array = $vars['chromeframe_array'];
    $cf = $cf_array['wrapper'] . theme_html_tag($cf_array['include']) . theme_html_tag($cf_array['launch']) . '<![endif]-->';

    $cf_link = $cf_array['wrapper'] . '<p class="chromeframe">' . t('You are using an outdated browser! !upgrade or !install to better experience this site.', array('!upgrade' => l(t('Upgrade your browser today'), $cf_array['redirect']), '!install' => l(t('install Google Chrome Frame'), $cf_array['url']))) . '<![endif]-->';

    if (!empty($vars['page_top'])) {
      $vars['page_top'] .= $cf_link;
    }
    else {
      $vars['page_top'] = $cf_link;
    }
  }

  //////////////////////////////
  // RWD Debug Integration
  //////////////////////////////
  if (theme_get_setting('aurora_viewport_width') || theme_get_setting('aurora_modernizr_debug')) {

    $debug_output = '<div id="aurora-debug">';

    if (theme_get_setting('aurora_viewport_width')) {
      $debug_output .= '<div id="aurora-viewport-width"></div>';
    }
    if (theme_get_setting('aurora_modernizr_debug')) {
      $debug_output .= '<div id="aurora-modernizr-debug" class="open"></div>';
    }

    $debug_output .= '</div>';

    if (!empty($vars['page_bottom'])) {
      $vars['page_bottom'] .= $debug_output;
    }
    else {
      $vars['page_bottom'] = $debug_output;
    }
  }

  //////////////////////////////
  // HTML5 Base Theme Forwardport
  //
  // Backports the following changes made to Drupal 8:
  // - #1077566: Convert html.tpl.php to HTML5.
  //////////////////////////////
  // Flatten out html_attributes and body_attributes.
  $vars['html_attributes'] = drupal_attributes($vars['html_attributes_array']);
  $vars['body_attributes'] = drupal_attributes($vars['body_attributes_array']);
}
/**
 * Return a themed breadcrumb trail.
 *
 * @param $variables
 *   - title: An optional string to be used as a navigational heading to give
 *     context for breadcrumb links to screen-reader users.
 *   - title_attributes_array: Array of HTML attributes for the title. It is
 *     flattened into a string within the theme function.
 *   - breadcrumb: An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 *
 * Lifted from Zen, because John is the man.
 */
function aurora_breadcrumb(&$vars) {
  if (theme_get_setting('toggle_breadcrumbs')) {
    return theme_breadcrumb($vars);
  }
}

/**
  * Implements hook_process_html_tag
  *
  * - From http://sonspring.com/journal/html5-in-drupal-7#_pruning
  */
function aurora_process_html_tag(&$vars) {
  if (theme_get_setting('aurora_html_tags')) {
    $el = &$vars['element'];

    // Remove type="..." and CDATA prefix/suffix.
    unset($el['#attributes']['type'], $el['#value_prefix'], $el['#value_suffix']);

    // Remove media="all" but leave others unaffected.
    if (isset($el['#attributes']['media']) && $el['#attributes']['media'] === 'all') {
      unset($el['#attributes']['media']);
    }
  }
}

//////////////////////////////
// HTML5 Base Theme Forwardport
//////////////////////////////
/**
 * Implements the hook_preprocess_comment().
 *
 * Backports the following variable changes to Drupal 8:
 * - #1189816: Convert comment.tpl.php to HTML5.
 */
function aurora_preprocess_comment(&$variables) {
  $variables['user_picture'] = theme_get_setting('toggle_comment_user_picture') ? theme('user_picture', array('account' => $comment)) : '';
}

/**
 * Implements hook_preprocess_user_profile_category().
 *
 * Backports the following changes to made Drupal 8:
 * - #1190218: Convert user-profile-category.tpl.php to HTML5.
 */
function aurora_preprocess_user_profile_category(&$variables) {
  $variables['classes_array'][] = 'user-profile-category-' . drupal_html_class($variables['title']);
}

/**
 * Implements hook_css_alter().
 *
 * Backports the following CSS changes made to Drupal 8:
 * - #1216950: Clean up the CSS for Block module.
 * - #1216948: Clean up the CSS for Aggregator module.
 * - #1216972: Clean up the CSS for Color module.
 *
 */
function aurora_css_alter(&$css) {
  // Path to the theme's CSS directory.
  $dir = drupal_get_path('theme', 'aurora') . '/css';

  // Swap out aggregator.css with the aggregator.theme.css provided by this
  // theme.
  $aggregator = drupal_get_path('module', 'aggregator');
  if (isset($css[$aggregator . '/aggregator.css'])) {
    $css[$aggregator . '/aggregator.css']['data'] = $dir . '/aggregator/aggregator.theme.css';
  }
  if (isset($css[$aggregator . '/aggregator-rtl.css'])) {
    $css[$aggregator . '/aggregator-rtl.css']['data'] = $dir . '/aggregator/aggregator.theme-rtl.css';
  }

  // Swap out block.css with the block.admin.css provided by this theme.
  $block = drupal_get_path('module', 'block');
  if (isset($css[$block . '/block.css'])) {
    $css[$block . '/block.css']['data'] = $dir . '/block/block.admin.css';
  }

  // Swap out color.css with the color.admin.css provided by this theme.
  $color = drupal_get_path('module', 'color');
  if (isset($css[$color . '/color.css'])) {
    $css[$color . '/color.css']['data'] = $dir . '/color/color.admin.css';
  }
  if (isset($css[$color . '/color-rtl.css'])) {
    $css[$color . '/color-rtl.css']['data'] = $dir . '/color/color.admin-rtl.css';
  }

  if (theme_get_setting('aurora_remove_core_css')) {
    foreach ($css as $key => $value) {
      if (strpos($key, 'modules/') === 0) {
        unset($css[$key]);
      }
    }
  }
}

/**
 * Implements hook_preprocess_node().
 *
 * Backports the following changes made to Drupal 8:
 * - #1077602: Convert node.tpl.php to HTML5.
 */
function aurora_preprocess_node(&$variables) {
  // Add article ARIA role.
  $variables['attributes_array']['role'] = 'article';
}

/**
  * Implements hook_js_alter
  */
function aurora_js_alter(&$js) {
  global $base_url;
  // Forces Modernizr to header if the Modernizr module is enabled.
  if (module_exists('modernizr')) {
    $js[modernizr_get_path()]['force header'] = true;
  }
}

function aurora_preprocess_panels_pane(&$vars) {
  $subtype = $vars['pane']->subtype;
  $layout = $vars['display']->layout;
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . $layout;
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . $subtype;
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . $layout . '__' . $subtype;
}

function aurora_panels_default_style_render_region($vars) {
  $output = '';
  $output .= implode("\n", $vars['panes']);
  return $output;
}
