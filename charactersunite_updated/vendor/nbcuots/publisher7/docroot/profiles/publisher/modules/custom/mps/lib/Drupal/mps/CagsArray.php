<?php

/**
 * @file
 * Class definition for MPS CagsArray.
 */

namespace Drupal\mps;

class CagsArray {

  // Use this string to delimit multiple cag values for a specific cag.
  const MPS_CAG_DELIMITER = '|';

  // Stores the cag array data where cag names are the keys and the values are
  // arrays.
  protected $cagsArray;

  /**
   * Constructor for cagsArray.
   *
   * @param null $initial_cags_array
   *   A default cags array in this form:
   *   - 'cag1' => 'value 1',
   *   - 'cag2' => 'value A|value B|value C'
   */
  public function __construct($initial_cags_array = NULL) {
    $this->cagsArray = is_array($initial_cags_array) ? $initial_cags_array : array();
  }

  /**
   * Add a value to the cags array under a specific cag name.
   *
   * @param string $cag_name
   *   The name of the cag group.
   *
   * @param string $cag_value
   *   A single value to add to the cag group.
   */
  public function addCag($cag_name, $cag_value) {
    $cag_name = $this->formatCagName($cag_name);
    $cag_value = $this->formatCagValue($cag_value);

    $this->cagsArray[$cag_name][] = $cag_value;
  }

  /**
   * Properly format the cag name.
   *
   * @param string $cag_name
   *   The name of the cag group.
   *
   * @return string
   *   A sanitized string appropriate for a cag group name.
   */
  private function formatCagName($cag_name) {
    ctools_include('cleanstring');

    return ctools_cleanstring($cag_name, array(
      'lower_case' => TRUE,
      'replacements' => array(' ' => '_'),
    ));
  }

  /**
   * Properly format the cag value.
   *
   * @param string $cag_value
   *   A single value that is being added to a cag group.
   *
   * @return string
   *   A sanitized string appropriate for a cag value.
   */
  private function formatCagValue($cag_value) {
    ctools_include('cleanstring');

    return ctools_cleanstring($cag_value, array(
      'lower_case' => TRUE,
    ));
  }

  /**
   * Get a properly formatted cags array.
   *
   * @return array
   *   'cag1' => 'value 1',
   *   'cag2' => 'value A|value B|value C'
   */
  public function getCags() {
    foreach ($this->cagsArray as $cag_name => &$cag_value) {
      if (is_array($cag_value)) {
        $this->cagsArray[$cag_name] = implode(self::MPS_CAG_DELIMITER, $cag_value);
      }
      else {
        unset($this->$cag_name);
      }
    }

    return $this->cagsArray;
  }
}
