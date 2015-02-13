<?php

/**
 * @file
 * State Flow implementation of the State Machine class.
 */

/**
 * Class DynamicQueueStatesEntity.
 */
class DynamicQueueStatesEntity extends StateFlowEntity {

  /**
   * On enter published callback.
   *
   * @see StateFlowEntity::fire_event()
   */
  public function on_enter_published() {
    $this->persist_status(TRUE);
  }

  /**
   * On enter unpublished callback.
   *
   * @see StateFlowEntity::fire_event()
   */
  public function on_enter_unpublished() {
    $this->persist_status(FALSE);
  }

  /**
   * On exit published callback.
   *
   * @see StateFlowEntity::fire_event()
   */
  public function on_exit_published() {
    // Do not do anything. Since onEnterUnpublished will do all the heavy
    // lifting.
  }

  /**
   * Set Published callback.
   *
   * StateFlowEntity calls this directly, so don't use camelCase here.
   *
   * @see StateFlowEntity::fire_event()
   */
  public function set_published($reset = FALSE) {
    $this->object->status = TRUE;
    $this->object->published_revision_id = $this->object->vid;
    if (isset($this->object->is_new) && isset($this->object->dqid)) {
      $this->object->is_new = FALSE;
    }
    $this->object->save();
  }

  /**
   * Persist the entity status.
   *
   * Persist the entity status. WARNING: This won't save the actual entity,
   * don't expect any entity hook to be fired by this method.
   *
   * @param bool $status
   *   The status to be persisted.
   */
  protected function persist_status($status) {
    $this->object->status = $status;
    drupal_write_record('dynamic_queue', $this->object, array('dqid'));
    drupal_write_record('dynamic_queue_revision', $this->object, array('vid'));
  }
}
