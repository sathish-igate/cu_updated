<?php
/**
 * @file
 * pub_promo_queue.features.inc
 */

/**
 * Implements hook_default_queues_type().
 */
function pub_promo_queue_default_queues_type() {
  $items = array();
  $items['promo_queue'] = entity_import('queues_type', '{
    "label" : "Promo Queue",
    "type" : "promo_queue",
    "target" : "node",
    "settings" : { "entityreference_field" : {
        "cardinality" : "-1",
        "target_bundles" : {
          "character_profile" : 0,
          "media_gallery" : 0,
          "movie" : 0,
          "person" : 0,
          "post" : 0,
          "tv_episode" : 0,
          "tv_season" : 0,
          "tv_show" : 0
        }
      }
    }
  }');
  return $items;
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function pub_promo_queue_form_state_flow_entity_events_revision_alter(&$form, &$form_state, $form_id) {
  if (isset($form['event']['#title'])) {
    $form['event']['#title'] = t('Change State');
  }
  if (isset($form['event_comment']['#required'])) {
    $form['event_comment']['#required'] = FALSE;
  }
}

/**
 * Implements hook_entity_revision_operation_info_alter().
 */
function pub_promo_queue_entity_revision_operation_info_alter(&$operations) {
  unset($operations['queues']['delete']);
}
