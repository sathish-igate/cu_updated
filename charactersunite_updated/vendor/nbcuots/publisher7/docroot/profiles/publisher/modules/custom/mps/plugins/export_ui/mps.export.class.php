<?php

/**
 * @file
 * A custom Ctools Export UI class for MPS ad blocks.
 */

/**
 * Customizations of the MPS ad UI.
 */
class mps_blocks_ui extends ctools_export_ui {

  /**
   * Provide the list of sort items.
   */
  function list_sort_options() {
    return array(
      'disabled' => t('Enabled, block name'),
      'name' => t('Block Name'),
      'machine_name' => t('Machine Name'),
      'storage' => t('Storage'),
    );
  }

  /**
   * Build a row based on the item.
   *
   * By default all of the rows are placed into a table by the render
   * method, so this is building up a row suitable for theme('table').
   * This doesn't have to be true if you override both.
   */
  function list_build_row($item, &$form_state, $operations) {
    // Set up sorting
    $name = $item->{$this->plugin['export']['key']};

    // Note: $item->type should have already been set up by export.inc so
    // we can use it safely.
    switch ($form_state['values']['order']) {
      case 'disabled':
        $this->sorts[$name] = empty($item->disabled) . $name;
        break;
      case 'title':
        $this->sorts[$name] = $item->{$this->plugin['export']['admin_title']};
        break;
      case 'name':
        $this->sorts[$name] = $item->block_name;
        break;
      case 'machine_name':
        $this->sorts[$name] = $item->machine_name;
        break;
      case 'storage':
        $this->sorts[$name] = $item->type . $name;
        break;
    }

    $operations = theme('links__ctools_dropbutton', array('links' => $operations, 'attributes' => array('class' => array('links', 'inline'))));
    $this->rows[$name] = array(
      'data' => array(
        array('data' => check_plain($item->block_name), 'class' => array('ctools-export-ui-name')),
        array('data' => check_plain($item->machine_name), 'class' => array('ctools-export-ui-name')),
        array('data' => check_plain($item->type), 'class' => array('ctools-export-ui-storage')),
        array('data' => $operations, 'class' => array('ctools-export-ui-operations')),
      ),
      'class' => !empty($item->disabled) ? array('ctools-export-ui-disabled') : array('ctools-export-ui-enabled'),
    );
  }

  /**
   * Provide the table header.
   *
   * If you've added columns via list_build_row() but are still using a
   * table, override this method to set up the table header.
   */
  function list_table_header() {
    $header = array();

    $header[] = array('data' => t('Block Name'), 'class' => array('ctools-export-ui-name'));
    $header[] = array('data' => t('Slot Name'), 'class' => array('ctools-export-ui-name'));
    $header[] = array('data' => t('Storage'), 'class' => array('ctools-export-ui-storage'));
    $header[] = array('data' => t('Operations'), 'class' => array('ctools-export-ui-operations'));

    return $header;
  }
}
