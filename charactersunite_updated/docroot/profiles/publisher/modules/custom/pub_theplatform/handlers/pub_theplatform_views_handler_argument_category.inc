<?php

/**
 * @file
 * Definition of pub_theplatform_views_handler_argument_category.
 */

/**
 * Basic argument handler to implement category handling for thePlatform
 *
 * @ingroup views_argument_handlers
 */
class pub_theplatform_views_handler_argument_category extends views_handler_argument_numeric {

  /**
   * Supply information about the argument option.
   *
   * @return array
   *   An associative array of information about the option.
   */
  public function option_definition() {
    $options = parent::option_definition();

    $options['argument_style'] = array(
      'node' => t('Drupal nodes (with proper thePlatform field)'),
      'guid' => t('MPX GUID'),
    );

    return $options;
  }

  /**
   * Add form option to allow for different methods of category input.
   *
   * Build a form so that we can switch between the different ways we
   * might have the category come in.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['argument_style'] = array(
      '#title' => t('What type of source will provide this argument?'),
      '#options' => array(
        'node' => t('Drupal nodes (with proper thePlatform field)'),
        'guid' => t('MPX GUID'),
      ),
      '#type' => 'radios',
      '#weight' => -100,
      '#required' => TRUE,
    );
  }

  /**
   * Build the query for thePlatform category on the viewed node.
   *
   * Build the query based upon thePlatform category present on the node we're
   * viewing.
   */
  public function query($group_by = FALSE) {
    // Loop over each argument nid these and add their categories (if present).
    $type = $this->options['argument_style'];

    if (!empty($this->value)) {
      foreach ($this->value as $i => $nid) {
        // This refactor is untested.  When we re-enable the select we should
        // do that.
        if ($type == 'node') {
          $category = $this->getCategoryFromNode();
        }
        elseif ($type == 'guid') {
          $category = $this->getCategoryFromMPXGUID();
        }
        else {
          $category = NULL;
        }

        $this->query->thePlatform->addArg('byCategories', $category);
        // Only honor one - it already only did that.
        break;
      }
    }
  }

  /**
   * Helper function to get thePlatform category from a node.
   *
   * Helper function to get the category from a node with a thePlatform category field.
   */
  private function getCategoryFromNode() {
    // Get the category for this node id.
    $nid = $this->value[0];
    $node = node_load($nid);
    $fields = field_info_fields();
    foreach ($fields as $field_name => $field_info) {
      // Figure out which field on the node is thePlatform category, and make sure this node type has that field.
      if ($field_info['type'] == 'theplatform_category' && isset($field_info['bundles']['node']) && in_array($node->type, $field_info['bundles']['node'])) {
        // If this node has a thePlatform category field, we'll add it to the query request to thePlatform to filter the videos.
        $category_field = field_get_items('node', $node, $field_info['field_name'], NULL);
        if (is_array($category_field)) {
          $category = array_pop(array_pop($category_field));
        }
        else {
          $category = NULL;
        }
      }
    }
    return $category;
  }

  /**
   * Helper function to get the category from a MPX guid.
   */
  private function getCategoryFromMPXGUID() {
    $guid = $this->value[0];
    $theP = new pubThePlatformAPIRequest(variable_get('theplatform_feed_url', ''));
    $theP->addField('media$categories')->setID($guid);
    $resp = $theP->execute();

    // If there is nothing, then well.  Give none.
    if (count($resp) == 0 && !is_array($resp)) {
      return '';
    }

    $categories = $resp[0]->{'media$categories'};
    $longestDir = array('name' => '', 'size' => 0);

    foreach ($categories as $c) {
      $len = count(explode('/', $c->{'media$name'}));
      if ($len >= $longestDir['size']) {
        $longestDir['size'] = $len;
        $longestDir['name'] = $c->{'media$name'};
      }
    }
    return $longestDir['name'];
  }
}
