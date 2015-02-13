<?php

/**
 * @file
 * Characterunite's theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template normally located in the
 * modules/system directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/Characterunite.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 * - $hide_site_name: TRUE if the site name has been toggled off on the theme
 *   settings page. If hidden, the "element-invisible" class is added to make
 *   the site name visually hidden, but still accessible.
 * - $hide_site_slogan: TRUE if the site slogan has been toggled off on the
 *   theme settings page. If hidden, the "element-invisible" class is added to
 *   make the site slogan visually hidden, but still accessible.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['header']: Items for the header region.
 * - $page['featured']: Items for the featured region.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['triptych_first']: Items for the first triptych.
 * - $page['triptych_middle']: Items for the middle triptych.
 * - $page['triptych_last']: Items for the last triptych.
 * - $page['footer_firstcolumn']: Items for the first footer column.
 * - $page['footer_secondcolumn']: Items for the second footer column.
 * - $page['footer_thirdcolumn']: Items for the third footer column.
 * - $page['footer_fourthcolumn']: Items for the fourth footer column.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see characterunite_process_page()
 * @see html.tpl.php
 */
?>
<div id="page-wrapper">
  <div id="page">
    <?php print render($page['header']); ?>
    <div id="main-container" class="clearfix">
      <div id="nav-container" class="wrapper clearfix">
        <?php if ($main_menu): ?>
          <div id="main-menu" class="navigation">
          <?php 
            if (module_exists('i18n_menu')) {
            $main_menu_tree = i18n_menu_translated_tree(variable_get('menu_main_links_source', 'main-menu'));
            } else {
            $main_menu_tree = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
            }
            print drupal_render($main_menu_tree);
          ?>
          </div> <!-- /#main-menu -->
        <?php endif; ?>
        <?php if ($page['social']): ?>
          <div class="social">
            <?php print render($page['social']); ?>
          </div>
        <?php endif; ?>
      </div>
      <div id="main" class="wrapper clearfix">
        <div class="initiatives">
          <div class="initiativesHeader">
            <?php  if ($breadcrumb): ?>
              <div id="breadcrumbs"><?php print $breadcrumb; ?></div>
            <?php endif;  ?>
            <?php if ($tabs): ?>
              <?php print render($tabs); ?>
            <?php endif; ?>
            <?php  if (!$is_front): ?>
              <?php if (isset($node->field_override_title[LANGUAGE_NONE]) && $node->field_override_title[LANGUAGE_NONE][0]['value'] == 1 && $node->field_display_title[LANGUAGE_NONE][0]['value'] != ''): ?>
                <div class="initTitle"><?php print $node->field_display_title[LANGUAGE_NONE][0]['value']; ?></div>
              <?php else: ?>
                <div class="initTitle"><?php print drupal_get_title(); ?></div>
              <?php endif; ?>
              <div class="wrapper clearfix" id="subnav-container">
                <div class="subnav">
                <?php if ($page['featured']): ?>
                  <div class="subnav-tabs">
                    <?php print render($page['featured']); ?>
                  </div>
                <?php endif; ?>
                </div>
              </div>
            <?php endif; ?>
          </div>
          <?php print render($page['content']); ?>
        </div>
      </div>  <!-- /#main -->
    </div> <!-- /#main-container -->
    <div id="footer-container">
      <footer class="wrapper">
        <div class="totals">
          <!-- AddThis Button BEGIN -->
          <div class="addthis_toolbox addthis_default_style ">
          <a class="addthis_button_tweet"  addthis:title="USA Network's Characters Unite is dedicated to combating hate, prejudice and discrimination."></a>
          <a class="addthis_button_facebook_like" fb:like:layout="button_count"></a>
          </div>
          <script type="text/javascript" src="http://s7.addthis.com/js/250/addthis_widget.js#pubid=xa-4f08e1e35b6b8f8a"></script>
          <!-- AddThis Button END -->
        </div>
        <?php print render($page['footer']); ?>
      </footer>
    </div>  <!-- /#footer-container -->
  </div> <!-- /#page -->
</div> <!-- /#page-wrapper -->
