<?php

/**
 * @file
 * Describe hooks provided by the Representative Image module.
 */

/**
 * Alter the image path of the representative image to use.
 *
 * You will likely use file_create_url() to help build that URL. An example
 * function name might be mymodule_representative_image_node_image_alter(); for
 * actual usage please see the code at
 * tests/representative_image_test/representative_image_test.module.
 *
 * @param  string $image
 *   The full URL of the representative image.
 *
 * @param  object $entity
 *   The current entity. This is provided for context.
 *
 * @param  string $bundle_name
 *   The name of the bundle we are dealing with. This is provided for context.
 */
function hook_representative_image_ENTITY_TYPE_image_alter(&$image, $entity, $bundle_name) {

}


/**
 * Alters the array of supported field widgets.
 *
 * @param array $widgets
 *    Array of supported field widgets, by default array('image_image', 'media_generic').
 */
function hook_representative_image_widget_type_alter(&$widgets){
  // Field widget type to support.
  $widgets[] = 'some_field_widget';
}

/**
 * Allows other modules to rewrite the output of the 'representative image' Views field.
 *
 * @param string $type
 *   Type of entity.
 * @param object $entity
 *   Entity object.
 * @param string $field
 *   The name of the field.
 * @param string $bundle
 *   The type of bundle.
 * @param object $values
 *   The Views values.
 * @param $options
 *   You can likely find this param in $this->options.
 *
 * @return array
 *   Renderable array, ready for passing to render().
 */
function hook_representative_image_views_handler_render($type, $entity, $field, $bundle = NULL, $values = NULL, $options = NULL) {
  // Field type to support.
  if ($field == 'some_field'){
    $image_field = field_view_field($type, $entity, $field, array('type' => 'some_field_formatter', 'label' => 'hidden'));
    return $image_field;
  }
}
