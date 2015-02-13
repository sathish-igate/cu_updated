<?php

/**
 * @file
 * Defines a custom views query.
 */

/**
 * Class for implementing a Views query backend plugin for thePlatform.
 */
class pub_theplatform_views_plugin_query extends views_plugin_query {

  // The thePlatformAPIRequest object.
  public $thePlatform;

  /**
   * {@inheritdoc}
   */
  public function init($base_table, $base_field, $options) {
    parent::init($base_table, $base_field, $options);
    $this->thePlatform = new pubThePlatformAPIRequest(variable_get('theplatform_feed_url', ''));
  }

  /**
   * {@inheritdoc}
   */
  public function build(&$view) {
    $view->build_info['theplatform_request'] = $this->thePlatform;

    // Grab the pager / items per page / offset settings, and use them to
    // control the number of results that are returned.
    if (isset($view->display[$view->current_display]->display_options['pager']['options']['items_per_page'])) {
      $upper_limit = $view->display[$view->current_display]->display_options['pager']['options']['items_per_page'];
      $lower_limit = isset($view->display[$view->current_display]->display_options['pager']['options']['offset']) ? $view->display[$view->current_display]->display_options['pager']['options']['offset'] : 0;
    }
    else {
      // If there is no limit set in this way, then we go for 50.
      if (isset($view->display['default']->display_options['pager']['options']['items_per_page'])) {
        $upper_limit = $view->display['default']->display_options['pager']['options']['items_per_page'];
      }
      else {
        $upper_limit = 50;
      }
      $lower_limit = isset($view->display['default']->display_options['pager']['options']['offset']) ? $view->display['default']->display_options['pager']['options']['offset'] : 0;
    }

    $view->build_info['theplatform_request']->setRange($lower_limit, $upper_limit);

    // Adding arguments to the request.
    if (isset($view->query->request_arguments)) {
      foreach ($view->query->request_arguments as $arg_key => $arg_value) {
        $view->build_info['theplatform_request']->addArg($arg_key, $arg_value);
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function add_field($table, $field, $alias = '', $params = array()) {
    // Test if there is a parent version of this function.
    if (get_parent_class($this) && in_array('add_field', get_class_methods(get_parent_class($this)))) {
      parent::add_field($table, $field, $alias, $params);
    }

    if (substr($field, 0, 6) === 'media_') {
      $this->thePlatform->addField('media$' . substr($field, 6));
    }
    elseif (substr($field, 0, 8) === 'plmedia_') {
      $this->thePlatform->addField('plmedia$' . substr($field, 8));
    }
    // Turns out that thePlatform wants these with a : instead of pl1$ like
    // everything else.  Yay special cases!
    elseif (substr($field, 0, 4) === 'pl1_') {
      $this->thePlatform->addField(':' . substr($field, 4));
    }
    elseif ($field === 'custom_runtime') {
      $this->thePlatform->addField('media$content');
    }
    else {
      $this->thePlatform->addField($field);
    }

    // They can access by the full name, we don't have the postgres issue where
    // it gets truncated.
    return $field;
  }

  /**
   * {@inheritdoc}
   */
  public function add_orderby($table, $field, $order = 'ASC', $alias = '', $params = array()) {
    if (get_parent_class($this) && in_array('add_orderby', get_class_methods(get_parent_class($this)))) {
      parent::add_orderby($table, $field, $alias, $params);
    }

    if (substr($alias, 0, 6) === 'media_') {
      $the_platform_name = 'media$' . substr($alias, 6);
    }
    elseif (substr($alias, 0, 8) === 'plmedia_') {
      $the_platform_name = 'plmedia$' . substr($alias, 8);
    }
    // Turns out that thePlatform wants these with a : instead of pl1$ like
    // everything else.  Yay special cases!
    elseif (substr($alias, 0, 4) === 'pl1_') {
      $the_platform_name = ':' . substr($alias, 4);
    }
    else {
      $the_platform_name = $alias;
    }

    $this->thePlatform->sort($the_platform_name, strtolower($order) === 'desc');
  }

  /**
   * {@inheritdoc}
   */
  public function execute(&$view) {
    $request = $view->build_info['theplatform_request'];

    $start = microtime(TRUE);
    $view->result = array();
    $resp = $request->execute();

    foreach ($resp as $item) {
      foreach ($item as $name => $value) {
        // Runtime is special.  We have to do some magic for this one.
        if ($name === 'media$content') {
          foreach ($value as $file) {
            if (isset($file->{'plfile$duration'})) {
              $item->{'custom_runtime'} = $file->{'plfile$duration'};
              break;
            }
          }
        }
        elseif (substr($name, 0, 6) === 'media$') {
          $item->{'media_' . substr($name, 6)} = $value;
        }
        elseif (substr($name, 0, 8) === 'plmedia$') {
          $item->{'plmedia_' . substr($name, 8)} = $value;
        }
        elseif (substr($name, 0, 4) === 'pl1$') {
          $item->{'pl1_' . substr($name, 4)} = $value;
        }
      }
      $view->result[] = $item;
    }

    $view->execute_time = microtime(TRUE) - $start;
  }
}
