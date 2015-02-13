<?php

/**
 * @file
 * Definition of dynamic_queue_handler_field_dynamic_queue_revision_is_public.
 */

/**
 * Class dynamic_queue_handler_field_dynamic_queue_revision_is_public.
 *
 * A handler to display if a given revision is the public revision or not.
 *
 * @ingroup views_field_handlers
 */
class dynamic_queue_handler_field_dynamic_queue_revision_is_public extends views_handler_field_boolean {

  /**
   * {@inheritdoc}
   */
  public function construct() {
    parent::construct();
    $this->additional_fields['dqr_dqid'] = 'dqid';
    $this->additional_fields['dqr_vid'] = 'vid';
    $this->additional_fields['dqr_status'] = 'status';
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * {@inheritdoc}
   */
  public function get_value($values, $field = NULL) {
    $vid = $this->get_field_value($values, 'vid');
    $dqid = $this->get_field_value($values, 'dqid');
    $status = $this->get_field_value($values, 'status');

    $public_vid = $this->get_public_revision($dqid);

    if ($vid == $public_vid && $status) {
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Gets value for a given field.
   *
   * @param object $values
   * @param string $field
   *
   * @return mixed
   */
  private function get_field_value($values, $field) {
    $alias = isset($this->aliases[$field]) ? $this->aliases[$field] : '';
    $value = isset($values->$alias) ? $values->$alias : NULL;
    return $value;
  }

  /**
   * Gets the public revision vid for a given DQID.
   *
   * This is based on the value of vid in dynamic_queue table.
   *
   * @param int $dqid
   *
   * @return int
   */
  private function get_public_revision($dqid) {

    if (!empty($dqid)) {
      $public_revision = db_select('dynamic_queue', 'dq')
        ->fields('dq', array('vid'))
        ->condition('dqid', $dqid)
        ->execute()
        ->fetchField();

      if (!empty($public_revision)) {
        return $public_revision;
      }
    }

    return FALSE;
  }

}
