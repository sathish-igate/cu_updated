<?php

/**
 * Load the default views
 * 
 * @access public
 * @return void
 */
function wp_report_server_views_default_views() {
  $views = array();
  include(dirname(__FILE__) .'/views/view.sitereports_view.inc');
  $views[$view->name] = $view;
  include(dirname(__FILE__) .'/views/view.sitereport_view.inc');
  $views[$view->name] = $view;
  return $views;
}
