<?php

function theme_fcollab_project_view_bid($bid) {
	$output = '<div class="fcollab_project_bid">';
	$output .= '</div>';
	return $output;
}

/**
 * Load bid by bid ID
 */
function fcollab_project_bid_load($id) {
	$info = db_fetch_object(db_query('SELECT * FROM {fcollab_project_bid} WHERE id = %d', $id));
	return $info;
}

function fcollab_project_bid_insert($bid) {
	if ($bid->created == '') $bid->created = mktime();
	db_query("INSERT INTO {fcollab_project_bid} (nid, uid, body, time, cost, created, status)
    VALUES (%d, %d, '%s', %d, %d, %d, %d)", 
    $bid->nid, $bid->uid, $bid->body, $bid->time, $bid->cost, $bid->created, $bid->status);
}

function fcollab_project_bid_update($bid) {
	db_query("UPDATE {fcollab_project_bid} SET body = '%s', time = %d, status = %d WHERE id = %d",
    $bid->body, $bid->time, $bid->status, $bid->id);
}

function fcollab_project_bid_validate($id) {
	// TODO: Something
}

function fcollab_project_bid_delete($bid) {
	db_query('DELETE FROM {fcollab_project_bid} WHERE id = %d', $bid->id);
}

function fcollab_project_bid_view($bid) {
	// TODO: Something
	return $bid;
}

?>