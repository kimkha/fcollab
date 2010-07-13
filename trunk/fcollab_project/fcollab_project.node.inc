<?php

/**
* Implementation of hook_load().
*/
function fcollab_project_load($node) {
  $additions = db_fetch_object(db_query('SELECT * FROM {fcollab_project} WHERE vid = %d', $node->vid));
  $additions->deadline = array(
		'year' => date('Y', $additions->deadline),
		'month' => date('n', $additions->deadline),
		'day' => date('j', $additions->deadline),
	);
  return $additions;
}

/**
* Implementation of hook_delete().
*/
function fcollab_project_delete(&$node) {
  db_query('DELETE FROM {fcollab_project} WHERE nid = %d', $node->nid);
}

/**
* Implementation of hook_insert().
*/
function fcollab_project_insert($node) {
	$d = $node->deadline;
	$deadline = mktime(0,0,0,$d['month'],$d['day'], $d['year']);
  db_query("INSERT INTO {fcollab_project} (nid, vid, detail, deadline, min_cost, max_cost, pstatus)
    VALUES (%d, %d, '%s', %d, %d, %d, %d)", 
    $node->nid, $node->vid, $node->detail, $deadline, $node->min_cost, $node->max_cost, $node->pstatus);
}

/**
* Implementation of hook_update().
*/
function fcollab_project_update($node) {
	$d = $node->deadline;
	$deadline = mktime(0, 0, 0, $d['month'], $d['day'], $d['year']);
  db_query("UPDATE {fcollab_project} SET detail = '%s', deadline = %d, min_cost = %d, max_cost = %d, pstatus = %d WHERE nid = %d AND vid = %d",
    $node->detail, $deadline, $node->min_cost, $node->max_cost, $node->pstatus, $node->nid, $node->vid);
}

/**
* Implementation of hook_validate().
*/
function fcollab_project_validate($node, &$form) {
  if (strlen($node->body) > 300) {
  	form_set_error('body', t('Brief description must be less than 300 characters.'));
  }
  
  $check_cost = true;
  if (!is_numeric($node->min_cost)) {
  	form_set_error('min_cost', t('Minimum cost must be a number.'));
  	$check_cost = false;
  } else if ($node->min_cost < 0) {
		form_set_error('min_cost', t('Minimum cost must be greater than 0.'));
  	$check_cost = false;
	}
  if (!is_numeric($node->max_cost)) {
  	form_set_error('max_cost', t('Maximum cost must be a number.'));
  	
  } else if ($node->min_cost < 0) {
		form_set_error('max_cost', t('Maximum cost must be greater than 0.'));
	} else if ($check_cost && $node->min_cost > $node->max_cost) {
		form_set_error('max_cost', t('Maximum cost must be greater than minimum cost.'));
		form_set_error('min_cost', t('Maximum cost must be greater than minimum cost.'));
		array_pop($_SESSION['messages']['error']);
	}
}

/**
* Implementation of hook_view().
*/
function fcollab_project_view($node, $teaser = FALSE, $page = FALSE) {
  /*
  if ($page) {
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb[] = l(t('Example'), 'example');
    $breadcrumb[] = l($node->field1, 'example/' . $node->field1);
    drupal_set_breadcrumb($breadcrumb);
  }/**/

  $node = node_prepare($node, $teaser);
  $node->content['cost'] = array(
    '#value' => theme('fcollab_project_cost_info', $node),
    '#weight' => 1,
  );
  /**/
  //print_r($node);
  return $node;
}

/**
* Implementation of hook_form().
*/
function fcollab_project_form(&$node, $form_state) {
  $type = node_get_types('type', $node);
  
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => check_plain($type->title_label),
    '#description' => check_plain(t('Choose short title for your project')),
    '#required' => TRUE,
    '#default_value' => $node->title,
    '#weight' => -5
  );
  
  $form['body_filter']['body'] = array(
    '#type' => 'textarea',
    '#title' => check_plain($type->body_label),
    '#description' => t('Brief description is displayed in the list page. Limit: !char_left characters is left.', array('!char_left' => '<span id="fcollab_word_count">300</span>')),
    '#default_value' => $node->body,
    '#required' => TRUE,
    '#attributes' => array(
			'onKeyup' => '$("#fcollab_word_count").text(300-$(this).val().length);'
		),
  );
  $form['body_filter']['detail'] = array(
    '#type' => 'textarea',
    '#title' => t('Detail description'),
    '#default_value' => $node->detail,
    '#required' => TRUE
  );
  $form['body_filter']['filter'] = filter_form($node->format);
  
  $form['deadline'] = array(
    '#type' => 'date',
    '#title' => t('Deadline'),
    '#default_value' => $node->deadline,
    '#weight' => 1
  );
  $form['cost'] = array(
    '#weight' => 2
	);
  $form['cost']['min_cost'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum Cost'),
    '#description' => t('The cost which freelancers bid must be greater than.'),
    '#default_value' => $node->min_cost,
  );
  $form['cost']['max_cost'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum Cost'),
    '#description' => t('The cost which freelancers bid must be less than. 0 is unlimited'),
    '#default_value' => $node->max_cost,
  );
  
  return $form;
}


function theme_fcollab_project_cost_info($node) {
	$output = '<div class="fcollab_project_cost">';
	$output .= '<b>'.t('Minimum Cost').'</b>: '.$node->min_cost.'<br />';
	$output .= '<b>'.t('Maximum Cost').'</b>: '.$node->max_cost.'<br />';
	$output .= '</div>';
	return $output;
}

?>