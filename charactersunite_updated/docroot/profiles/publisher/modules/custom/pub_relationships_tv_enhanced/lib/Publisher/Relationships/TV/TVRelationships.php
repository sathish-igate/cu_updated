<?php

/**
 * @file
 * TVRelationships class.
 */

namespace Publisher\Relationships\TV;

/**
 * Class TVRelationships
 * @package Publisher\Relationships\TV
 */
class TVRelationships {
  public $elements;
  public $show;
  public $season;
  public $episode;
  public $delta;

  /**
   * TVRelationships Constructor.
   *
   * Sets up all the default value and ajax properties.
   *
   * @param $field
   * @param $form
   * @param $form_state
   * @param $items
   * @param $delta
   * @param $langcode
   */
  public function __construct($field, $form, $form_state, $items, $delta, $langcode) {
    $this->form = $form;
    $this->form_state = $form_state;
    $this->langcode = $langcode;
    $this->delta = $delta;
    $this->field_name = $field['field_name'];


    $this->show = $this->elements['show'] = isset($items[$delta]['show']) ? $items[$delta]['show'] : '';
    $this->season = $this->elements['season'] = isset($items[$delta]['season']) ? $items[$delta]['season'] : '';
    $this->episode = $this->elements['episode'] = isset($items[$delta]['episode']) ? $items[$delta]['episode'] : '';

    // If the values are set & is an ajax request always take those over anything.
    if (!empty($this->form_state['triggering_element'])) {
      if (isset($this->form_state['values'][$this->field_name][$this->langcode][$delta]['show'])) {
        $this->show = $this->elements['show'] = $this->form_state['values'][$this->field_name][$this->langcode][$delta]['show'];
      }
      if (isset($this->form_state['values'][$this->field_name][$this->langcode][$delta]['season'])) {
        $this->season = $this->elements['season'] = $this->form_state['values'][$this->field_name][$this->langcode][$delta]['season'];
      }
      if (isset($this->form_state['values'][$this->field_name][$this->langcode][$delta]['episode'])) {
        $this->episode = $this->elements['episode'] = $this->form_state['values'][$this->field_name][$this->langcode][$delta]['episode'];
      }

      // If the triggering element is show we MUST clear out the season.
      $trigger = $this->form_state['triggering_element'];
      if ($trigger['#title'] === t('Show')) {
        $delta_hack = $trigger['#parents'][2];
        if ($delta_hack === $delta) {
          $this->season = $this->elements['season'] = '';
        }
      }
    }
  }

  /**
   * Used to simplified the default value for each element.
   *
   * @see pub_relationships_tv_enhanced_field_widget_form
   *
   * @param $element_name
   *
   * @return string
   */
  public function default_value($element_name) {
    if (!empty($this->elements[$element_name])) {
      return $this->elements[$element_name];
    }

    return '';
  }

  /**
   * Simple Entity Type Mapper from Element Name to Content Type Name.
   *
   * @param $element_name
   *
   * @return bool
   */
  private function entity_type_map($element_name) {
    $map = array(
      'show' => 'tv_show',
      'season' => 'tv_season',
      'episode' => 'tv_episode',
    );

    if (isset($map[$element_name])) {
      return $map[$element_name];
    }

    return FALSE;
  }

  /**
   * Returns options for Show Element.
   */
  public function options_show() {
    return $this->query('show');
  }

  /**
   * Returns options for Season element.
   *
   * @see pub_relationships_tv_enhanced_field_widget_form()
   *
   * @return array
   */
  public function options_season() {
    $options = array();

    if (empty($this->show)) {
      return $options;
    }

    $query = new \EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'tv_season')
      ->fieldCondition($this->field_name, 'show', $this->show, '=');

    $result = $query->execute();
    if (isset($result['node'])) {
      $options = $this->query('season', array_keys($result['node']));
    }

    return $options;
  }

  /**
   * Returns options for Episode element.
   *
   * @see pub_relationships_tv_enhanced_field_widget_form()
   *
   * @return array
   */
  public function options_episode() {
    $options = array();

    if (empty($this->show) || empty($this->season)) {
      return $options;
    }

    $query = new \EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'tv_episode')
      ->fieldCondition($this->field_name, 'season', $this->season, '=');

    $result = $query->execute();
    if (isset($result['node'])) {
      $options = $this->query('episode', array_keys($result['node']));
    }
    return $options;
  }

  /**
   * @param $element_name
   * @param array $ids
   * @param int $limit
   * @param bool $published
   *
   * @return array
   */
  private function query($element_name, $ids = array(), $limit = 0, $published = TRUE) {
    $options = array();

    // Start the Query.
    $query = db_select('node', 'n')
      ->fields('n', array('nid', 'title', 'type'))
      ->orderBy('title');
    $query->addTag('node_access');
    $query->addTag('pub_relationship_tv_entity_reference');
    $query->condition('type', $this->entity_type_map($element_name));

    if (!empty($ids)) {
      $query->condition('nid', $ids);
    }

    if ($limit > 0) {
      $query->range(0, $limit);
    }

    if ($published === FALSE) {
      // Allow anyone to select unpublished nodes. This is required when they're
      // trying to set up a bunch of content to be published together. The user
      // still requires access to the content because we use the node_access
      // tag.
      $query->condition('status', 0);
    }

    $results = $query->execute();
    foreach ($results as $record) {
      $options[$record->nid] = filter_xss($record->title);
    }

    // Make sure results are sorted naturally.
    natcasesort($options);

    return $options;
  }
}
