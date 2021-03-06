<?php
/**
 * @file
 * Settings form to use within the Context module settings page.
 */

/**
 * Expose DART tags as context reactions.
 */
class dart_context_reaction_tags extends context_reaction {
  /**
   * Allow admins to choose what DART tags to hide.
   */
  function options_form($context) {
    // Get existing values for this form.
    $values = $this->fetch_from_context($context);

    // Get a list of all DART tags.
    $tags = dart_tag_load();
    foreach ($tags as $tag) {
      $options[$tag->machinename] = $tag->name;
    }

    if (!empty($tags)) {
      $form = array(
        '#title' => t('Hide these DART tags'),
        '#description' => t('The following DART tags will not be displayed.'),
        '#type' => 'checkboxes',
        '#options' => $options,
        '#default_value' => isset($values) ? $values : array(),
      );
    }
    else {
      $form = array(
        '#type' => 'markup',
        '#markup' => '<div class="messages warning">' . t('No DART tags currently exist.') . '</div>'
      );
    }

    return $form;
  }

  /**
   * Return TRUE as long as no contexts have the machinename-specified tag
   * marked as "hidden".
   */
  function execute(&$tag) {
    // Check each currently set context to see if the DART tag specified by
    // machinename should be displayed or not.
    foreach ($this->get_contexts() as $context_name => $context) {
      if (isset($context->reactions['dart_tags']) && in_array($tag->machinename, $context->reactions['dart_tags'], TRUE)) {
        $tag->disabled = TRUE;
        break;
      }
    }
  }
}
