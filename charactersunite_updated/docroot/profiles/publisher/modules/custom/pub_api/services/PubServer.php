<?php

/**
 * @file
 * Pub specific server class.
 */

class PubServerException extends Exception {}

class PubServer extends RESTServer {

  private static $currentVersion = '';

  private static $versions = array();

  protected static $version;

  /**
   * Overrides RESTServer::__construct().
   */
  function __construct(ServicesContextInterface $context, ServicesContentTypeNegotiatorInterface $negotiator, $resources, $parsers, $formatters) {
    parent::__construct($context, $negotiator, $resources, $parsers, $formatters);

    static::$currentVersion = variable_get('pub_api_version');
    static::$versions = explode(',', variable_get('pub_api_versions'));
  }

  /**
   * Overrides RESTServer::parseJSON().
   */
  public static function parseJSON($handle) {
    static::$version = static::getVersion();

    return parent::parseJSON($handle);
  }

  /**
   * Helper function to parse out the API version from the request accept
   * header. If no accept header is sent the current API version will be used.
   *
   * @return string
   *   The API version the request intends to use or the current API version if
   *   the requesting version could not be determined.
   */
  public static function getVersion() {
    $version = static::$currentVersion;

    // There is only one valid type of return that can specify api version
    if (isset($_SERVER['HTTP_ACCEPT'])) {
      $accept_string = variable_get('pub_api_accept_header', 'application/json');
      foreach (static::$versions as $t_version) {
        if ($_SERVER['HTTP_ACCEPT'] == sprintf($accept_string, $t_version)) {
          $version = $t_version;
          break;
        }
      }
    }

    return $version;
  }

  /**
   * Overrides RESTServer::getControllerArguments().
   */
  protected function getControllerArguments($controller) {
    $args = array();

    foreach ($controller['args'] as $argument_number => $argument_info) {
      if ($argument_info['source'] == 'const') {
        $controller['args'][$argument_number]['optional'] = TRUE;
        $args[$argument_number] = $argument_info['value'];
      }
    }

    $args += parent::getControllerArguments($controller);

    return $args;
  }

}

