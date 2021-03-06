<?php
/**
 * @file
 * Custom tokens for Metatag.
 */

/**
 * Implements hook_token_info().
 */
function metatag_token_info() {
  $info = array();

  $info['types']['metatag'] = array(
    'name' => t('Meta tags'),
    'description' => t('Generated by the Metatag module, may not be used to fill in other meta tags.'),
  );

  $metatag_info = metatag_get_info();

  foreach($metatag_info['tags'] as $value) {
    $info['tokens']['metatag'][$value['name']] = array(
      'name' => $value['label'],
      'description' => $value['description']
    );
  }

  if (module_exists('taxonomy')) {
    $info['tokens']['term']['metatag'] = array(
      'name' => t('Metatag.'),
      'description' => t('Metatag.'),
      'type' => 'metatag'
    );
  }

  if (module_exists('node')) {
    $info['tokens']['node']['metatag'] = array(
      'name' => t('Metatag.'),
      'description' => t('Metatag.'),
      'type' => 'metatag'
    );
  }

  return $info;
}

/**
 * Implements hook_tokens().
 */
function metatag_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();

  $sanitize = !empty($options['sanitize']);

  // Metatag tokens.
  if ($type == 'metatag' && !empty($data['metatag'])) {
    $metatag = $data['metatag'];
    foreach ($tokens as $name => $original) {
      if(isset($metatag[$name])){
        $replacements[$original] = $sanitize ? filter_xss($metatag[$name]) : $metatag[$name];
      }
    }
  }

  // Token tokens.
  if ($type == 'term' && !empty($data['term'])) {
    $term = $data['term'];

    if ($metatag_tokens = token_find_with_prefix($tokens, 'metatag')) {
      $result = metatag_token_generate_array($term, 'taxonomy_term', $term->vocabulary_machine_name);
      $replacements += token_generate('metatag', $metatag_tokens, array('metatag' => $result), $options);
    }
  }

  // Node tokens.
  if ($type == 'node' && !empty($data['node'])) {
    $node = $data['node'];

    if ($metatag_tokens = token_find_with_prefix($tokens, 'metatag')) {
      $result = metatag_token_generate_array($node, 'node', $node->type);
      $replacements += token_generate('metatag', $metatag_tokens, array('metatag' => $result), $options);
    }
  }

  return $replacements;
}

/**
 * Generate an array of meta tags for a given entity.
 */
function metatag_token_generate_array($entity, $entity_type, $bundle) {
  if (metatag_entity_supports_metatags($entity_type, $bundle)) {
    $token_type = token_get_entity_mapping('entity', $entity_type);

    $instance = "{$entity_type}:{$bundle}";
    $options = array();
    $options['token data'][$token_type] = $entity;
    $options['entity'] = $entity;

    $metatags = array();
    if (!empty($entity->metatags)) {
      $language = metatag_entity_get_language($entity_type, $entity);
      if (!empty($entity->metatags[$language])) {
        $metatags = $entity->metatags[$language];
      }
    }
    $metatags += metatag_config_load_with_defaults($instance);
    // Process it for entity metatag replacement to avoid infinite recursion.
    $metatags = _metatag_token_process_metatag($metatags, $token_type);

    $result = array();
    foreach ($metatags as $metatag => $data) {
      if ($metatag_instance = metatag_get_instance($metatag, $data)) {
        $result[$metatag] = $metatag_instance->getValue($options);
      }
    }
    return $result;
  }

  return NULL;
}

/**
 * Loop through metatags to replace entity-metatag-token
 * to its actual entity metatag field value to avoid infinite recursion.
 *
 * @param array $metatags
 *   A list entity metatag tokens.
 * @param string $token_type
 *   Entity token type. e.g, 'node','term'.
 *
 * @return array
 *   Retrun entity metatags array.
 */
function _metatag_token_process_metatag($metatags, $token_type) {
  foreach ($metatags as $metatag => $data) {
    // Explode all metatag token in field.
    $data_tokens = token_scan($data['value']);
    if (isset($data_tokens[$token_type])) {
      foreach($data_tokens[$token_type] as $key => $value) {
        $metatag_parts = explode(':', $key);
        // Check entity-metatag-token. Like [<entity_token_type>:metatag:<xyz>].
        if ($metatag_parts[0] == 'metatag') {
          $entity_field = implode(':', array_slice($metatag_parts, 1));
          // Entity metatag field may contain other entity-metatag-token
          // that need to be replace too.
          $replaced_value = metatag_token_entitymetatagtoken_replace($metatags, $metatags[$entity_field]['value'], $token_type);
          $metatags[$metatag]['value'] = str_replace($value, $replaced_value, $metatags[$metatag]['value']);
        }
      }
    }
  }

  return $metatags;
}