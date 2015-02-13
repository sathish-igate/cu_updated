<?php
/**
 * @file
 * feature_pub_mpx_file_types.file_type.inc
 */

/**
 * Implements hook_file_default_types().
 */
function feature_pub_mpx_file_types_file_default_types() {
  $export = array();

  $file_type = new stdClass();
  $file_type->disabled = FALSE; /* Edit this to true to make a default file_type disabled initially */
  $file_type->api_version = 1;
  $file_type->type = 'mpx_player';
  $file_type->label = 'MPX Player';
  $file_type->description = 'Players ingested from thePlatform.';
  $file_type->mimetypes = array(
    0 => 'player/mpx',
  );
  $export['mpx_player'] = $file_type;

  $file_type = new stdClass();
  $file_type->disabled = FALSE; /* Edit this to true to make a default file_type disabled initially */
  $file_type->api_version = 1;
  $file_type->type = 'mpx_video';
  $file_type->label = 'MPX Video';
  $file_type->description = 'Videos ingested from thePlatform.';
  $file_type->mimetypes = array(
    0 => 'video/mpx',
  );
  $export['mpx_video'] = $file_type;

  return $export;
}
