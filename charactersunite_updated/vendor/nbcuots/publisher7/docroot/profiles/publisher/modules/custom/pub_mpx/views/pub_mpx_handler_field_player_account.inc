<?php

/**
 * @file pub_mpx_handler_field_player_account.inc
 */

/*
 * Field handler to provide a renderer for the MPX player account.
 */
class pub_mpx_handler_field_player_account extends views_handler_field {

  function render($values) {
    if (!empty($values->mpx_player_account)) {
      return rawurldecode($values->mpx_player_account);
    }
    return NULL;
  }
}
