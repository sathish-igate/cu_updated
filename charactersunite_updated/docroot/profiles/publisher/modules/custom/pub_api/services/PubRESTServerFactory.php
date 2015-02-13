<?php

/**
 * @file
 * Custom server factory.
 */

class PubRESTServerFactory extends ServicesRESTServerFactory {

  static $class_name = 'PubServer';

  public function getRESTServer() {
    // The purpose of this class is to override the content type negotiator to
    // use a custom negotiation logic.
    $content_type_negotiator = static::getContentTypeNegotiator();
    $context = $this->getContext();
    $resources = $this->getResources();
    $parsers = $this->getParsers();
    $formatters = $this->getFormatters();

    $class_name = static::$class_name;
    return new $class_name($context, $content_type_negotiator, $resources, $parsers, $formatters);
  }

  protected function getContentTypeNegotiator() {
    return new PubServicesContentTypeNegotiator();
  }

}

