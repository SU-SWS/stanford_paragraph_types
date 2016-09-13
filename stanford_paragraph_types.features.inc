<?php
/**
 * @file
 * stanford_paragraph_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function stanford_paragraph_types_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_paragraphs_info().
 */
function stanford_paragraph_types_paragraphs_info() {
  $items = array(
    'stanford_block' => array(
      'name' => 'Block',
      'bundle' => 'stanford_block',
      'locked' => '1',
    ),
    'stanford_gallery' => array(
      'name' => 'Gallery',
      'bundle' => 'stanford_gallery',
      'locked' => '1',
    ),
    'stanford_image' => array(
      'name' => 'Image',
      'bundle' => 'stanford_image',
      'locked' => '1',
    ),
    'stanford_pull_quote' => array(
      'name' => 'Pull Quote',
      'bundle' => 'stanford_pull_quote',
      'locked' => '1',
    ),
    'stanford_table_data' => array(
      'name' => 'Table Data',
      'bundle' => 'stanford_table_data',
      'locked' => '1',
    ),
    'stanford_video' => array(
      'name' => 'Video',
      'bundle' => 'stanford_video',
      'locked' => '1',
    ),
    'stanford_wysiwyg' => array(
      'name' => 'WYSIWYG',
      'bundle' => 'stanford_wysiwyg',
      'locked' => '1',
    ),
  );
  return $items;
}
