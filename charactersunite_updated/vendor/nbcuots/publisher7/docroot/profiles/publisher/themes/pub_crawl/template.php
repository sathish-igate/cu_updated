<?php
/**
  * Implements hook_preprocess_html()
  */
function pub_crawl_preprocess_html(&$vars) {
  // Be sure replace this with a custom Modernizr build!
  drupal_add_js(drupal_get_path('theme', 'pub_crawl') . '/javascripts/modernizr-2.5.3.js', array('force header' => true));
  
  // yep/nope for conditional JS loading!
  drupal_add_js(drupal_get_path('theme', 'pub_crawl') . '/javascripts/loader.js');

  // logo Fallback to PNG if SVG not supported by browser like IE8
  drupal_add_js(drupal_get_path('theme', 'pub_crawl') . '/javascripts/logo.js');
}
