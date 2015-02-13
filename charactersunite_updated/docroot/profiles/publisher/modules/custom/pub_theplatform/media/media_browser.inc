<?php
/**
 * @file
 * Publisher integration with thePlatform.
 *
 * This integration works similar to how an integration with YouTube might work.
 * Video assets from MPX are simply referenced using this integration; they are
 * not imported as entities.
 */

/**
 * Media browser plugin for thePlatform sources.
 */
class MediaBrowserThePlatform extends MediaBrowserPlugin {
  /**
   * Implements MediaBrowserPlugin::view().
   */
  public function view() {

    // If video is not allowed, then we want to prevent printing a tab.
    if (!isset($this->params['types']['video'])) {
      return array();
    }

    $viewname = variable_get('pub_theplatform_selection_view', 'theplatform_videos');

    // Add in the JS that we're going to need here.
    $path = drupal_get_path('module', 'pub_theplatform');
    $build['#attached']['js'][] = $path . '/js/pub_theplatform.media_browser.js';
    $build['#attached']['css'][] = $path . '/css/thePlatform-media-browser.css';
    $build['#settings']['theplatform_info_api'] = base_path() . 'pub_theplatform/select/';
    $build['#settings']['pub_theplatform_view_id'] = $viewname;

    // Views ajax forms do not work inside of another form - the view needs to
    // be embedded as the primary content.
    $build['#markup'] = views_embed_view($viewname);

    return $build;
  }
}

/**
 * Form to submit the video from thePlatform.
 */
function pub_theplatform_select_video($form, &$form_state, $viewname) {
  $form['view'] = array(
    '#type' => 'markup',
    '#markup' => views_page($viewname, 0),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * AJAX handler for getting a video file from the GUID.
 */
function pub_theplatform_video_data($guid) {
  $media_form_state = array(
    'values' => array(
      'embed_code' => 'theplatform://' . $guid,
    ),
  );
  media_internet_add_validate(array('#validators' => array()), $media_form_state);
  media_internet_add_submit(array('#validators' => array()), $media_form_state);

  // Catch errors if this is a bad value and just 404.
  $errors = drupal_get_messages('error');

  if (isset($media_form_state['file']) && is_object($media_form_state['file']) && count($errors) === 0) {
    drupal_json_output($media_form_state['file']);
  }
  else {
    drupal_not_found();
  }
}
