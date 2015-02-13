<?php

/**
 * @file
 * Provides action links for Views.
 */

/**
 * A handler to modify the actions available to a scheduled revision.
 *
 * This is essentially a handler for disabling any actions (operations in the
 * view) when MPX value overrides is not enabled.
 *
 * @ingroup views_field_handlers
 */
class pub_mpx_revision_scheduler_handler_field_actions extends revision_scheduler_handler_field_actions {
  /**
   * @var
   */
  protected $mpxValueOverridesEnabled;

  /**
   * @var
   */
  protected $entity;

  /**
   * @var
   */
  protected $publishNotAvailable;

  /**
   * @var
   */
  protected $unpublishNotAvailable;

  /**
   * @var
   */
  protected $completed;

  /**
   * Get bundle type of entity.
   */
  public function getBundleType($id) {
    $entities = entity_load('file', array($id));

    return array_pop($entities);
  }

  /**
   * Render method.
   */
  public function render($values) {
    if (!user_access('schedule revisions')) {
      return '';
    }

    $is_mpxvideo = isset($values->field_data_field_mpx_id_file_entity_type);

    if ($is_mpxvideo) {
      $this->entity = $this->getBundleType($values->fid);

      $this->mpxValueOverridesEnabled = variable_get('pub_mpx_' . $this->entity->type . '_enable_default_field_overrides', FALSE);
      if (!$this->mpxValueOverridesEnabled ||
        ($this->publishNotAvailable && !$this->completed) ||
        ($this->unpublishNotAvailable && !$this->completed)) {

        drupal_set_message(t('Note: Some operations may be unavailable. For details, point to inactive Operations links.'), 'warning', FALSE);
      }
    }

    $operation = array(
      'id' => $values->{$this->aliases['id']},
      'operation' => $values->{$this->aliases['operation']},
      'time_scheduled' => $values->{$this->aliases['time_scheduled']},
      'time_executed' => $values->{$this->aliases['time_executed']},
      'time_queued' => $values->{$this->aliases['time_queued']},
    );

    $this->completed = !empty($operation['time_executed']);

    if ($is_mpxvideo) {
      $this->publishNotAvailable = $this->entity->published == 1 && $operation['operation'] == 'publish' ? TRUE : FALSE;
      $this->unpublishNotAvailable = $this->entity->published == 0 && $operation['operation'] == 'unpublish' ? TRUE : FALSE;
    }

    if ($this->completed) {
      $output = t('Completed');
    }
    elseif (!empty($operation['time_queued'])) {
      $output = t('Queued');
    }
    elseif (!$this->mpxValueOverridesEnabled) {
      $output = t('No operations available');
    }
    else {
      $items = array();
      $value = implode('-', array(
        'run',
        $operation['id'],
        $operation['operation'],
        $operation['time_scheduled'],
        )
      );
      $items['links']['run'] = array(
        'title' => t('Run now'),
        'href' => 'revision-scheduler/' . $operation['id'] . '/run',
        'query' => array(
          'token' => drupal_get_token($value),
        ) + drupal_get_destination(),
      );

      if ($is_mpxvideo) {
        if ($this->publishNotAvailable || $this->unpublishNotAvailable) {
          unset($items['links']['run']['href']);
          $items['links']['run']['attributes'] = array('title' => t("Operation not available because video is already !operation.", array('!operation' => $operation['operation'] . 'ed')));
        }
      }

      $items['links']['delete'] = array(
        'title' => t('Cancel'),
        'href' => 'revision-scheduler/' . $operation['id'] . '/delete',
        'query' => drupal_get_destination(),
      );

      $output = theme('links__ctools_dropbutton', $items);
    }

    return $output;
  }
}
