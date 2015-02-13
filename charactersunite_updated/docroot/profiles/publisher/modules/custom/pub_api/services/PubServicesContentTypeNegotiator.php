<?php


/**
 * Class used to do Content Type negotiation.
 */

class PubServicesContentTypeNegotiator extends ServicesContentTypeNegotiator {

  /**
   * Determine response format and mime type using headers to negotiate content types.
   *
   * @param string $mime_type
   *   Mime type. This variable to be overriden.
   * @param string $canonical_path
   *   Canonical path of the request.
   * @param array $formats
   *   Enabled formats by endpoint.
   *
   * @return string
   *   Negotiated response format. For example 'json'.
   */
  public function getResponseFormatContentTypeNegotiations(&$mime_type, $canonical_path, $formats, $context) {
    drupal_add_http_header('Vary', 'Accept');

    // Note: This is a very blunt instrument - unfortunately, we need a hammer.
    // Services currently *forces* default formatters, formatters which
    // the default content type negotiator will likely match - usually resulting
    // in a formtter of XML being selected for web requests - but really
    // any best match for a non-specified accept header will win.
    // What we wanted was a default behavior of our custom formatter, what it
    // seems like we will have to settle for is  - only returning our
    // formatter.  As far as I understand it - this matches to the configuration
    // though. So - No harm no foul?  --theBruce.

    return pub_api_get_header();
  }

}
