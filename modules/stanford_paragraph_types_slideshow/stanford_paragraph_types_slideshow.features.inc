<?php
/**
 * @file
 * stanford_paragraph_types_slideshow.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function stanford_paragraph_types_slideshow_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_paragraphs_info().
 */
function stanford_paragraph_types_slideshow_paragraphs_info() {
  $items = array(
    'p_slideshow' => array(
      'name' => 'Slideshow',
      'bundle' => 'p_slideshow',
      'locked' => '1',
    ),
  );
  return $items;
}
