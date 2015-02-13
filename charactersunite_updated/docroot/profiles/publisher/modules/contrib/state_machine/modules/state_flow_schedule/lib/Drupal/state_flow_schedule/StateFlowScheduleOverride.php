<?php
/**
 * @file
 * SPS (Site Preview Sytem) integration for state flow schedule.
 */

namespace Drupal\state_flow_schedule;

use \Drupal\sps\Plugins\Override\NodeDateOverride;

class StateFlowScheduleOverride extends NodeDateOverride {
  protected $results = array();

  /**
   * Returns a list of vid's to override the default vids to load.
   *
   * @return array
   *   An array of override revision_ids.
   */
  public function getOverrides() {
    $select = db_select('state_flow_schedule', 'sfs')
      ->fields('sfs', array('sid', 'entity_type', 'entity_id', 'revision_id'))
      ->condition('date', $this->timestamp, '<=')
      ->orderBy('revision_id');

    $this->results = $select->execute()->fetchAllAssoc('sid', \PDO::FETCH_ASSOC);

    return $this->processOverrides();
  }

  /**
   * Process the raw override results to return a list.
   *
   * @return array
   *   An array of override revision_ids.
   */
  protected function processOverrides() {
    $list = array();
    foreach ($this->results as $key => $result) {
      if (isset($result['entity_id'])) {
        $result = array($result);
      }

      foreach ($result as $sub => $row) {
        $transform = array();
        $transform['id'] = $row['entity_id'];
        $transform['type'] = $row['entity_type'];
        $transform['revision_id'] = $row['revision_id'] == 0 ? NULL : $row['revision_id'];
        $transform['status'] = $row['revision_id'] > 0 ? 1 : 0;
        $list[$row['entity_type'] . '-' . $row['entity_id']] = $transform;
      }
    }

    return $list;
  }
}
