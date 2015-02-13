<?php

/**
 * @file
 * Functions needed for devel_generate Fields API integration.
 */

/**
 * Enrich the $object that is about to be saved with arbitrary
 * information in each of its fields.
 **/
function devel_generate_fields(&$object, $obj_type, $bundle) {
  $field_types = field_info_field_types();
  $instances = field_info_instances($obj_type, $bundle);
  $skips = function_exists('drush_get_option') ? drush_get_option('skip-fields', '') : @$_REQUEST['skip-fields'];
  foreach (explode(',', $skips) as $skip) {
    unset($instances[$skip]);
  }
  foreach ($instances as $instance) {
    $field_name = $instance['field_name'];
    $field = field_info_field($field_name);

    $object_field = array();
    // If module handles own multiples, then only call its hook once.
    if (field_behaviors_widget('multiple values', $instance) == FIELD_BEHAVIOR_CUSTOM) {
      $max = 0;
    }
    else {
      switch ($field['cardinality']) {
        case FIELD_CARDINALITY_UNLIMITED:
          $max_cardinality = variable_get('devel_generate_max_field_cardinality', 3);
          $max = rand(0, $max_cardinality);
          break;
        default:
          $max = $field['cardinality'] - 1;
          break;
      }
    }
    for ($i = 0; $i <= $max; $i++) {
      $module = $field_types[$field['type']]['module'];

      // Include any support file that might exist for this field.
      if (in_array($module, array('file', 'image', 'taxonomy', 'number', 'text', 'comment', 'list'))) {
        // devel_generate implements on behalf of core and special friends.
        module_load_include('inc', 'devel_generate', "$module.devel_generate");
      }
      else {
        module_load_include('inc', $module, "$module.devel_generate");
      }
      $function = $module . '_devel_generate';
      if (function_exists($function)) {
        if ($result = $function($object, $field, $instance, $bundle)) {
          if (field_behaviors_widget('multiple values', $instance) == FIELD_BEHAVIOR_CUSTOM) {
            // Fields that handle their own multiples will add their own deltas.
            $object_field = $result;
          }
          else {
            // When multiples are handled by the content module, add a delta for each result.
            $object_field[$i] = $result;
          }
        }
      }
    }
    // TODO: Completely overriding any existing $object->{$field['field_name']}
    // is necessary here because the forum module has a bug where it
    // initializes the property with incorrect data.
    // @see http://drupal.org/node/652176
    $object->{$field['field_name']} = array(
      $field['translatable'] ?  $object->language : LANGUAGE_NONE => $object_field,
    );
  }
}

/**
 * A simple function to return multiple values for fields that use
 * custom multiple value widgets but don't need any other special multiple
 * values handling. This will call the field generation function
 * a random number of times and compile the results into a node array.
 */
function devel_generate_multiple($function, $object, $field, $instance, $bundle) {
  $object_field = array();
  if (function_exists($function)) {
    switch ($field['cardinality']) {
      case FIELD_CARDINALITY_UNLIMITED:
        $max_cardinality = variable_get('devel_generate_max_field_cardinality', 3);
        $max = rand(0, $max_cardinality);
        break;
      default:
        $max = $field['cardinality'] - 1;
        break;
    }
    for ($i = 0; $i <= $max; $i++) {
      $result = $function($object, $field, $instance, $bundle);
      if (!empty($result)) {
        $object_field[$i] = $result;
      }
    }
  }
  return $object_field;
}