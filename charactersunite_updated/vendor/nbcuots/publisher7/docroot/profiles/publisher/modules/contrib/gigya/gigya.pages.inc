<?php

/**
 * @file
 * Page display functions for for Gigya module.
 */

/**
 * Page callback for the user/%user/edit/gigya page.
 *
 * @see gigya_menu()
 *
 * @return
 *   Gigya connect page HTML.
 */
function gigya_connect() {
  drupal_set_title(t('Edit your Social Network connections'));
  global $user;
  if ($user->uid === arg(1)) {
    return theme('gigya_connect_display');
  }
  return t('only users can edit thire own connections');
}

/**
 * socialize-login page callback.
 *
 * @see gigya_menu()
 */
function gigya_login_ajax() {
  require_once(drupal_get_path('module', 'gigya') . '/GSSDK.php');
  ctools_include('ajax');
  ctools_include('modal');
  $parms = $_POST;
  //If the admin set a post login redirect send the user to it if no just reload the page.
  $dest =  variable_get('gigya_login_uiconfig_urlredirect', '');
  if (!empty($dest)) {
    $sucess_command = ctools_ajax_command_redirect($dest);
  }
  else {
    $sucess_command = ctools_ajax_command_reload();
  }
  //Check if the user is not logged in.
  if (!user_is_logged_in()) {
    $commands = array();
    $_SESSION['gigya_suppress_notifylogin_js'] = TRUE;
    module_load_include('inc', 'gigya');
    $secretkey = variable_get('gigya_SecretKey', '');
    if (SigUtils::validateUserSignature($parms['UID'], $parms['timestamp'], $secretkey, $parms['signature'])) {
      $gigya_user = $parms['user'];

      // Check to see if the Gigya user is a Drupal user.
      if (is_numeric($gigya_user['UID']) && $parms['isSiteUID'] === 'true' && $user = user_load($gigya_user['UID'])) {
        if (!variable_get('user_email_verification', TRUE)) {
          // We can suppress the notify login JS because the user is clearly
          // already logged into gigya.
          //$_SESSION['gigya_suppress_notifylogin_js'] = TRUE;
          // Log the user in.
          global $user;
          $user = user_load($parms['UID']);
          user_login_finalize();
          $commands[] = $sucess_command;
        }
        else {
          $commands[] = ajax_command_alert(t('You must validate your email address for this account before logging in.'));
        }
        return array('#type' => 'ajax', '#commands' => $commands);
      }
      // If the user isn't a Drupal user, try to register them if allowed.
      elseif (variable_get('user_register', 1)) {
        $form_state['values'] = array();
        $uname = $parms['user']['email'];
        $user_existes = gigya_dose_user_exist($uname);
        if ($user_existes) {
          $form_state = array(
            'title' => t('Please login to link the accounts'),
            'ajax' => TRUE,
            'email' => $parms['user']['email'],
          );
          $commands = ctools_modal_form_wrapper('gigya_link_accounts_form', $form_state);
          return array('#type' => 'ajax', '#commands' => $commands);
        }
        else {
          $form_state['values']['name'] = $uname;
        }
        $form_state['values']['mail'] = $uname;
        $form_state['values']['pass'] = user_password();
        $_SESSION['gigya_uid'] = $parms['user']['UID'];

        // Allow other modules to change this info before we create the user.
        drupal_alter('gigya_create_user', $form_state, $parms);
        drupal_form_submit('user_register_form', $form_state);

        if (form_get_errors()) {
          if (variable_get('gigya_debug', 0)) {
            $messages = drupal_get_messages('error');
            $output = print_r($messages, TRUE);
            // We were unable to register a valid new user.
            // Send the error messages to watchdog.
            watchdog('gigya', 'Unable to auto-create user account:' . $output);
          }
          //if there is an error in the registration process, return the registration form in a modal.
          $form_state = array(
            'title' => t('Please fill-in missing details'),
            'ajax' => TRUE,
            'gigya' => TRUE,
          );
          $commands = ctools_modal_form_wrapper('user_register_form', $form_state);
          return array('#type' => 'ajax', '#commands' => $commands);
        }
        // The register process is done.
        $commands[] = $sucess_command;
        return array('#type' => 'ajax', '#commands' => $commands);
      }
      else {
        $commands[] = ajax_command_alert(t('Only site administrators can create new user accounts.'));
        return array('#type' => 'ajax', '#commands' => $commands);
      }
    }
    $commands[] = ajax_command_alert(t('Gigya signature not valid.'));
    return array('#type' => 'ajax', '#commands' => $commands);
  }
  $commands[] = $sucess_command;
  return array('#type' => 'ajax', '#commands' => $commands);
}

function gigya_raas_login_ajax() {
  if (!empty($_POST)) {
    ctools_include('ajax');
    ctools_include('modal');
    $sucess_command = ctools_ajax_command_reload();
    require_once(drupal_get_path('module', 'gigya') . '/GSSDK.php');
    $parms = $_POST;
    if (!user_is_logged_in()) {
      $commands = array();
      $_SESSION['gigya_suppress_notifylogin_js'] = TRUE;
      module_load_include('inc', 'gigya');
      // Make sure the request came from Gigya
      $secretkey = variable_get('gigya_SecretKey', '');
      if (SigUtils::validateUserSignature($parms['UID'], $parms['signatureTimestamp'], $secretkey, $parms['UIDSignature'])) {
        $email = $parms['profile']['email'];
        if (empty($email)) {
          $commands[] = ajax_command_alert(t('Email address is required by Drupal and is missing, please contact the site administrator.'));
          return array('#type' => 'ajax', '#commands' => $commands);
        }
        global $user;
        $user_exist = gigya_dose_user_exist($email);
        if ($user_exist) {
          $req_params = array(
            'UID' => $parms['UID'],
            'include' => 'loginIDs'
          );
          $res = _gigya_api('accounts.getAccountInfo', $req_params);
          if (gigya_is_raas_primary_user($res, $email)) {
            $user = user_load_by_mail($email);
            global $raas_login;
            $raas_login = TRUE;
            $_SESSION['gigya_raas_uid'] = $parms['UID'];
            user_login_finalize();
          } else {
            // If this user is not the primary user account in gigya we delete the account (we don't want two different users with the same email)
            _gigya_api('accounts.deleteAccount',array('UID' => $parms['UID']));
            // Get info about the primary account.
            $query = 'select loginProvider from accounts where loginIDs.emails = ' . $email;
            $search_res = _gigya_api('accounts.search', array('query' => $query));
            $p_provider = $search_res['results'][0]['loginProvider'];
            $sec_provider = $res['loginProvider'];
            $msg = t('We found your email in our system.<br />Please login to your existing account using your <b>@p_provider</b> identity.<br />
            If you wish to link your account with your <b>@sec_provider</b> identity - after logging-in, please go to your profile page and click the <b>@sec_provider</b> button.', array('@p_provider' => $p_provider, '@sec_provider' => $sec_provider));
            $commands[] = ctools_modal_command_display('Email all ready exists in system', '<div class="gigya-error">' . $msg . '</div>');
            return array('#type' => 'ajax', '#commands' => $commands);
          }
        }
        else {
          $new_user = array(
            'name' => $email,
            'pass' => user_password(),
            'mail' => $email,
            'status' => 1,
            'init' => $email,
          );
          // Allow other modules to modify the data before user is created in drupal database
          drupal_alter('gigya_raas_create_user',$new_user, $parms);
          $user = user_save(NULL, $new_user);
          $_SESSION['gigya_raas_uid'] = $parms['UID'];
          user_login_finalize();
        }
        if ($user !== FALSE) {
          $commands[] = $sucess_command;
          return array('#type' => 'ajax', '#commands' => $commands);
        }
        else {
          watchdog('gigya-RaaS', 'There was a problem registering a user');
          // TODO: handle this error
        }
      }
    }
  }
}


/**
 * Get the user friends list from Gigya.
 *
 * @param $account
 *   The user object.
 *
 * @return
 *   HTML for friends list.
 */
function gigya_get_friends($account) {
  $title = isset($account->title) ? $account->title : $account->name;
  drupal_set_title(check_plain($title));

  module_load_include('inc', 'gigya');
  $site_friends = array();
  $this_gigya_user = new GigyaUser($account->uid);
  if ($friends = $this_gigya_user->getFriends(array('siteUsersOnly' => TRUE))) {
    if (!empty($friends['friends'])) {
      foreach ($friends['friends'] as $friend) {
        if ($friend['isSiteUser'])
          $site_friends[] = $friend;
      }
    }
  }
  return theme('gigya_friends', array('friends' => $site_friends));
}

/**
 * Wrapper for the Gigya Javascript userInfo function.
 *
 * Injects the Gigya getUserInfo Javascript function.
 *
 * @param $account
 *   The user object.
 *
 * @return
 *   The user info from Gigya.
 */
function gigya_get_user($account) {
  $title = isset($account->title) ? $account->title : $account->name;
  drupal_set_title(check_plain($title));

  // Add the onload functions .
  $behavior_js = 'Drupal.behaviors.gigyaGetUserInfo = { attach: function(context, settings) { gigya.services.socialize.getUserInfo(Drupal.settings.gigya.conf, {callback:Drupal.gigya.getUserInfoCallback}); }}';
  drupal_add_js($behavior_js, array('type' => 'inline', 'scope' => JS_DEFAULT));

  $userinfo = '<div id="userinfo"></div>';
  return $userinfo;
}


function gigya_register_ajax($form, $form_state) {
  ctools_include('ajax');
  ctools_include('modal');
  ctools_add_js('ajax-responder');
  drupal_process_form('user_register_form', $form, $form_state);
  $commands[] = ctools_modal_command_dismiss();
  $dest =  variable_get('gigya_login_uiconfig_urlredirect', '');
  if (!empty($dest)) {
    $commands[] = ctools_ajax_command_redirect($dest);
  }
  else {
    $commands[] = ctools_ajax_command_reload();
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}
