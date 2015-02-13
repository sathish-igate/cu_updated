<?php

/*
 * @file pub_mpx_views_handler_field_account.inc
 */

/*
 * Field handler to provide a renderer for the MPX video account.
 */
class pub_mpx_handler_field_account extends views_handler_field {

  function render($values) {
  	
    if (!empty($values->mpx_video_account)) {
      return rawurldecode($values->mpx_video_account);
    }
    return NULL;
  }
}
