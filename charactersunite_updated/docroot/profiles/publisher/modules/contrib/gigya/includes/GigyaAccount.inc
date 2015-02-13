<?php
/**
 * Created by JetBrains PhpStorm.
 * User: Yaniv Aran-Shamir
 * Date: 10/15/13
 * Time: 2:14 PM
 */

class GigyaAccount {

  private $profile;
  private $data;

  public  function __construct($uid) {
    $res = _gigya_api('accounts.getAccountInfo', array('UID' => $uid));
    if (is_array($res)) {
      $this->profile = $res['profile'];
      $this->data = $res['data'];
    }
  }

  /**
   * @return mixed
   */
  public function getData() {
    return $this->data;
  }

  /**
   * @return mixed
   */
  public function getProfile() {
    return $this->profile;
  }

  public function getProfileField($field_name) {
    return !empty($this->profile[$field_name]) ? $this->profile[$field_name] : NULL;
  }

  public function getDataField($field_name) {
    $path = explode('.', $field_name);
    $branch = array();
    foreach ($path as $p) {
      if (isset($this->data[$p])) {
         if (is_array($this->data[$p])) {
        $branch = $this->data[$p];
      } else {
           return $this->data[$p];
         }
      } elseif (isset($branch[$p])) {
        if (is_array($branch[$p])) {
          $branch = $branch[$p];
        } else {
          return $branch[$p];
        }
      } else {
        return NULL;
      }
    }
  }
}