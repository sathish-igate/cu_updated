<?php

/**
 * @file
 * Class TVRelationshipsTest
 */

include_once __DIR__ . '/../lib/Publisher/Relationships/TV/TVRelationships.php';

use Publisher\Relationships\TV\TVRelationships;

class TVRelationshipsTest extends PHPUnit_Framework_TestCase {
  public $tv_relationship;

  public function testDefaultValues() {
    $this->setUp();

    $this->assertEquals(6, $this->tv_relationship->default_value('show'));
    $this->assertEquals(12, $this->tv_relationship->default_value('season'));
    $this->assertEquals(24, $this->tv_relationship->default_value('episode'));
  }

  public function testAjaxSetUp() {
    $this->setUp(TRUE);

    $this->assertEquals(7, $this->tv_relationship->default_value('show'));
    $this->assertEquals(13, $this->tv_relationship->default_value('season'));
    $this->assertEquals(25, $this->tv_relationship->default_value('episode'));
  }

  public function testAjaxSetUpWithDelta() {
    $this->setUp(TRUE, 1);

    $this->assertEquals(7, $this->tv_relationship->default_value('show'));
    $this->assertEquals(13, $this->tv_relationship->default_value('season'));
    $this->assertEquals(25, $this->tv_relationship->default_value('episode'));
  }

  /**
   * Set up the fake arrays require for testing our functionality.
   *
   * When $ajax is passed in the Ajax form_state is passed in to see if our
   * default values are modified.
   */
  protected function setUp($ajax = FALSE, $delta = 0) {
    $form = array();
    $form_state = array();
    $delta = 0;
    $langcode = 'und';
    $field = array('field_name' => 'sample_tv_relationship');
    $items = array(array('show' => 6, 'season' => 12, 'episode' => 24));

    if ($ajax === TRUE) {
      // Fake ajax form_state.
      $form_state = array(
        'triggering_element' => array(
          '#title' => 'Episode',
          '#parents' => array('sample_tv_relationship_field', '', 0, 'sample_tv_relationship'),
          '#title' => 'TV Relationship',
        ),
        'values' => array(
          'sample_tv_relationship' => array(
            $langcode => array(
              $delta => array(
                'show' => 7,
                'season' => 13,
                'episode' => 25,
              ),
            ),
          ),
        ),
      );
    }

    $this->tv_relationship = new TVRelationships($field, $form, $form_state, $items, $delta, $langcode);
  }
}
