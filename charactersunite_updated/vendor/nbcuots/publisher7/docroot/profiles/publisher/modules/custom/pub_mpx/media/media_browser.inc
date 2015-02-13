<?php


/**
 * Media browser plugin for thePlatform sources.
 */
class MediaBrowserPubMPXVideo extends MediaBrowserPlugin {

  /**
   * Implements MediaBrowserPlugin::view().
   */
  public function view() {

    //  If video is not allowed, then we want to prevent printing a tab.
    $display_tab = FALSE;
    foreach ($this->params['types'] as $type) {
      if (strpos($type, 'mpx_video') === 0) {
        $display_tab = TRUE;
      }
    }
    if (!$display_tab) {
      return array();
    }

    // TODO: Create admin form to change this.
    $viewname = variable_get('pub_mpx_video_media_browser_view_name', 'pub_mpx_video_media_browser');

    //  Add in the JS that we're going to need here.
    $path = drupal_get_path('module', 'pub_mpx');

    $build = array();
    $build['#attached']['js'][] = $path . '/js/pub_mpx.video_media_browser.js';
    $build['#attached']['css'][] = $path . '/css/pub_mpx.video_media_browser.css';
    $build['#settings']['view_name'] = $viewname;

    // Views ajax forms do not work inside of another form - the view needs to be
    // embedded as the primary content.
    $build['#markup'] = views_embed_view($viewname);

    return $build;
  }
}
