<?php
/**
 * @file
 * pub_promotional_content.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function pub_promotional_content_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|blog_post|promoted_content';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'blog_post';
  $ds_fieldsetting->view_mode = 'promoted_content';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|blog_post|promoted_content'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|promotional_content|promoted_content';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'promotional_content';
  $ds_fieldsetting->view_mode = 'promoted_content';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|promotional_content|promoted_content'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|tv_episode|promoted_content';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'tv_episode';
  $ds_fieldsetting->view_mode = 'promoted_content';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|tv_episode|promoted_content'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|tv_season|promoted_content';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'tv_season';
  $ds_fieldsetting->view_mode = 'promoted_content';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|tv_season|promoted_content'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|tv_show|promoted_content';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'tv_show';
  $ds_fieldsetting->view_mode = 'promoted_content';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|tv_show|promoted_content'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function pub_promotional_content_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|blog_post|promoted_content';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'blog_post';
  $ds_layout->view_mode = 'promoted_content';
  $ds_layout->layout = 'promotional_content';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'media' => array(
        0 => 'field_photo',
      ),
      'title' => array(
        0 => 'title',
      ),
    ),
    'fields' => array(
      'field_photo' => 'media',
      'title' => 'title',
    ),
    'limit' => array(
      'field_photo' => '1',
    ),
    'classes' => array(),
  );
  $export['node|blog_post|promoted_content'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|promotional_content|promoted_content';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'promotional_content';
  $ds_layout->view_mode = 'promoted_content';
  $ds_layout->layout = 'promotional_content';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'marquee' => array(
        0 => 'field_marquee_text',
        1 => 'field_marquee_position',
      ),
      'media' => array(
        0 => 'field_promotional_content',
      ),
      'details' => array(
        0 => 'field_blurb',
      ),
      'link' => array(
        0 => 'field_link',
        1 => 'field_link_target',
      ),
      'title' => array(
        0 => 'title',
      ),
    ),
    'fields' => array(
      'field_marquee_text' => 'marquee',
      'field_marquee_position' => 'marquee',
      'field_promotional_content' => 'media',
      'field_blurb' => 'details',
      'field_link' => 'link',
      'field_link_target' => 'link',
      'title' => 'title',
    ),
    'classes' => array(),
  );
  $export['node|promotional_content|promoted_content'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|tv_episode|promoted_content';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'tv_episode';
  $ds_layout->view_mode = 'promoted_content';
  $ds_layout->layout = 'promotional_content';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'media' => array(
        0 => 'field_schedule_dynamic_lead',
      ),
      'title' => array(
        0 => 'title',
      ),
      'details' => array(
        0 => 'field_original_air_date',
      ),
    ),
    'fields' => array(
      'field_schedule_dynamic_lead' => 'media',
      'title' => 'title',
      'field_original_air_date' => 'details',
    ),
    'classes' => array(),
  );
  $export['node|tv_episode|promoted_content'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|tv_season|promoted_content';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'tv_season';
  $ds_layout->view_mode = 'promoted_content';
  $ds_layout->layout = 'promotional_content';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'media' => array(
        0 => 'field_schedule_dynamic_lead',
      ),
      'title' => array(
        0 => 'title',
      ),
    ),
    'fields' => array(
      'field_schedule_dynamic_lead' => 'media',
      'title' => 'title',
    ),
    'classes' => array(),
  );
  $export['node|tv_season|promoted_content'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|tv_show|promoted_content';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'tv_show';
  $ds_layout->view_mode = 'promoted_content';
  $ds_layout->layout = 'promotional_content';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'media' => array(
        0 => 'field_schedule_dynamic_lead',
      ),
      'title' => array(
        0 => 'title',
      ),
    ),
    'fields' => array(
      'field_schedule_dynamic_lead' => 'media',
      'title' => 'title',
    ),
    'classes' => array(),
  );
  $export['node|tv_show|promoted_content'] = $ds_layout;

  return $export;
}
