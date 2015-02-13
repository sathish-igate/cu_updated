<?php

/**
 * Implements hook_preprocess_maintenance_page().
 */
function characterunite_preprocess_maintenance_page(&$variables) {
  // By default, site_name is set to Drupal if no db connection is available
  // or during site installation. Setting site_name to an empty string makes
  // the site and update pages look cleaner.
  // @see template_preprocess_maintenance_page
  if (!$variables['db_is_active']) {
    $variables['site_name'] = '';
  }
}

/**
 * Override or insert variables into the maintenance page template.
 */
function characterunite_process_maintenance_page(&$variables) {
  // Always print the site name and slogan, but if they are toggled off, we'll
  // just hide them visually.
  $variables['hide_site_name']   = theme_get_setting('toggle_name') ? FALSE : TRUE;
  $variables['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
  if ($variables['hide_site_name']) {
    // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
    $variables['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));
  }
  if ($variables['hide_site_slogan']) {
    // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
    $variables['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
  }
}

/**
 * Implements hook_preprocess_node().
 *
 * Override or insert variables into the node templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered
 */
function characterunite_preprocess_node(&$variables, $hook) {
  $node = $variables['node'];
  $language = $node->language;

  if ($variables['view_mode'] == 'full' && node_is_page($variables['node'])) {
    $variables['classes_array'][] = 'node-full';
  }
  // Get a list of all the regions for this theme
  foreach (system_region_list($GLOBALS['theme']) as $region_key => $region_name) {
    // Get the content for each region and add it to the $region variable
    if ($blocks = block_get_blocks_by_region($region_key)) {
      $variables['region'][$region_key] = $blocks;
    }
    else {
      $variables['region'][$region_key] = array();
    }
  }

  /** Video Section Start **/
  if(!(empty($node->field_video_section))) {
    $field_video_sections = field_get_items('node', $node, 'field_video_section');
    if (!empty($field_video_sections)) {
      $field_video_section_items = array();
      foreach ($field_video_sections as $field_video_section) {
        $field_video_section_items[] = entity_revision_load('field_collection_item', $field_video_section['revision_id']); //load current revision of collection
      }
      foreach ($field_video_section_items as $item) {
        $field_video = characterunite_reset(field_get_items('field_collection_item', $item, 'field_video_id'));
        $variables['field_video_id'] = (isset($field_video['value'])?$field_video['value']:'');

        $transcript_title = characterunite_reset(field_get_items('field_collection_item', $item, 'field_transcript_title'));
        $variables['field_transcript_title'] = (isset($transcript_title['value'])?$transcript_title['value']:'');

        $transcript_description = characterunite_reset(field_get_items('field_collection_item', $item, 'field_transcript_description'));
        $variables['field_transcript_description'] = (isset($transcript_description['value'])?$transcript_description['value']:'');

        $transcript_more_link = characterunite_reset(field_get_items('field_collection_item', $item, 'field_transcript_more_link'));
        $variables['field_transcript_more_link'] = (isset($transcript_more_link['value'])?$transcript_more_link['value']:'');

        $video_description = characterunite_reset(field_get_items('field_collection_item', $item, 'field_video_description'));
        $variables['field_video_description'] = (isset($video_description['value'])?$video_description['value']:'');
      }
    }
  }
  /** Video Section End **/

  /** Black Box Section Start **/
  if(!(empty($node->field_black_box_section))) {
    $field_black_box = field_get_items('node', $node, 'field_black_box_section');
    if (!empty($field_black_box)) {
      $field_black_box_section_items = array();
      foreach ($field_black_box as $field_black_box_section) {
        $field_black_box_section_items[] = entity_revision_load('field_collection_item', $field_black_box_section['revision_id']); //load current revision of collection
      }
      foreach ($field_black_box_section_items as $item) {
        $black_box_title = characterunite_reset(field_get_items('field_collection_item', $item, 'field_black_box_title'));
        $variables['field_black_box_title'] = (isset($black_box_title['value'])?$black_box_title['value']:'');

        $black_box_title_2 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_black_box_title_2'));
        $variables['field_black_box_title_2'] = (isset($black_box_title_2['value'])?$black_box_title_2['value']:'');

        $black_box_description = characterunite_reset(field_get_items('field_collection_item', $item, 'field_black_box_description'));
        $field_black_box_description = (isset($black_box_description['value'])?$black_box_description['value']:'');

        $black_box_more_link = characterunite_reset(field_get_items('field_collection_item', $item, 'field_black_box_more_link'));
        $variables['field_black_box_more_link'] = (isset($black_box_more_link['value'])?$black_box_more_link['value']:'');
      }
      if ($field_black_box_description != '' && ($field_black_box_description == strip_tags($field_black_box_description))) {
        $variables['field_black_box_description'] = '<p>'.$field_black_box_description.'</p>';
      }
      else {
        $variables['field_black_box_description'] = $field_black_box_description;
      }
    }
  }
  /** Black Box Section End **/
  
  /** Description Section Start **/
  if(!(empty($node->field_description_section))) {
    $field_description_sections = field_get_items('node', $node, 'field_description_section');
    $description_section = array();
    if (!empty($field_description_sections)) {
      $field_description_section_items = array();
      foreach ($field_description_sections as $field_description_section) {
        $field_description_section_items[] = entity_revision_load('field_collection_item', $field_description_section['revision_id']); //load current revision of collection
      }
      $index = 0;
      foreach ($field_description_section_items as $item) {
        $ds_title_1 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_ds_title_1'));
        $description_section[$index]['field_ds_title_1'] = (isset($ds_title_1['value'])?$ds_title_1['value']:'');

        $ds_title_2 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_ds_title_2'));
        $description_section[$index]['field_ds_title_2'] = (isset($ds_title_2['value'])?$ds_title_2['value']:'');

        $ds_body = characterunite_reset(field_get_items('field_collection_item', $item, 'field_ds_body'));
        $description_section[$index]['field_ds_body'] = (isset($ds_body['value'])?$ds_body['value']:'');

        $ds_link_url = characterunite_reset(field_get_items('field_collection_item', $item, 'field_ds_link'));
        $field_ds_link_url = (isset($ds_link_url['url'])?($ds_link_url['url']):'');
        $field_ds_link_label = (isset($ds_link_url['title'])?($ds_link_url['title']):'');
        $field_ds_link_target = (isset($ds_link_url['attributes']['target'])?($ds_link_url['attributes']['target']):'');
        $description_section[$index]['ds_link_tag'] = '';
        if ($field_ds_link_url != '') {
          $description_section[$index]['ds_link_tag'] = l($field_ds_link_label, $field_ds_link_url, array('attributes' => array('target' => $field_ds_link_target)));
        } 

        $ds_position = characterunite_reset(field_get_items('field_collection_item', $item, 'field_ds_position'));
        $description_section[$index]['field_ds_position'] = (isset($ds_position['tid'])?taxonomy_term_load($ds_position['tid'])->name:'');
        $index++;
      }
      if (isset($description_section))
        $variables['description_section'] = $description_section;      
    }
  }
  /** Description Section End **/

  /** Half Module Section Start **/
  if(!(empty($node->field_half_module_section))) {
    $half_module = array();
    $field_half_module_sections = field_get_items('node', $node, 'field_half_module_section');
    if (!empty($field_half_module_sections)) {
      $field_half_module_section_items = array();
      foreach ($field_half_module_sections as $field_half_module_section) {
        $field_half_module_section_items[] = entity_revision_load('field_collection_item', $field_half_module_section['revision_id']); //load current revision of collection
      }
      $iteration = 0;
      foreach ($field_half_module_section_items as $item) {
        $half_module_title_1 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_half_module_title_1'));
        $field_half_module_title_1 = (isset($half_module_title_1['value'])?$half_module_title_1['value']:'');

        $half_module_title_2 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_half_module_title_2'));
        $field_half_module_title_2 = (isset($half_module_title_2['value'])?$half_module_title_2['value']:'');

        $half_module_description = characterunite_reset(field_get_items('field_collection_item', $item, 'field_half_module_description'));
        $field_half_module_description = (isset($half_module_description['value'])?$half_module_description['value']:'');

        $half_module_link = characterunite_reset(field_get_items('field_collection_item', $item, 'field_half_module_link'));
        $field_half_module_link_url = (isset($half_module_link['url'])?($half_module_link['url']):'');
        $field_half_module_link_label = (isset($half_module_link['title'])?$half_module_link['title']:'');
        $field_half_module_link_target = (isset($half_module_link['attributes']['target'])?($half_module_link['attributes']['target']):'');

        $ds_position = characterunite_reset(field_get_items('field_collection_item', $item, 'field_ds_position'));
        $field_ds_position = (isset($ds_position['tid'])?taxonomy_term_load($ds_position['tid'])->name:'');
        if (substr($field_half_module_link_url, 0, 4) != 'http' && substr($field_half_module_link_url, 0, 1) != '/' && $field_half_module_link_url != '') {
          $field_half_module_link_url = '/'.$field_half_module_link_url;
        }
        $half_module_link_tag = '';
        if ($field_half_module_link_url != '') {
          $half_module_link_tag = '<p><a href="'.$field_half_module_link_url.'" target="'.$field_half_module_link_target.'" class="uppercase">'.$field_half_module_link_label.'</a></p>';
        }
    
        if ($field_half_module_title_1 != '' || $field_half_module_title_2 != '' || $field_half_module_description != '' || $field_half_module_link_url != '') {
          $half_module[$iteration]['field_half_module_title_1'] = $field_half_module_title_1;
          $half_module[$iteration]['field_half_module_title_2'] = $field_half_module_title_2;
          $half_module[$iteration]['field_half_module_description'] = $field_half_module_description;
          $half_module[$iteration]['half_module_link_tag'] = $half_module_link_tag;
          if (strtolower($field_ds_position) != 'right') {
            $field_half_module_left = $half_module;
          }
          else {
            $field_half_module_right = $half_module;
          }
        }
        $iteration++;
      }
      if (isset($field_half_module_left))
        $variables['field_half_module_left'] = $field_half_module_left;
      if (isset($field_half_module_right))
        $variables['field_half_module_right'] = $field_half_module_right;      
    }
  }
  /** Half Module Section End **/

  /** Download File Section Start **/
  if(!(empty($node->field_file_download_section))) {
    $file_download = array();
    $field_file_download_sections = field_get_items('node', $node, 'field_file_download_section');
    if (!empty($field_file_download_sections)) {
      $field_file_download_section_items = array();
      foreach ($field_file_download_sections as $field_file_download_section) {
        $field_file_download_section_items[] = entity_revision_load('field_collection_item', $field_file_download_section['revision_id']); //load current revision of collection
      }
      $iteration = 0;
      foreach ($field_file_download_section_items as $item) {
        $download_title_1 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_file_download_title_1'));
        $field_file_download_title_1 = (isset($download_title_1['value'])?$download_title_1['value']:'');

        $download_title_2 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_file_download_title_2'));
        $field_file_download_title_2 = (isset($download_title_2['value'])?$download_title_2['value']:'');

        $download_description = characterunite_reset(field_get_items('field_collection_item', $item, 'field_file_download_description'));
        $field_file_download_description = (isset($download_description['value'])?$download_description['value']:'');

        $download_file = (field_get_items('field_collection_item', $item, 'field_file_download_file'));

        $ds_position = characterunite_reset(field_get_items('field_collection_item', $item, 'field_ds_position'));
        $field_ds_position = (isset($ds_position['tid'])?taxonomy_term_load($ds_position['tid'])->name:'');

        $file_download_tag = array();
        $download_file_count = count($download_file);
        if ($download_file_count > 0) {
          for($file = 0; $file < $download_file_count; $file++) {
            if ($download_file[$file]['uri'] != '')
              $file_download_tag[$file]['file'] = '<p>'.l($download_file[$file]['description'], file_create_url($download_file[$file]['uri']), array('attributes' => array('target' => '_blank', 'class' => 'cta uppercase download'))).'</p>';
          }
        }
        $download_link = field_get_items('field_collection_item', $item, 'field_file_download_link');

        $file_download_link_tag = array();
        $download_link_count = count($download_link);
        if ($download_link_count > 0) {
          for($link = 0; $link < $download_link_count; $link++) {
            if ($download_link[$link]['url'] != '')
            $file_download_link_tag[$link]['link'] = '<p>'.l($download_link[$link]['title'], file_create_url($download_link[$link]['url']), array('attributes' => array('target' => '_blank', 'class' => 'cta uppercase'))).'</p>';
          }
        }

        if ($field_file_download_title_1 != '' || $field_file_download_title_2 != '' || $field_file_download_description != '' || $file_download_tag != '') {
          $file_download[$iteration]['field_file_download_title_1'] = $field_file_download_title_1;
          $file_download[$iteration]['field_file_download_title_2'] = $field_file_download_title_2;
          $file_download[$iteration]['field_file_download_description'] = $field_file_download_description;
          $file_download[$iteration]['file_download_tag'] = $file_download_tag;
          $file_download[$iteration]['file_download_link_tag'] = $file_download_link_tag;
          if (strtolower($field_ds_position) != 'right') {
            $field_file_download_left = $file_download;
          }
          else {
            $field_file_download_right = $file_download;
          }
        }
        $iteration++;
      }
      if (isset($field_file_download_left))
        $variables['field_file_download_left'] = $field_file_download_left;
      if (isset($field_file_download_right))
        $variables['field_file_download_right'] = $field_file_download_right;      
    }
  }
  /** Download File Section End **/

  /** Related Link Section Start **/
  if(!(empty($node->field_link_section))) {
    $link_section = array();
    $field_link_sections = field_get_items('node', $node, 'field_link_section');
    if (!empty($field_link_sections)) {
      $field_link_section_items = array();
      foreach ($field_link_sections as $field_link_section) {
        $field_link_section_items[] = entity_revision_load('field_collection_item', $field_link_section['revision_id']); //load current revision of collection
      }
      $index = 0;
      foreach ($field_link_section_items as $item) {
        $link_title_1 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_link_title_1'));
        $field_link_title_1 = (isset($link_title_1['value'])?$link_title_1['value']:'');

        $link_title_2 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_link_title_2'));
        $field_link_title_2 = (isset($link_title_2['value'])?$link_title_2['value']:'');

        $field_links = field_get_items('field_collection_item', $item, 'field_links');
        
        $link_section[$index]['field_link_title_1'] = $field_link_title_1;
        $link_section[$index]['field_link_title_2'] = $field_link_title_2;
        $field_links_count = count($field_links);
        if ($field_links_count > 0) {
          for($take_action = 0; $take_action < $field_links_count; $take_action++) {
            if ($field_links[$take_action]['url'] != '') {
              if (substr($field_links[$take_action]['url'], 0, 4) != 'http' && substr($field_links[$take_action]['url'], 0, 1) != '/' && $field_links[$take_action]['url'] != '') {
                $field_links[$take_action]['url'] = '/'.$field_links[$take_action]['url'];
              }      
              $related_links = '<a href="'.$field_links[$take_action]['url'].'" class="cta uppercase" target="_blank">'.$field_links[$take_action]['title'].'</a>';
              $link_section[$index]['related_links'][$take_action]['links'] = $related_links;
            }
          }
        }        
      }
      $variables['link_section'] = $link_section;
    }
  }
  /** Related Link Section Start **/
  
  /** Related Videos Section Start **/
  if(!(empty($node->field_related_videos_section))) {
    $related_videos = array(); 
    $field_related_videos_sections = field_get_items('node', $node, 'field_related_videos_section');
    if (!empty($field_related_videos_sections)) {
      $field_related_videos_section_items = array();
      foreach ($field_related_videos_sections as $field_related_videos_section) {
        $field_related_videos_section_items[] = entity_revision_load('field_collection_item', $field_related_videos_section['revision_id']); //load current revision of collection
      }
      $index = 0;
      foreach ($field_related_videos_section_items as $item) {
        $related_videos_title_1 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_related_videos_title_1'));
        $field_related_videos_title_1 = (isset($related_videos_title_1['value'])?$related_videos_title_1['value']:'');

        $related_videos_title_2 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_related_videos_title_2'));
        $field_related_videos_title_2 = (isset($related_videos_title_2['value'])?$related_videos_title_2['value']:'');

        $related_videos_description = characterunite_reset(field_get_items('field_collection_item', $item, 'field_related_videos_description'));
        $field_related_videos_description = (isset($related_videos_description['value'])?$related_videos_description['value']:'');

        $related_videos_link = characterunite_reset(field_get_items('field_collection_item', $item, 'field_related_videos_link'));
        $field_related_videos_link_url = (isset($related_videos_link['url'])?($related_videos_link['url']):'');
        $field_related_videos_link_label = (isset($related_videos_link['title'])?$related_videos_link['title']:'');
        $field_related_videos_link_target = (isset($related_videos_link['attributes']['target'])?($related_videos_link['attributes']['target']):'');

        $related_videos_position = characterunite_reset(field_get_items('field_collection_item', $item, 'field_related_videos_position'));
        $field_related_videos_position = (isset($related_videos_position['tid'])?taxonomy_term_load($related_videos_position['tid'])->name:'');

        if ($field_related_videos_title_1 != '' || $field_related_videos_title_2 != '') {
          $related_videos_link_tag = '';
          if ($field_related_videos_link_url != '') {
            if (substr($field_related_videos_link_url, 0, 4) != 'http' && substr($field_related_videos_link_url, 0, 1) != '/') {
              $field_related_videos_link_url = '/'.$field_related_videos_link_url;
            }
            $related_videos_link_tag = '<p><a href="'.$field_related_videos_link_url.'" class="uppercase" target="'.$field_related_videos_link_target.'">'.$field_related_videos_link_label.'</a></p>';
          }

          $related_videos[$index]['field_related_videos_title_1'] = $field_related_videos_title_1;
          $related_videos[$index]['field_related_videos_title_2'] = $field_related_videos_title_2;
          $related_videos[$index]['field_related_videos_description'] = $field_related_videos_description;
          $related_videos[$index]['related_videos_link_tag'] = $related_videos_link_tag;
        
          $field_related_videos_iterations = field_get_items('field_collection_item', $item, 'field_related_videos_iteration');
          if (!empty($field_related_videos_iterations)) {
            $field_related_videos_iteration_items = array();
            foreach ($field_related_videos_iterations as $field_related_videos_iteration) {
              $field_related_videos_iteration_items[] = entity_revision_load('field_collection_item', $field_related_videos_iteration['revision_id']); //load current revision of collection
            }
            $iteration = 0;
            foreach ($field_related_videos_iteration_items as $iteration_item) {
              $rvi_video_title = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_rvi_video_title'));
              $field_rvi_video_title = (isset($rvi_video_title['value'])?$rvi_video_title['value']:'');  

              $rvi_video_info = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_rvi_video_info'));
              $field_rvi_video_info = (isset($rvi_video_info['value'])?$rvi_video_info['value']:'');  

              $rvi_video_thumbnail = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_rvi_video_thumbnail'));
              $field_rvi_video_thumbnail = (isset($rvi_video_thumbnail['uri'])?$rvi_video_thumbnail['uri']:'');
              //$rvi_video_thumbnail = (field_get_items('field_collection_item', $iteration_item, 'field_rvi_video_thumbnail'));
              //$field_rvi_video_thumbnail = field_view_value('field_collection_item', $iteration_item, 'field_rvi_video_thumbnail', $rvi_video_thumbnail[0], array('type' => 'image','settings' => array('image_style' => 'thumbnail')));
              $rvi_video_link = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_rvi_video_link'));
              $field_rvi_video_link_url = (isset($rvi_video_link['url'])?$rvi_video_link['url']:'');  
              $field_rvi_video_link_label = (isset($rvi_video_link['title'])?$rvi_video_link['title']:'');  
              $field_rvi_video_link_target = (isset($rvi_video_link['attributes']['target'])?$rvi_video_link['attributes']['target']:'_self');
      
              if (substr($field_rvi_video_link_url, 0, 4) != 'http' && substr($field_rvi_video_link_url, 0, 1) != '/' && $field_rvi_video_link_url != '') {
                //$field_rvi_video_link_url = '/'.$field_rvi_video_link_url;
              }

              $related_videos[$index]['related_videos_iteration'][$iteration]['field_rvi_video_title'] = $field_rvi_video_title;
              $related_videos[$index]['related_videos_iteration'][$iteration]['field_rvi_video_info'] = $field_rvi_video_info;
              $related_videos[$index]['related_videos_iteration'][$iteration]['field_rvi_video_thumbnail'] = $field_rvi_video_thumbnail;
              $related_videos[$index]['related_videos_iteration'][$iteration]['field_rvi_video_link_url'] = $field_rvi_video_link_url;
              $related_videos[$index]['related_videos_iteration'][$iteration]['field_rvi_video_link_label'] = $field_rvi_video_link_label;
              $related_videos[$index]['related_videos_iteration'][$iteration]['field_rvi_video_link_target'] = $field_rvi_video_link_target;
              $iteration++;
            }
          }
          if (strtolower($field_related_videos_position) != 'right') {
            $related_videos_left = $related_videos;
          }
          else {
            $related_videos_right = $related_videos;
          }
        }
        $index++;
      }
      if (isset($related_videos_left))
        $variables['related_videos_left'] = $related_videos_left;
      if (isset($related_videos_right))
        $variables['related_videos_right'] = $related_videos_right;
    }
  }
  /** Related Videos Section End **/
  

  /** Related Images Section Start **/
  if(!(empty($node->field_related_image_section))) {
    $related_images = array();
    $field_related_image_sections = field_get_items('node', $node, 'field_related_image_section');
    if (!empty($field_related_image_sections)) {
      $field_related_image_section_items = array();
      foreach ($field_related_image_sections as $field_related_image_section) {
        $field_related_image_section_items[] = entity_revision_load('field_collection_item', $field_related_image_section['revision_id']); //load current revision of collection
      }
      $index = 0;
      foreach ($field_related_image_section_items as $item) {
      
        $related_image_title_1 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_related_image_title_1'));
        $field_related_image_title_1 = (isset($related_image_title_1['value'])?$related_image_title_1['value']:'');

        $related_image_title_2 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_related_image_title_2'));
        $field_related_image_title_2 = (isset($related_image_title_2['value'])?$related_image_title_2['value']:'');

        $related_image_description = characterunite_reset(field_get_items('field_collection_item', $item, 'field_related_image_description'));
        $field_related_image_description = (isset($related_image_description['value'])?$related_image_description['value']:'');

        $related_image_link = characterunite_reset(field_get_items('field_collection_item', $item, 'field_related_image_link'));
        $field_related_image_link_url = (isset($related_image_link['url'])?($related_image_link['url']):'');
        $field_related_image_link_label = (isset($related_image_link['title'])?$related_image_link['title']:'');
        $field_related_image_link_target = (isset($related_image_link['attributes']['target'])?($related_image_link['attributes']['target']):'');

        $related_image_position = characterunite_reset(field_get_items('field_collection_item', $item, 'field_related_image_position'));
        $field_related_image_position = (isset($related_image_position['tid'])?taxonomy_term_load($related_image_position['tid'])->name:'');
            
        if ($field_related_image_title_1 != '' || $field_related_image_title_2 != '') {
          $related_image_link_tag = '';
          if ($field_related_image_link_url != '') {
            $related_image_link_tag = '<p>'.l($field_related_image_link_label, $field_related_image_link_url, array('attributes' => array('target' => $field_related_image_link_target, 'class' => 'cta uppercase'))).'</p>';
          }
          
          $related_images[$index]['field_related_image_title_1'] = $field_related_image_title_1;
          $related_images[$index]['field_related_image_title_2'] = $field_related_image_title_2;
          $related_images[$index]['field_related_image_description'] = $field_related_image_description;
          $related_images[$index]['related_image_link_tag'] = $related_image_link_tag;
        
          $field_related_image_iterations = field_get_items('field_collection_item', $item, 'field_related_image_iteration');
          if (!empty($field_related_image_iterations)) {
            $field_related_image_iteration_items = array();
            foreach ($field_related_image_iterations as $field_related_image_iteration) {
              $field_related_image_iteration_items[] = entity_revision_load('field_collection_item', $field_related_image_iteration['revision_id']); //load current revision of collection
            }
            $iteration = 0;
            foreach ($field_related_image_iteration_items as $iteration_item) {
              $rii_image = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_rii_image'));
              $field_rii_image = (isset($rii_image['uri'])?$rii_image['uri']:'');  

              $rii_image_link = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_rii_image_link'));
              $field_rii_image_link_url = (isset($rii_image_link['url'])?$rii_image_link['url']:'');  
              $field_rii_image_link_label = (isset($rii_image_link['title'])?$rii_image_link['title']:'');  
              $field_rii_image_link_target = (isset($rii_image_link['attributes']['target'])?$rii_image_link['attributes']['target']:'_self');
              if (substr($field_rii_image_link_url, 0, 4) != 'http' && substr($field_rii_image_link_url, 0, 1) != '/') {
                $field_rii_image_link_url = '/'.$field_rii_image_link_url;
              }
              $related_images[$index]['related_images_iteration'][$iteration]['field_rii_image'] = $field_rii_image;
              $related_images[$index]['related_images_iteration'][$iteration]['field_rii_image_link_url'] = $field_rii_image_link_url;
              $related_images[$index]['related_images_iteration'][$iteration]['field_rii_image_link_label'] = $field_rii_image_link_label;
              $related_images[$index]['related_images_iteration'][$iteration]['field_rii_image_link_target'] = $field_rii_image_link_target;
              $iteration++;
            }
          }
          if (strtolower($field_related_image_position) != 'right') {
            $related_images_left = $related_images;
          }
          else {
            $related_images_right = $related_images;
          }
        }
        $index++;$related_images = array();
      }
      if (isset($related_images_left))
        $variables['related_images_left'] = $related_images_left;
      if (isset($related_images_right))
        $variables['related_images_right'] = $related_images_right;      
    }
  }
  /** Related Images Section End **/
  

  /** Image Landing Section Start **/
  if(!(empty($node->field_ilp_image))) {
    $ilp_image = characterunite_reset(field_get_items('node', $node, 'field_ilp_image'));
    $variables['field_ilp_image'] = (isset($ilp_image['uri'])?$ilp_image['uri']:'');
    $ilp_image_title = characterunite_reset(field_get_items('node', $node, 'field_ilp_image_title'));
    $variables['field_ilp_image_title'] = (isset($ilp_image_title['value'])?$ilp_image_title['value']:'');
    $ilp_image_description = characterunite_reset(field_get_items('node', $node, 'field_ilp_image_description'));
    $variables['field_ilp_image_description'] = (isset($ilp_image_description['value'])?$ilp_image_description['value']:'');
  }
    /** Gallery in Image landing page **/
    if(!(empty($node->field_ilp_photo_gallery_images))) {
      $field_ilp_photo_gallery_images = field_get_items('node', $node, 'field_ilp_photo_gallery_images');
      if (!empty($field_ilp_photo_gallery_images)) {
        $ilp_photo_gallery_title = characterunite_reset(field_get_items('node', $node, 'field_ilp_photo_gallery_title'));
        $variables['field_ilp_photo_gallery_title'] = (isset($ilp_photo_gallery_title['value'])?$ilp_photo_gallery_title['value']:'');

        $ilp_photo_gallery_link = characterunite_reset(field_get_items('node', $node, 'field_ilp_photo_gallery_link'));
        $variables['field_ilp_photo_gallery_link'] = (isset($ilp_photo_gallery_link['url'])?$ilp_photo_gallery_link['url']:'');
        $variables['field_ilp_photo_gallery_label'] = (isset($ilp_photo_gallery_link['title'])?$ilp_photo_gallery_link['title']:'');
        if (isset($field_ilp_photo_gallery_images)) {
          $field_ilp_photo_gallery_images_count = count($field_ilp_photo_gallery_images);
          for ($ilp_photo_gallery = 0; $ilp_photo_gallery<$field_ilp_photo_gallery_images_count; $ilp_photo_gallery++) {
            $variables['photo_gallery_images'][$ilp_photo_gallery]['ilp_photo_gallery'] = $field_ilp_photo_gallery_images[$ilp_photo_gallery]['uri'];
          }
        }
      }
    }
  /** Image Landing Section End **/
  
  /** ISSUES Variables Start ***/
  $issues_banner = characterunite_reset(field_get_items('node', $node, 'field_issues_banner'));
  $variables['field_issues_banner'] = (isset($issues_banner['uri'])?$issues_banner['uri']:'');

  $issues_banner_link = characterunite_reset(field_get_items('node', $node, 'field_issues_banner_link'));
  $variables['field_issues_banner_link'] = (isset($issues_banner_link['url'])?$issues_banner_link['url']:'');
  $variables['field_issues_banner_target'] = (isset($issues_banner_link['attributes']['target'])?$issues_banner_link['attributes']['target']:'');

  /** ISSUES Variables End ***/

  /** Biography List Start **/
  if(!(empty($node->field_biography_list_section))) {
    $bio_list = array();
    $field_biography_list_sections = field_get_items('node', $node, 'field_biography_list_section');
    if (!empty($field_biography_list_sections)) {
      $field_biography_list_section_items = array();
      foreach ($field_biography_list_sections as $field_video_section) {
        $field_biography_list_section_items[] = entity_revision_load('field_collection_item', $field_video_section['revision_id']); //load current revision of collection
      }
      $index = 0;      
      foreach ($field_biography_list_section_items as $item) {
        $field_bl_sections = field_get_items('field_collection_item', $item, 'field_bl_section');
        if (!empty($field_bl_sections)) {
          $field_bl_section_items = array();
          foreach ($field_bl_sections as $field_bl_section) {
            $field_bl_section_items[] = entity_revision_load('field_collection_item', $field_bl_section['revision_id']); //load current revision of collection
          }
          $bl_section = 0;
          $bl_category_title = characterunite_reset(field_get_items('field_collection_item', $item, 'field_bl_category_title'));
          $bio_list[$index]['field_bl_category_title'] = (isset($bl_category_title['value'])?($bl_category_title['value']):'');          
          foreach ($field_bl_section_items as $iteration_item) {
            $bl_section_title = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_bl_section_title'));
            $bio_list[$index][$bl_section]['field_bl_section_title'] = (isset($bl_section_title['value'])?$bl_section_title['value']:'');  

            $bl_section_title_2 = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_bl_section_title_2'));
            $bio_list[$index][$bl_section]['field_bl_section_title_2'] = (isset($bl_section_title_2['value'])?$bl_section_title_2['value']:'');  

            $bl_section_info = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_field_bl_section_info'));
            $bio_list[$index][$bl_section]['field_field_bl_section_info'] = (isset($bl_section_info['value'])?$bl_section_info['value']:'');  

            $bl_section_description = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_bl_section_description'));
            $bio_list[$index][$bl_section]['field_bl_section_description'] = (isset($bl_section_description['value'])?$bl_section_description['value']:'');  

            $bl_section_thumbnail = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_bl_section_thumbnail'));
            $bio_list[$index][$bl_section]['field_bl_section_thumbnail'] = (isset($bl_section_thumbnail['uri'])?($bl_section_thumbnail['uri']):'');

            $bl_section_link = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_bl_section_link'));
            $bio_list[$index][$bl_section]['field_bl_section_link_url'] = (isset($bl_section_link['url'])?($bl_section_link['url']):'');  
            $bio_list[$index][$bl_section]['field_bl_section_link_title'] = (isset($bl_section_link['title'])?($bl_section_link['title']):'');  
            $bio_list[$index][$bl_section]['field_bl_section_link_target'] = (isset($bl_section_link['attributes']['target'])?($bl_section_link['attributes']['target']):'_self');

            $bl_section++;
          }
          $index++;
        }     
      }
      if (isset($bio_list))
        $variables['biography_list'] = $bio_list;      
    }
  }
  /** Biography List End **/

  /** Video HUB Start **/
  if(!empty($node->field_video_hub_description) || !empty($node->field_video_hub_section)) {
    $video_hub_description = characterunite_reset(field_get_items('node', $node, 'field_video_hub_description'));
    $field_video_hub_description = (isset($video_hub_description['value'])?$video_hub_description['value']:'');

    if ($field_video_hub_description != '') {
      $variables['field_video_hub_description'] = $field_video_hub_description;
    }
    $video_hub = array();
    $field_video_hub_sections = field_get_items('node', $node, 'field_video_hub_section');

    if (!empty($field_video_hub_sections)) {
      $field_video_hub_sections_items = array();
      foreach ($field_video_hub_sections as $field_video_hub_section) {
        $field_video_hub_sections_items[] = entity_revision_load('field_collection_item', $field_video_hub_section['revision_id']); //load current revision of collection
      }
      $index = 0;
      foreach ($field_video_hub_sections_items as $item) {
        $hub_category = characterunite_reset(field_get_items('field_collection_item', $item, 'field_video_hub_category'));
        $field_video_hub_category = (isset($hub_category['value'])?$hub_category['value']:'');
        
        if ($field_video_hub_category != '') {
          $video_hub[$index]['field_video_hub_category'] = $field_video_hub_category;
        }
        
        $field_video_hub_iterations = field_get_items('field_collection_item', $item, 'field_video_hub_iteration');
        if (!empty($field_video_hub_iterations)) {
          $field_video_hub_iterations_items = array();
          foreach ($field_video_hub_iterations as $field_video_hub_iteration) {
            $field_video_hub_iterations_items[] = entity_revision_load('field_collection_item', $field_video_hub_iteration['revision_id']); //load current revision of collection
          }
          $iteration = 0;
          foreach ($field_video_hub_iterations_items as $iteration_item) {
            $vhi_name = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_vhi_name'));
            $video_hub[$index][$iteration]['field_vhi_name'] = (isset($vhi_name['value'])?$vhi_name['value']:'');  

            $vhi_thumbnail = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_vhi_thumbnail'));
            $video_hub[$index][$iteration]['field_vhi_thumbnail'] = (isset($vhi_thumbnail['uri'])?$vhi_thumbnail['uri']:'');

            $field_vhi = '';
            $field_vhi_info = field_get_items('field_collection_item', $iteration_item, 'field_vhi_info');
            if (isset($field_vhi_info)) {
              $field_vhi_info_count = count($field_vhi_info);
              for ($vhi_info = 0; $vhi_info < $field_vhi_info_count; $vhi_info++) {
                $field_vhi .= '<br/>'.$field_vhi_info[$vhi_info]['value'];
              }
            }
            $video_hub[$index][$iteration]['field_vhi_info'] = $field_vhi;

            $vhi_link = characterunite_reset(field_get_items('field_collection_item', $iteration_item, 'field_vhi_link'));
            if (count($vhi_link) != 0) {
              $video_hub[$index][$iteration]['field_vhi_link_url'] = (isset($vhi_link['url'])?$vhi_link['url']:'');  
              $video_hub[$index][$iteration]['field_vhi_link_label'] = (isset($vhi_link['title'])?$vhi_link['title']:'');  
              $video_hub[$index][$iteration]['field_vhi_link_target'] = (isset($vhi_link['attributes']['target'])?$vhi_link['attributes']['target']:'_self');
            }
            $iteration++;
          }
        }
        $index++;
      }
    }
    if (isset($video_hub))
      $variables['video_hub'] = $video_hub;    
  }
  /** Video HUB End **/

  /** Take Action Section Start **/
  if(!empty($node->field_issues_takeaction_section)) {

    $take_action = array();
    $field_issues_takeaction_sections = field_get_items('node', $node, 'field_issues_takeaction_section');

    if (!empty($field_issues_takeaction_sections)) {
      $field_issues_takeaction_sections_items = array();
      foreach ($field_issues_takeaction_sections as $field_issues_takeaction_section) {
        $field_issues_takeaction_sections_items[] = entity_revision_load('field_collection_item', $field_issues_takeaction_section['revision_id']); //load current revision of collection
      }
      $index = 0;
      foreach ($field_issues_takeaction_sections_items as $item) {
        $title_1 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_take_action_title_1'));
        $take_action[$index]['field_take_action_title_1'] = (isset($title_1['value'])?$title_1['value']:'');

        $title_2 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_take_action_title_2'));
        $take_action[$index]['field_take_action_title_2'] = (isset($title_2['value'])?$title_2['value']:'');

        $take_action_list = field_get_items('field_collection_item', $item, 'field_take_action_list');
        if ($take_action_list != '') {
          $take_action_list_count = count($take_action_list);
          for ($i = 0; $i < $take_action_list_count; $i++) {
            $field_take_action_list[$i]['value'] = (isset($take_action_list[$i]['value'])?$take_action_list[$i]['value']:'');
          }
          $take_action[$index]['field_take_action_list'] = $field_take_action_list;
        }
        $index++;
      }
    }
    if (isset($take_action))
      $variables['take_action'] = $take_action;    
  }
  /** Take Action Section Start **/
  
  /** Facts Section Start **/
  if(!empty($node->field_issues_facts_section)) {

    $facts = array();
    $field_issues_facts_sections = field_get_items('node', $node, 'field_issues_facts_section');

    if (!empty($field_issues_facts_sections)) {
      $field_issues_facts_sections_items = array();
      foreach ($field_issues_facts_sections as $field_issues_facts_section) {
        $field_issues_facts_sections_items[] = entity_revision_load('field_collection_item', $field_issues_facts_section['revision_id']); //load current revision of collection
      }
      $index = 0;
      foreach ($field_issues_facts_sections_items as $item) {
        $title_1 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_facts_title_1'));
        $facts[$index]['field_facts_title_1'] = (isset($title_1['value'])?$title_1['value']:'');

        $title_2 = characterunite_reset(field_get_items('field_collection_item', $item, 'field_facts_title_2'));
        $facts[$index]['field_facts_title_2'] = (isset($title_2['value'])?$title_2['value']:'');

        $facts_list = field_get_items('field_collection_item', $item, 'field_facts_list');
        if ($facts_list != '') {
          $facts_list_count = count($facts_list);
          for ($i = 0; $i < $facts_list_count; $i++) {
            $field_facts_list[$i]['value'] = (isset($facts_list[$i]['value'])?$facts_list[$i]['value']:'');
          }
          $facts[$index]['field_facts_list'] = $field_facts_list;
        }
        $index++;
      }
    }
    if (isset($facts))
      $variables['facts'] = $facts;    
  }
  /** Facts Section Start **/
  
  
}

/**
 * Implements theme_menu_tree().
 */
function characterunite_menu_tree($variables) {
  return '<ul class="sf-menu clearfix">' . $variables['tree'] . '</ul>';
}

/**
 * Ouptuts site breadcrumbs with current page title appended onto trail
 */
function characterunite_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  if (!empty($breadcrumb)) {
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';
    $crumbs = '<div class="breadcrumb">';
    $array_size = count($breadcrumb);
    $i = 0;
    while ( $i < $array_size) {
      $crumbs .= '<span class="breadcrumb-' . $i;
      if ($i == 0) {
        $crumbs .= ' first';
      }
      $crumbs .=  '">' . str_replace(".", "", $breadcrumb[$i]) . '</span>&nbsp;&gt;&nbsp;';
      $i++;
    }
    $crumbs .= '<span class="active">'. drupal_get_title() .'</span></div>';
    return $crumbs;
  }
}

/**
 * Array reset, is the argument is an array 
 */
function characterunite_reset($array) {
  if (is_array($array))
  return reset($array);
}

/**
 * Implements theme_preprocess_page().
 */
function characterunite_preprocess_page(&$variables) {
  $theme_path = drupal_get_path('theme', 'characterunite');
  $node = menu_get_object();
  if (isset($variables['node']->type) && $variables['node']->type == 'unite') {
    $variables['theme_hook_suggestions'][] = 'page__node__' . $variables['node']->type;
    drupal_add_css($theme_path . '/css/cu_unite-against-bullying.css');
    drupal_add_css($theme_path . '/css/cu_foundation.css');
    drupal_add_css($theme_path . '/css/cu_unite-against-bullying-helper.css');
    $variables['page']['field_unite_video_id'] = characterunite_reset(field_get_items('node', $node, 'field_unite_video_id'));
    $variables['page']['field_unite_video_description'] = characterunite_reset(field_get_items('node', $node, 'field_unite_video_description'));
    $variables['page']['field_unite_social_section'] = characterunite_reset(field_get_items('node', $node, 'field_unite_social_section'));
    $variables['page']['field_unite_billboard_banner'] = characterunite_reset(field_get_items('node', $node, 'field_unite_billboard_banner'));
    $variables['page']['field_unite_billboard_link'] = characterunite_reset(field_get_items('node', $node, 'field_unite_billboard_link'));
  }
}