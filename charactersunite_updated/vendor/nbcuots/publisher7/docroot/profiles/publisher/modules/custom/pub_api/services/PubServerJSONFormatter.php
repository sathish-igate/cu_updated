<?php

/**
 * @file
 * Formatter for Pub API results.
 */

class PubServerJSONFormatter implements ServicesFormatterInterface {
  protected $version;

  /**
   * Implements ServicesFormatterInterface::render().
   */
  public function render($data) {
    $this->version = PubServer::getVersion();

    drupal_add_http_header(
      'Content-Type',
      sprintf(
        variable_get('pub_api_accept_header', 'application/json'),
        $this->version
      )
    );

    $json = str_replace('\\/', '/', json_encode($data));
    return $json;
  }

}

