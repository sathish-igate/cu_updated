<?php

/**
 * @file
 * Contains the operation field handler.
 */
class revision_scheduler_handler_field_operation extends views_handler_field {

  function init(&$view, &$options) {
    parent::init($view, $options);
    // Don't add the additional fields to groupby.
    if (!empty($this->options['link_to_node'])) {
      $this->additional_fields['nid'] = array('table' => 'node', 'field' => 'nid');
      if (module_exists('translation')) {
        $this->additional_fields['language'] = array('table' => 'node', 'field' => 'language');
      }
    }

    $this->additional_fields['entity_type'] = array('table' => 'revision_scheduler', 'field' => 'entity_type');
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['machine_name'] = array('default' => FALSE);
    $options['link_to_node'] = array('default' => isset($this->definition['link_to_node default']) ? $this->definition['link_to_node default'] : FALSE, 'bool' => TRUE);

    return $options;
  }

  /**
   * Provide machine_name and link to node options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['link_to_node'] = array(
      '#title' => t('Link this field to the original piece of content'),
      '#description' => t("Enable to override this field's links."),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to_node']),
    );

    $form['machine_name'] = array(
      '#title' => t('Output machine name'),
      '#description' => t('Display field as the transition machine name.'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['machine_name']),
    );
  }

  /**
   * Render the field.
   */
  function render($values) {
    $value = $this->get_value($values);
    $revision_entity_type = $this->get_value($values, 'entity_type');

    // Set the name of the field to the action unless machine_name is checked.
    if ($this->options['machine_name'] != 1) {

      // Retrieve the revision operation information.
      if ($revision_entity_type) {
        $revision_info = revision_scheduler_entity_revision_operation_get_info($revision_entity_type, $value);
        $value = $revision_info['label'];
      }
    }

    return $this->render_link($this->sanitize_value($value), $values, $revision_entity_type);
  }

  /**
   * Render whatever the data is as a link to the node.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values, $revision_entity_type) {
    if (!empty($this->options['link_to_node']) && !empty($this->additional_fields['nid'])) {
      if ($data !== NULL && $data !== '') {
        $this->options['alter']['make_link'] = TRUE;

        if ($revision_entity_type == 'node') {
          $entity_id = $values->{$this->aliases['entity_id']};
          if (module_exists('workbench_moderation')) {
            $this->options['alter']['path'] = "node/$entity_id/moderation/schedule";
          }
          else {
            $this->options['alter']['path'] = "node/$entity_id/revisions/schedule";
          }
        }

        if (isset($this->aliases['language'])) {
          $languages = language_list();
          $language = $this->get_value($values, 'language');
          if (isset($languages[$language])) {
            $this->options['alter']['language'] = $languages[$language];
          }
          else {
            unset($this->options['alter']['language']);
          }
        }
      }
      else {
        $this->options['alter']['make_link'] = FALSE;
      }
    }
    return $data;
  }
}
