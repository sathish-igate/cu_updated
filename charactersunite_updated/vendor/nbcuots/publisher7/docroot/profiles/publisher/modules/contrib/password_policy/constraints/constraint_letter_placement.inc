<?php
/**
 * @file
 * Password policy constraint callbacks.
 */

//////////////////////////////////////////////////////////////////////////////
// Constraint API

/**
 * Description of the constraint.
 */
function password_policy_constraint_letter_placement_description() {
  return array('name' => t('Letter Placement'), 'description' => t('Password must begin and end with a letter. Put any value to enforce this policy.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_letter_placement_error($constraint) {
  return t('Password must begin and end with a letter.');
}

/**
 * Password validation.
 */
function password_policy_constraint_letter_placement_validate($password, $constraint, $account) {
  $length = drupal_strlen($password);
  if ($length > 0 && ctype_alpha($password[0]) && ctype_alpha($password[$length - 1])) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Javascript portion.
 */
function password_policy_constraint_letter_placement_js($constraint, $account) {
  $s = '';
  $s .= "  var valid=false;\n";
  $s .= "  var len=value.length;\n";
  $s .= "  if(len > 0) {\n";
  $s .= "    var first_char=value.charAt(0);\n";
  $s .= "    var last_char=value.charAt(len - 1);\n";
  $s .= "    if(first_char.toUpperCase() != first_char.toLowerCase() && last_char.toUpperCase() != last_char.toLowerCase()) {\n";
  $s .= "      valid=true;\n";
  $s .= "    }\n";
  $s .= "  }\n";
  $s .= "  if(!valid) {\n";
  $s .= "    strength=\"low\";\n";
  $s .= "    msg.push(translate.constraint_letter_placement);\n";
  $s .= "  }\n";
  return $s;
}
