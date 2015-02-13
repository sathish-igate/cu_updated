<?php

/**
 * @file
 * Env-specific settings file.
 */

/**
 * Ensure errors are never displayed on prod environment.
 */
ini_set('display_errors', 'Off');

/**
 * Environment indicator settings.
 */
$conf['environment_indicator_overwrite'] = FALSE;
$conf['environment_indicator_overwritten_name'] = 'LIVE';
$conf['environment_indicator_overwritten_color'] = '#990000';

/**
 * Pub SSO settings.
 */
// This defaults to a stage URL.
$conf['sso_password_reset'] = 'https://sso.external.nbcuni.com/nbcucentral/jsp/pwchange.jsp';
