<?php
/**
 * @file
 * pub_commerce_example.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function pub_commerce_example_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: categories-menu.
  $menus['categories-menu'] = array(
    'menu_name' => 'categories-menu',
    'title' => 'Categories menu',
    'description' => 'This menu breaks down the selection of items by the <em>Categories</em> taxonomy type.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Categories menu');
  t('This menu breaks down the selection of items by the <em>Categories</em> taxonomy type.');


  return $menus;
}
