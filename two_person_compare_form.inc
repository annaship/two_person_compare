<?php

//require_once('two_person_compare_form_submit.inc');

function two_person_compare_form($form_state) {
  $form = array();
  $person_nids  = variable_get('person_checked', '');
//  $person_nids = array(17572, 17495);
//  dpm($person_nids);
////  $new_person_node = _get_new_person_node($new_person_nid);
//  $old_person_nids = person_checked('old_person_nids', '');
//  $new_last_name   = $new_person_node['last_name'];
////  $old_person_nids = ($new_last_name);
//
////  $nodes = $new_person_node;
//  $nodes = _two_person_compare_items($person_nids);
//  dpm($nodes);
//  $new_a = array();
//  $new_a[] = node_load($new_person_nid);
//  $old_a = _two_person_compare_items($old_person_nids);
//
//  $nodes = array_merge($new_a, $old_a);

//  $nodes = _two_person_compare_items($old_person_nids);

  $form['container'] = array(
    '#type' => 'markup',
    '#value' => '',
    '#theme' => 'two_person_compare_form_table',
  );

  if (!empty ($person_nids)) {
    foreach($person_nids as $nid) {
      $form['container']['node_' . $nid] = array(
        '#type' => 'checkbox',
        '#title' => NULL,
        '#size' => 4,
        '#default_value' => 0,
      );
    }
  }

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit'),
    );

  return $form;
}

//function two_person_compare_form_validate($form, &$form_state) {
//  foreach($form_state['values'] as $field_name => $value) {
//    if(strpos($field_name, 'node_') === 0) {
//      if(!is_numeric($value) || intval($value) < 0) {
//        form_set_error($field_name, t('Value must be a non-negative integer.'));
//      }
//    }
//  }
//}

function two_person_compare_form_submit($form, &$form_state) {
  drupal_set_message(t('The form 2 has been submitted.'));

}

function two_person_compare_theme($existing, $type, $theme, $path) {
  return array(
    'two_person_compare_form_table' => array(
      'arguments' => array('fieldset' => NULL),
    )
  );
}


function theme_two_person_compare_form_table($container) {

  // Define header row for the table
//  $header = array('1','2');
  array(
      t(''),
      t('First Person'),
      t('Second Person'),
      );

  $rows = array();
//  $rows = array('a','b');

  $transformed_container = _regroup_two_person_data($container);
  
  foreach($container as $field_name => $field) {
    // All the fields were named 'node_' . $node->nid
    if (strpos($field_name, 'node_') === 0) {

      $nid  = substr($field_name, 5);
      $node = node_load($nid);

//      $rows = array(
//
//      );
      $rows[] = array(
        $node->nid,
        check_plain($node->field_person_first_name[0]['value']),
        check_plain($node->field_person_last_name[0]['value']),
        check_plain($node->field_person_email[0]['email']),
        drupal_render($field),
      );

    }
  }

  return theme_table($header, $rows);
}


function _regroup_two_person_data($container) {
  $comparison = array();
  if (!empty ($container)) {
    foreach($container as $field_name => $field) {
      if (strpos($field_name, 'node_') === 0) {
        $nid  = substr($field_name, 5);
        $node = node_load($nid);
        $comparison['first_name'][]  	= $node->field_person_first_name[0]['value'];
        $comparison['last_name'][]  	= $node->field_person_last_name[0]['value'];
        $comparison['organization'][] = $node->field_person_organization[0]['value'];
        $comparison['title'][]  			= $node->field_person_title[0]['value'];
        $comparison['address'][]  		= $node->field_person_address[0]['value'];
        $comparison['city'][]         = $node->field_person_city[0]['value'];
        $comparison['state'][]  			= $node->field_person_state[0]['value'];
        $comparison['zipcode'][]  		= $node->field_person_zipcode[0]['value'];
        $comparison['country'][]  		= $node->field_person_country[0]['value'];
        $comparison['phone'][]  			= $node->field_person_phone[0]['value'];
        $comparison['fax'][]          = $node->field_person_fax[0]['value'];
        $comparison['email'][]  			= $node->field_person_email[0]['email'];
        $comparison['personid'][]  		= $node->field_person_personid[0]['value'];
        $comparison['role'][]         = $node->field_person_role[0]['value'];
        $comparison['uid'][]          = $node->field_person_uid[0]['uid'];
      }
    }
  }
  dpm($comparison);
  return($comparison);
}

//function two_person_compare_form_submit($form, &$form_state) {
//  drupal_set_message(t('The form has been submitted.'));
//}

function _get_new_person_node($new_person_nid) {
  $new_person = array();
  $node       = node_load($new_person_nid);
  $new_person['first_name']		= $node->field_person_first_name[0]['value'];
  $new_person['last_name']		= $node->field_person_last_name[0]['value'];
  $new_person['organization']	= $node->field_person_organization[0]['value'];
  $new_person['title']				= $node->field_person_title[0]['value'];
  $new_person['address']			= $node->field_person_address[0]['value'];
  $new_person['city']         = $node->field_person_city[0]['value'];
  $new_person['state']				= $node->field_person_state[0]['value'];
  $new_person['zipcode']			= $node->field_person_zipcode[0]['value'];
  $new_person['country']			= $node->field_person_country[0]['value'];
  $new_person['phone']				= $node->field_person_phone[0]['value'];
  $new_person['fax']          = $node->field_person_fax[0]['value'];
  $new_person['email']				= $node->field_person_email[0]['email'];
  $new_person['personid']			= $node->field_person_personid[0]['value'];
  $new_person['role']         = $node->field_person_role[0]['value'];
  $new_person['uid']          = $node->field_person_uid[0]['uid'];
  return $new_person;
}


function _two_person_compare_items($person_nids) {
  $res = array();
  if (!empty($person_nids)) {
    foreach ($person_nids as $value) {
      $res[] = node_load($value);
    }
  }

  if (count($res) == 0) {
    drupal_set_message(t("Couldn't find any nodes!"), 'warning');
  }
  return $res;
}