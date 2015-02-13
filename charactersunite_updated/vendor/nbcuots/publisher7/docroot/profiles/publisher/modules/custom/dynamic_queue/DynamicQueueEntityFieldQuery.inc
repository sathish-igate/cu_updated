<?php

/**
 * @file
 * A custom EFQ class for dynamic queues.
 */

class DynamicQueueEntityFieldQuery extends EntityFieldQuery {

  /**
   * Gets the total number of results and initializes a pager for the query.
   *
   * The pager can be disabled by either setting the pager limit to 0, or by
   * setting this query to be a count query.
   *
   * This version of the function allows for queries with ranges and with pagers
   * to display the correct number of items on the last page even when the items
   * per page do not divide evenly into the total.
   */
  public function initializePager() {
    if ($this->pager && !empty($this->pager['limit']) && !$this->count) {
      $page = pager_find_page($this->pager['element']);
      $count_query = clone $this;
      $this->pager['total'] = $count_query->count()->execute();
      $this->pager['start'] = $page * $this->pager['limit'];
      pager_default_initialize($this->pager['total'], $this->pager['limit'], $this->pager['element']);
      $this->range($this->pager['start'], min($this->pager['limit'], max($this->pager['total'] - $this->pager['start'], 0)));
    }
  }
}
