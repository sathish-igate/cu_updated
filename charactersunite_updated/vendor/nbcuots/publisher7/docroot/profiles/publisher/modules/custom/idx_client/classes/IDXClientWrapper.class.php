<?php
/**
 * @file
 * IDX Client Wrapper. A specific wrapper around the IDX member.* APIs
 * Used by the IDX Client module.
 *
 * @see IDXClient.class.php
 */

class IDXClientWrapper extends IDXClient {
  /**
   * @var array member from IDX.
   */
  protected $member = array();

  /**
   * Class constructor method.
   *
   * Optionally gets IDX APIs settings. But can uses default settings from the
   * idx_client module.
   *
   * @param string $api_key
   *   (optional) A brand API key.
   * @param string $brand_id
   *   (optional) A brand ID key.
   * @param array $api_env
   *   (optional) A brand environment url.
   * @param bool $debug
   *   (optional) If true, extra debug messages will be displayed.
   */
  public function __construct($api_key = NULL, $brand_id = NULL, $api_env = array(), $debug = FALSE) {
    if (!$api_key) {
      $api_key = idx_client_get_api_key();
    }
    if (!$brand_id) {
      $brand_id = idx_client_get_api_brand_id();
    }
    if (!$api_env) {
      $api_env = idx_client_get_api_url();
    }
    try {
      parent::__construct($api_key, $brand_id, $api_env, $debug);
    }
    catch (Exception $e) {
      watchdog('IDX', $e->getMessage(), array(), WATCHDOG_WARNING);
    }
  }

  /**
   * Retrieve a member info from the IDX service.
   *
   * @param string $member_id
   *   A uuid, email address or username.
   * @param string $provider
   *   A provider name. Default: 'idx'.
   * @param string $view
   *   'most-recent-user', 'most-recent-all', or 'best-guess'
   *   (optional) How to filter the data on the user, defaults to
   *   most-recent-user.
   * @param string $brands
   *   (optional) The brands to retrieve data from, defaults to all.
   *
   * @return bool
   *   Returns TRUE on success and FALSE on failure
   */
  public function memberGet($member_id, $provider = 'idx', $view = NULL, $brands = NULL) {
    try {
      $member = parent::memberGet($member_id, $view, $provider, $brands);
      if ($member) {
        $this->member = $member;
        return TRUE;
      }
      else {
        return FALSE;
      }
    }
    catch (Exception $e) {
      watchdog('IDX', $e->getMessage(), array(), WATCHDOG_WARNING);
      return FALSE;
    }
  }

  /**
   * Put a member info into the IDX service.
   *
   * @param string $brand
   *   The brand affected by this operation, if not set, will use the brand
   *   specified in the constructor if it was only one brand.
   *
   * @return bool
   *   Returns TRUE on success and FALSE on failure
   */
  public function memberPut($brand = NULL) {
    try {
      if (!empty($this->member)) {
        $result = parent::memberPut($this->member, $brand);
        if ($result) {
          $this->member = $result;
          return TRUE;
        }
        return FALSE;
      }
      else {
        watchdog('IDX', 'No member data before send to IDX service.', array(), WATCHDOG_WARNING);
        return FALSE;
      }
    }
    catch (Exception $e) {
      watchdog('IDX', $e->getMessage(), array(), WATCHDOG_WARNING);
      return FALSE;
    }
  }

  /**
   * Returns a member data.
   *
   * @return array
   *   Member data.
   */
  public function getMember() {
    return $this->member;
  }

  /**
   * Returns member data from member array by a filed.
   *
   * @param string $field
   *   A field name in a member array.
   *
   * @return array
   *   Member data.
   */
  public function getMemberData($field) {
    if (!$field) {
      return array();
    }
    return isset($this->member[$field]) ? $this->member[$field] : array();
  }

  /**
   * Returns brand data from member info.
   *
   * @param string $brand_field
   *   A brand filed.
   *
   * @return array
   *   Brand data.
   */
  public function getMemberBrandData($brand_field = IDX_CLIENT_BRAND_DATA) {
    return $this->getMemberData($brand_field);
  }

  /**
   * Set data into a member field.
   *
   * @param string $field
   *   A field name.
   * @param mixed $value
   *   A field value.
   *
   * @return bool
   *   Returns TRUE on success and FALSE on failure
   */
  public function setMemberData($field, $value) {
    if (!$field) {
      return FALSE;
    }
    if (isset($this->member[$field])) {
      $this->member[$field] = $value;
      return TRUE;
    }
    else {
      watchdog('IDX', 'The field "!field" is not exist in setMemberData() method.', array('!field' => $field), WATCHDOG_WARNING);
      return FALSE;
    }
  }

  /**
   * Set data into a member 'brand data' field.
   *
   * @param string $field
   *   A field name.
   * @param mix $value
   *   A field value.
   * @param string $brand_field
   *   A brand field name.
   *
   * @return bool
   *   Returns TRUE on success and FALSE on failure
   */
  public function setMemberBrandData($field, $value, $brand_field = IDX_CLIENT_BRAND_DATA) {
    if (!$field) {
      return FALSE;
    }
    if (isset($this->member[$brand_field])) {
      $this->member[$brand_field][$field] = $value;
      return TRUE;
    }
    else {
      watchdog('IDX', 'The brand data field "!bf" is not exist in setMemberBrandData() method.', array(
        '!bf' => $brand_field,
      ), WATCHDOG_WARNING);
      return FALSE;
    }
  }

}
