<?php
/**
 * Sorts CSS and JavaScript resources.
 *
 * Callback for uasort() within:
 * - drupal_get_css()
 * - aurora_get_js()
 *
 * This sort order helps optimize front-end performance while providing modules
 * and themes with the necessary control for ordering the CSS and JavaScript
 * appearing on a page.
 *
 * @param $a
 *   First item for comparison. The compared items should be associative arrays
 *   of member items from drupal_add_css() or aurora_add_js().
 * @param $b
 *   Second item for comparison.
 *
 * @see drupal_add_css()
 * @see aurora_add_js()
 */
function aurora_sort_css_js($a, $b) {
  // First order by group, so that, for example, all items in the CSS_SYSTEM
  // group appear before items in the CSS_DEFAULT group, which appear before
  // all items in the CSS_THEME group. Modules may create additional groups by
  // defining their own constants.
  if (!empty($a['group']) && !empty($b['group'])) {
    if ($a['group'] < $b['group']) {
      return -1;
    }
    elseif ($a['group'] > $b['group']) {
      return 1;
    }
  }

  // Within a group, order all infrequently needed, page-specific files after
  // common files needed throughout the website. Separating this way allows for
  // the aggregate file generated for all of the common files to be reused
  // across a site visit without being cut by a page using a less common file.
  elseif (!empty($a['every_page']) && !empty($b['every_page'])) {
    if ($a['every_page'] && !$b['every_page']) {
      return -1;
    }
    elseif (!$a['every_page'] && $b['every_page']) {
      return 1;
    }
  }

  // Finally, order by weight.
  elseif (!empty($a['weight']) && !empty($b['weight'])) {
    if ($a['weight'] < $b['weight']) {
      return -1;
    }
    elseif ($a['weight'] > $b['weight']) {
      return 1;
    }
  }

  else {
    return 0;
  }
}
