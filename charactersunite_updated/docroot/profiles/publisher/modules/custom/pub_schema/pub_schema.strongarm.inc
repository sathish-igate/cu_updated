<?php
/**
 * @file
 * pub_schema.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pub_schema_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'restws_schema';
  $strongarm->value = array(
    'show' => array(
      'label' => 'Show',
      'properties' => array(
        'name' => array(
          'type' => 'Text',
          'label' => 'Show name',
        ),
        'id' => array(
          'type' => 'Integer',
          'label' => 'Show ID',
        ),
        'description' => array(
          'type' => 'Text',
          'label' => 'Show description',
        ),
        'genre' => array(
          'type' => 'Text',
          'label' => 'Show genre',
        ),
        'seasons' => array(
          'type' => 'Reference',
          'label' => 'The show\'s seasons',
        ),
        'status' => array(
          'type' => 'Boolean',
          'label' => 'Show published status',
        ),
      ),
    ),
    'season' => array(
      'label' => 'Season',
      'properties' => array(
        'name' => array(
          'type' => 'Text',
          'label' => 'Season name',
        ),
        'id' => array(
          'type' => 'Integer',
          'label' => 'Season ID',
        ),
        'description' => array(
          'type' => 'Text',
          'label' => 'Season description',
        ),
        'show' => array(
          'type' => 'Text',
          'label' => 'Show',
        ),
        'episodes' => array(
          'type' => 'Reference',
          'label' => 'The season\'s episodes',
        ),
        'status' => array(
          'type' => 'Boolean',
          'label' => 'Season status',
        ),
      ),
    ),
    'episode' => array(
      'label' => 'Episode',
      'properties' => array(
        'name' => array(
          'type' => 'Text',
          'label' => 'Episode name',
        ),
        'id' => array(
          'type' => 'Integer',
          'label' => 'Episode ID',
        ),
        'description' => array(
          'type' => 'Text',
          'label' => 'Episode description',
        ),
        'show' => array(
          'type' => 'Reference',
          'label' => 'The episode\'s show',
        ),
        'season' => array(
          'type' => 'Reference',
          'label' => 'The episode\'s season',
        ),
        'status' => array(
          'type' => 'Boolean',
          'label' => 'Episode status',
        ),
      ),
    ),
    'blog' => array(
      'label' => 'Blog',
      'properties' => array(
        'name' => array(
          'type' => 'Text',
          'label' => 'Blog name',
        ),
        'id' => array(
          'type' => 'Integer',
          'label' => 'Blog ID',
        ),
        'description' => array(
          'type' => 'Text',
          'label' => 'Blog description',
        ),
        'show' => array(
          'type' => 'Reference',
          'label' => 'The blog\'s show',
        ),
        'season' => array(
          'type' => 'Reference',
          'label' => 'The blog\'s season',
        ),
        'episode' => array(
          'type' => 'Reference',
          'label' => 'The blog\'s episode',
        ),
        'status' => array(
          'type' => 'Boolean',
          'label' => 'Blog status',
        ),
      ),
    ),
    'gallery' => array(
      'label' => 'Gallery',
      'properties' => array(
        'name' => array(
          'type' => 'Text',
          'label' => 'Gallery name',
        ),
        'id' => array(
          'type' => 'Integer',
          'label' => 'Gallery ID',
        ),
        'description' => array(
          'type' => 'Text',
          'label' => 'Gallery description',
        ),
        'photos' => array(
          'type' => 'Image',
          'label' => 'Gallery photos',
        ),
        'show' => array(
          'type' => 'Reference',
          'label' => 'The gallery\'s show',
        ),
        'season' => array(
          'type' => 'Reference',
          'label' => 'The gallery\'s season',
        ),
        'episode' => array(
          'type' => 'Reference',
          'label' => 'The gallery\'s episode',
        ),
        'status' => array(
          'type' => 'Boolean',
          'label' => 'Gallery status',
        ),
      ),
    ),
  );
  $export['restws_schema'] = $strongarm;

  return $export;
}
