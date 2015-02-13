<?php
/**
 * @file context_condition_resolution.inc
 * Provides the context CTools plugin base class.
 */

class ContextConditionBreakpoint extends context_condition {

  protected $cookieName = 'context_breakpoint';

  protected function parseBreakpoint($query) {
    $query = str_replace(' ', '', $query);

    preg_match_all('/\(([a-z\-]+)\:(.+?)\)/', $query, $matches);

    $point = array();
    for ($i = 0; $i < count($matches[0]); $i++) {
      $cmd = $matches[1][$i];
      $value = $matches[2][$i];

      switch ($cmd) {
        case 'width':
        case 'min-width':
        case 'max-width':
        case 'height':
        case 'min-height':
        case 'max-height':
        case 'device-width':
        case 'min-device-width':
        case 'max-device-width':
        case 'device-height':
        case 'min-device-height':
        case 'max-device-height':
          // Only px values are supported.
          if (strpos($value, 'px') !== false) {
            $point[$cmd] = (int) str_replace('px', '', $value);
          }
          break;

        case 'aspect-ratio':
        case 'min-aspect-ratio':
        case 'max-aspect-ratio':
        case 'device-aspect-ratio':
        case 'min-device-aspect-ratio':
        case 'max-device-aspect-ratio':
          $parts = explode('/', $value);

          if (count($parts) === 2 && is_numeric($parts[0]) && is_numeric($parts[1])) {
            $point[$cmd] = (float) $parts[0] / (float) $parts[1];
          }

          break;

        default:
          // Unsupported.
          break;
      }
    }
    return count($point) ? $point : FALSE;
  }

  protected function parseCookie($cookie) {
    $data = drupal_json_decode($cookie);
    return $data;
  }

  public function getJSConfig() {
    $conf = array();

    $valid = array(
      'width',
      'min-width',
      'max-width',
      'height',
      'min-height',
      'max-height',
      'aspect-ratio',
      'min-aspect-ratio',
      'max-aspect-ratio',
    );

   foreach ($this->get_contexts() as $context) {
      $values = $this->fetch_from_context($context, 'values');
      $options = $this->fetch_from_context($context, 'options');

      if (isset($options['autoreload']) && $options['autoreload']) {
        $breakpoint = breakpoints_breakpoint_load_by_fullkey($values[0]);
        if (!$breakpoint) continue;

        $conditions = $this->parseBreakpoint($breakpoint->breakpoint);

        $point = array();

        foreach ($conditions as $cmd => $value) {
          if (in_array($cmd, $valid)) {
            $point[$cmd] = $value;
          }
        }

        if (count($point)) {
          $conf[$breakpoint->machine_name] = $point;
        }
      }
    }

    return $conf;
  }

  /**
   * Condition values.
   */
  function condition_values() {
    $breakpoints = array();

    foreach (breakpoints_breakpoint_load_all() as $point) {
      if ($this->parseBreakpoint($point->breakpoint)) {
        $breakpoints[$point->machine_name] = $point->name . ' | ' . $point->breakpoint;
      }
    }

    return $breakpoints;
  }

  /**
   * Condition form.
   */
  function condition_form($context) {
    $supported = implode(', ', array(
      '(min/max-)width',
      '(min/max-)height',
      '(min/max-)device-width',
      '(min/max-)device-height',
      '(min/max-)aspect-ratio',
      '(min/max-)device-aspect-ratio',
    ));

    $values = $this->fetch_from_context($context, 'values');
    $bp = ($values && count($values)) ? $values[0] : '';

    return array(
      '#title' => $this->title,
      '#description' => t('Choose the breakpoint you want to react to. Only compatible breakpoints are displayed. <br />Supported: ' . $supported . '. "and" queries are supported. <br />' . l('Configure breakpoints', 'admin/config/media/breakpoints')),
      '#options' => $this->condition_values(),
      '#type' => 'select',
      '#default_value' => $bp,
    );
  }

  /**
   * Condition form submit handler.
   */
  function condition_form_submit($values) {
    return array($values);
  }

  function options_form($context = NULL) {
    $defaults = $this->fetch_from_context($context, 'options');
    $form = array(
      'autoreload' => array(
        '#type' => 'checkbox',
        '#title' => t('Auto-reload'),
        '#description' => t('When enabled, the page will automatically reload when when this breakpoint becomes active or unactive(due to resizing the browser).<br /> Only works for width, height and aspect-ratio.'),
        '#default_value' => isset($defaults['autoreload']) ? $defaults['autoreload'] : 0,
      )
    );

    return $form;
  }

  function execute() {
     // Check if there is a valid resolution stored in the cookie.
    if (isset($_COOKIE[$this->cookieName])) {
      $data = $this->parseCookie($_COOKIE[$this->cookieName]);
      if ($data) {
        foreach ($this->get_contexts() as $context) {
          $values = $this->fetch_from_context($context, 'values');
          if ($data[$values[0]]) {
            $this->condition_met($context);
          }
        }
      }
    }
  }
}
