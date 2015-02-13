<?php

/**
 * Page callback for admin/workbench/scheduled.
 *
 * This contains some teaser views.
 *
 * @return array
 *   A Render API array of content creation options.
 */
function pub_workbench_content() {
  $output = array();

  // Allow other modules to add content here.
  $output['pub_workbench_scheduled_content'] = array(
    '#view' => 'pub_workbench_scheduled_content',
    '#view_display' => 'block',
    '#theme' => 'workbench_element',
  );

  $output['pub_workbench_scheduled_videos'] = array(
    '#view' => 'pub_workbench_scheduled_videos',
    '#view_display' => 'block',
    '#theme' => 'workbench_element',
  );

  // Allow other modules to alter the default page.
  drupal_alter('pub_workbench_content', $output);

  // Transform the Views into markup.
  // @see views_embed_view()
  foreach (element_children($output) as $key) {
    if (isset($output[$key]['#view']) && $view = views_get_view($output[$key]['#view'])) {
      $output[$key] += array('#markup' => '', '#view_display' => 'default');
      $display_id = $output[$key]['#view_display'];

      // Build contextual links.
      if (module_exists('contextual')) {
        $output[$key] += contextual_element_info();
        views_add_contextual_links($output[$key]['#contextual_links'], 'block', $view, $display_id);
      }

      if ($view->access($display_id)) {
        $output[$key]['#markup'] .= $view->preview($display_id, array());
        if ($title = $view->get_title()) {
          $output[$key]['#title'] = $title;
        }
      }
      $view->destroy();
    }
  }

  return $output;
}

/**
 * Add any CSS necessary.
 */
function pub_workbench_css() {
  // Include the Ctools Dropbutton CSS from Views.
  drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.css');
  drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.ctools.css');
  drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.seven.css');
  drupal_add_css(drupal_get_path('module', 'pub_workbench') . '/css/pub_workbench.css', array('weight' => 100));
}
