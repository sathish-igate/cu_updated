<?php

/**
 * @file
 * pub_theplatform.api.inc
 */


/**
 * Class that describes a request to thePlatform's feeds.
 *
 * The methods are designed to be chained together until the ->execute() call.
 * That one returns the response data.
 */
class thePlatformAPIRequest {

  // Initialized when the class is instantiated.
  protected $base_url;

  // These are added by ->addArg calls (and can be chained).
  protected $args = array();

  // Reference ID for a particular video to load the extended metadata for.
  protected $refid = 0;

  // These are the fields that need to come back from the thePlatform servers.
  protected $fieldsToLoad = array();

  // Whether or not ot retrieve categories.
  protected $getCategories = FALSE;

  // The name of the field to sort on.
  protected $sortField = '';

  // Sort descending.
  protected $sortDesc = FALSE;

  // The query range.
  protected $range = NULL;

  /**
   * Construct the object.
   *
   * @param string $base_url
   *   (optional) Overwrite the base URL when constructing the class. Defaults
   *   to the Drupal set value.
   *
   * @throws Exception
   */
  public function __construct($base_url = '') {
    $this->base_url = $base_url;

    if (strlen($this->base_url) == 0) {
      throw new Exception("thePlatform module has not been configured");
    }
  }

  /**
   * Set the range for our query.
   *
   * @param int $lower_limit
   *   (optional) The lower limit for our desired range.
   *
   * @param int $upper_limit
   *   (optional) The upper limit for our desired range.
   *
   * @return obj
   *   Reference to $this for chainability.
   */
  public function setRange($lower_limit = 0, $upper_limit = 100) {
    $this->range = $lower_limit . '-' . $upper_limit;
    return $this;
  }

  /**
   * Set the video's ID that we want to query for.
   *
   * @param int $refid
   *   The reference ID that we're going to want to get back.
   *
   * @return obj
   *   Reference to $this for chainability.
   */
  public function setID($refid) {
    if (is_int($refid) || strlen($refid) > 0) {
      // If we have a ref id coming in, we need it to be a number or a string of
      // some length.
      $this->refid = $refid;
    }
    else {
      // If we fail these tests, then we assume the user is trying to reset it
      // to nothing. So we remove the filter.
      $this->refid = 0;
    }
    return $this;
  }

  /**
   * Set that we want to get categories instead.
   *
   * @param bool $get_categories
   *   (optional) Whether or not we should get the categories instead of videos
   *   (defaults to TRUE).
   *
   * @return obj
   *   Reference to $this for chainability.
   */
  public function getCategories($get_categories = TRUE) {
    $this->getCategories = $get_categories;
    return $this;
  }

  /**
   * Add an argument to the query we pass to thePlatform.
   *
   * @param string $name
   *   Name of the filter to apply.
   * @param mixed $value
   *   Value to filter for.
   *
   * @return obj
   *   Reference to $this for chainability.
   */
  public function addArg($name, $value) {
    // Remove the value if there is an empty string.
    if (strlen($value) == 0) {
      unset($this->args[$name]);
    }
    // Otherwise set it up.
    else {
      $this->args[$name] = $value;
    }
    return $this;
  }

  /**
   * Add a field that we want to return to the query we pass to thePlatform.
   *
   * @param string $field
   *   Name of the field to get.
   *
   * @return obj
   *   Reference to $this for chainability.
   */
  public function addField($field) {
    $this->fieldsToLoad[] = $field;
    return $this;
  }

  /**
   * Set the sort field for the query.
   *
   * @param string $field
   *   Name of the field to sort on.
   *
   * @param bool $desc
   *   Whether or not to sort descending.
   *
   * @return obj
   *   Reference to $this for chainability.
   */
  public function sort($field, $desc = TRUE) {
    $this->sortField = $field;
    $this->sortDesc = $desc;
    return $this;
  }

  /**
   * Helper that will generate the query args for this request.
   *
   * @return array
   *   query args.
   */
  protected function buildQueryArgs() {
    $query_args = array(
      'fields' => implode(',', $this->fieldsToLoad), 'form' => 'json',
      'pretty' => 'true',
    );
    // If we have a refid set, then we go for them as the values to use.
    if ($this->refid) {
      $query_args = array_merge($query_args, array('byGuid' => $this->refid));
    }
    else {
      $query_args = array_merge($query_args, $this->args);
    }

    if (strlen($this->sortField) > 0) {
      $query_args['sort'] = $this->sortField . ($this->sortDesc ? '|DESC' : '');
    }

    // If we have a range set, use it to limit the number of results in our
    // query.
    if (isset($this->range)) {
      $query_args['range'] = $this->range;
    }

    $this->query_args = $query_args;
    return $query_args;
  }


  /**
   * Execute the request to thePlatform and get the data back.
   *
   * @return obj
   *   Reference to $this for chainability.
   *
   * @throws Exception
   */
  public function execute() {
    $query_args = $this->buildQueryArgs();

    $base = $this->base_url . ($this->getCategories ? '/categories' : '');

    $response = drupal_http_request($base . '?' . drupal_http_build_query($query_args));

    if ($response->code == 200 && $response->data) {
      $data = json_decode($response->data);
      if (is_array($data->entries)) {
        return $data->entries;
      }
      else {
        throw new Exception('Unexpected API Response');
      }
    }
    else {
      return (object) array();
    }
  }
}
