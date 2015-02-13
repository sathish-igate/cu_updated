<?php

/**
 * @file
 * Definition of pub_editorial_views_handler_field_operations.
 */

/**
 * A handler to provide proper displays for the representative image.
 *
 * @ingroup views_field_handlers
 */
class pub_editorial_views_handler_field_operations extends views_handler_field {

  function query() {
    // Do nothing -- to override the parent query.
  }

  function get_value($values, $field = NULL) {
    if (isset($values->{$field})) {
      return $values->{$field};
    }
  }

  function render($values) {
    $output = '';

    if (empty($this->relationship)) {
      // Get the entity type from the views data.
      $data = views_fetch_data($this->table);
      $type = $data['pub_editorial']['entity_type'];
      $key = $data['pub_editorial']['entity_key'];

      // Load the entity and render the field.
      $entities = entity_load($type, array($this->get_value($values, $key)));
      $entity = array_pop($entities);

      // Build the links array.
      $value = $this->get_value($values, $key);
      if (entity_access('update', $type, $entity)) {
        $links[] = array(
          'title' => t('Edit'),
          'href' => $type . '/' . $value . '/edit',
          'query' => drupal_get_destination(),
        );
      }
      if ($type != 'user' && entity_access('delete', $type, $entity)) {
        $links[] = array(
          'title' => t('Delete'),
          'href' => $type . '/' . $value . '/delete',
        );
      }
      switch ($type) {
        case 'node':
          if (module_exists('clone') && clone_access_cloning($entity)) {
            $links[] = array(
              'title' => t('Clone'),
              'href' => $type . '/' . $value . '/clone/' . clone_token_to_arg(),
              'query' => drupal_get_destination(),
            );
          }
          break;

        case 'file':
          if ($entity->type == 'image' && entity_access('update', $type, $entity)) {
            $links[] = array(
              'title' => t('Edit Image Focus'),
              'href' => $type . '/' . $value . '/edit',
              'query' => array_merge(drupal_get_destination(), array('image-focus' => 1)),
            );
          }
          break;

        case 'comment':
          if (user_access('administer comments')) {
            $links[] = array(
              'title' => t('Approve'),
              'href' => $type . '/' . $value . '/approve',
            );
          }
          break;

        case 'user':
          if (user_access('administer users')) {
            $links[] = array(
              'title' => t('Cancel'),
              'href' => $type . '/' . $value . '/cancel',
            );
          }
          break;

        default:
          // In case we are dealing with a non-supported entity, we empty the
          // links array.
          $links = array();
      }

      // Allow other modules to add links to the dropdown.
      drupal_alter('pub_editorial_operations_links', $links);
      if (!empty($links)) {
        $output = theme('links__ctools_dropbutton', array('title' => t('operations'), 'links' => $links));
      }

      $this->pub_editorial_css();
    }
    else {
      drupal_set_message(t('The "Operations" field does not work when using a relationship. You should remove the %field field from your view.', array('%field' => $this->definition['group'] . ': ' . $this->definition['title'])), 'warning', FALSE);
    }

    return $output;
  }

  /**
   * Add any CSS necessary.
   */
  function pub_editorial_css() {
    // Include the Ctools Dropbutton CSS from Views.
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.css');
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.ctools.css');
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.seven.css');
    drupal_add_css(drupal_get_path('module', 'pub_editorial') . '/css/pub_editorial.css', array('weight' => 100));
  }
}
