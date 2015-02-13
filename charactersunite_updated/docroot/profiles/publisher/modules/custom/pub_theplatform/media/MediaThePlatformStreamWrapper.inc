<?php
/**
 * @file
 * Media stream wrapper for thePlatform.
 */


/**
 *  Create an instance like this:
 *  $mpxvideo = new ResourceThePlatformStreamWrapper('theplatform://[guid]');
 */
class MediaThePlatformStreamWrapper extends MediaReadOnlyStreamWrapper {
  // @todo: Make this work for sites other than syfy.
  protected $base_url = 'http://www.syfy.com/videos/Homepage/vid:';

  // The vid of the current asset.
  public $vid = NULL;

  /**
   * Get the VID from the provided URI.
   *
   * @param string $uri
   *   The URI of the video asset.
   *
   * @return int
   *   The ID of the asset.
   */
  public function getVid($uri) {
    preg_match('/([\d]+)/', $uri, $id);
    return (int) ($id[0]);
  }

  /**
   * This is a stub of getVid(). It is here simply for backwards compatibility.
   *
   * @param string $uri
   *   The URI of the video asset.
   *
   * @return int
   *   The ID of the asset.
   */
  public function get_vid($uri) {
    return $this->getVid($uri);
  }

  /**
   * {@inheritdoc}
   */
  public function setUri($uri) {
    $this->uri = $uri;
    $this->vid = $this->getVid($uri);
  }

  /**
   * {@inheritdoc}
   */
  public function getExternalUrl() {
    return $this->base_url . $this->vid;
  }

  /**
   * This does nothing. DO NOT USE.
   *
   * @todo: Remove this. It doesn't appear to be used anywhere and that it was
   * copied in from the Youtube StreamWrapper. But just in case I'm leaving it.
   *
   * @param mixed $f
   *   This parameter is useless.
   *
   * @return bool
   *   Always returns FALSE.
   */
  public function getTarget($f) {
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public static function getMimeType($uri, $mapping = NULL) {
    return 'video/theplatform';
  }

  /**
   * Gets the path to the video asset's thumbnail on MPX.
   *
   * @return mixed
   *   The thumbnail path or NULL.
   *
   * @throws Exception
   */
  public function getOriginalThumbnailPath() {
    $req = new thePlatformAPIRequest(variable_get('theplatform_feed_url', ''));
    $resp = $req->setID($this->vid)
      ->addField('plmedia$defaultThumbnailUrl')
      ->execute();

    if (is_array($resp) && count($resp) > 0 && isset($resp[0]->{'plmedia$defaultThumbnailUrl'})) {
      // Sometimes MPX will send us invalid URLs like:
      // "{ssl:https:http}://mpxstatic-nbcmpx.nbcuni.com/...jpg". We need to
      // fix the protocol for the ingestion to work. When the root cause is
      // fixed this code may go away.
      $thumbnail_url = $resp[0]->{'plmedia$defaultThumbnailUrl'};
      $thumbnail_url = preg_replace('/(\{.*\})\:\/\/(.*)/', "http://$2", $thumbnail_url);

      return $thumbnail_url;
    }
  }

  /**
   * Gets the local path to the video asset's thumbnail.
   *
   * @return string
   *   The local path to the video asset's thumbnail.
   */
  public function getLocalThumbnailPath() {
    $thumbnail_url = $this->getOriginalThumbnailPath();
    $filename = substr($thumbnail_url, strrpos($thumbnail_url, '/') + 1);
    $local_path = 'public://pub_theplatform/' . $filename;
    if (!file_exists($local_path)) {
      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
      $response = drupal_http_request($thumbnail_url);
      file_save_data($response->data, $local_path, TRUE);
    }
    return $local_path;
  }
}
