<?php
/**
 * @file
 * Media internet handler for thePlatform.
 */

/**
 * Class MediaInternetThePlatformHandler.
 */
class MediaInternetThePlatformHandler extends MediaInternetBaseHandler {
  /**
   * Parse the given embed code.
   *
   * @param string $embed_code
   *   Embed code to parse.
   *
   * @return string
   *   The URI for the given video asset.
   */
  public function parse($embed_code) {
    // Extract the asset ID and grab the first one.
    preg_match('/([\d]+)/', $embed_code, $id);
    $id = (int) ($id[0]);

    return file_stream_wrapper_uri_normalize('theplatform://' . $id);
  }

  /**
   * {@inheritdoc}
   */
  public function claim($embed_code) {
    // Extract the ID.
    preg_match('/theplatform\:\/+([\d]+)/', $embed_code, $id);
    if (empty($id)) {
      return FALSE;
    }
    $id = $id[1];

    // Make sure the video exists.
    $req = new pubThePlatformAPIRequest(variable_get('theplatform_feed_url', ''));
    $resp = $req->setID($id)
      ->addField('guid')
      ->execute();
    $valid = (isset($resp[0]->guid) && $resp[0]->guid == $id);

    // Throw an error that tells them that we aren't willing to handle this
    // because of a validation error, but would otherwise.
    if (!$valid) {
      watchdog('thePlatform', 'thePlatform does not have a video with the GUID: %guid', array('%guid' => $resp[0]->guid));
      return FALSE;
    }

    return $id;
  }

  /**
   * {@inheritdoc}
   */
  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    $file = file_uri_to_object($uri, TRUE);

    if (empty($file->fid) && $title = $this->getPlatformTitle()) {
      $file->filename = truncate_utf8($title, 255);
    }

    return $file;
  }

  /**
   * Gets the title of the current asset.
   *
   * @return string
   *   The title of the video asset.
   */
  private function getPlatformTitle() {
    $req = new pubThePlatformAPIRequest(variable_get('theplatform_feed_url', ''));

    // Extract the ID and grab the first one.
    preg_match('/([\d]+)/', $this->embedCode, $id);
    $id = (int) ($id[0]);

    $resp = $req->setID($id)
      ->addField('title')
      ->execute();

    if (is_array($resp) && count($resp) > 0 && isset($resp[0]->title)) {
      return $resp[0]->title;
    }
    return '<Video Not Found>';
  }
}
