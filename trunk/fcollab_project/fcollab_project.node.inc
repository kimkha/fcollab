<?php

/**
* Implementation of hook_load().
*/
function fcollab_project_load($node) {
  $additions = db_fetch_object(db_query('SELECT * FROM {fcollab_project} WHERE vid = %d', $node->vid));
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
  db_query("INSERT INTO {fcollab_project} (nid, vid, detail, deadline, min_cost, max_cost, pstatus)
    VALUES (%d, %d, '%s', %d, %d, %d, %d)", 
    $node->nid, $node->vid, $node->detail, $node->deadline, $node->min_cost, $node->max_cost, $node->pstatus);
}

/**
* Implementation of hook_update().
*/
function fcollab_project_update($node) {
  db_query("UPDATE {fcollab_project} SET detail = '%s', deadline = %d, min_cost = %d, max_cost = %d, pstatus = %d WHERE nid = %d AND vid = %d",
    $node->detail, $node->deadline, $node->min_cost, $node->max_cost, $node->pstatus, $node->nid, $node->vid);
}

/**
* Implementation of hook_validate().
*/
function fcollab_project_validate($node, &$form) {
  /*
  if (isset($node->end) && isset($node->start)) {
    if ($node->start > $node->end) {
      form_set_error('time', t('An event may not end before it starts.'));
    }
  }*/
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
  }

  $node = node_prepare($node, $teaser);
  $node->content['myfield'] = array(
    '#value' => theme('mymodule_myfield', $node->myfield),
    '#weight' => 1,
  );
  */
  return $node;
}


?>