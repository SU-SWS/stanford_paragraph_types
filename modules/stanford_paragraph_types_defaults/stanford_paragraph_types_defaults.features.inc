<?php

/**
 * @file
 * stanford_paragraph_types_defaults.features.inc
 */

/**
 * Implements hook_features_export_options().
 */
function paragraph_defaults_features_export_options() {
  return db_select('stanford_paragraphs_defaults', 's')
    ->fields('s', array('pid', 'label'))
    ->execute()->fetchAllKeyed();
}

/**
 * Implements hook_features_export().
 */
function paragraph_defaults_features_export($data, &$export, $module_name) {
  $export['dependencies']['stanford_paragraph_types_defaults'] = 'stanford_paragraph_types_defaults';
  $query = db_select('stanford_paragraphs_defaults', 's')
    ->fields('s')
    ->condition('pid', $data, 'IN')
    ->execute();

  while ($default = $query->fetchAssoc()) {
    $id = "{$default['entity_type']}-{$default['bundle']}-{$default['machine_name']}";
    $export['features']['paragraph_defaults'][$id] = $id;
  }

  return array();
}

/**
 * Implements hook_features_export_render().
 */
function paragraph_defaults_features_export_render($module_name, $data, $export = NULL) {

  $code = array();
  $code[] = '  $paragraph_defaults = array();';
  foreach ($data as $item) {
    list($type, $bundle, $machine_name) = explode('-', $item);

    $defaults = stanford_ptd_load_default_paragraphs($type, $bundle, $machine_name);
    $items = array(
      '#type' => $type,
      '#bundle' => $bundle,
      '#machine_name' => $machine_name,
    );

    foreach ($defaults as $default) {
      $object = new stdClass();
      foreach ($default as $prop => $value) {
        $object->{$prop} = $value;
      }
      unset($object->item_id, $object->revision_id, $object->default_revision, $object->archived);
      $items['paragraphs'][] = $object;
    }

    $code[] = "  \$paragraph_defaults['{$item}'] = " . features_var_export($items) . ";";
    $code[] = '';
  }

  $code[] = "return \$paragraph_defaults;";
  $code = implode("\n", $code);
  return array('paragraph_defaults' => $code);
}

/**
 * Implements hook_features_rebuild().
 */
function paragraph_defaults_features_rebuild($module_name) {
  $paragraph_defaults = module_invoke($module_name, 'paragraph_defaults');
  if (!empty($paragraph_defaults)) {
    foreach ($paragraph_defaults as $paragraph_default) {
      paragraph_defaults_save($paragraph_default);
    }
  }
}

/**
 * Implements hook_features_revert().
 */
function paragraph_defaults_features_revert($module_name) {
  $paragraph_defaults = module_invoke($module_name, 'paragraph_defaults');
  if (!empty($paragraph_defaults)) {
    foreach ($paragraph_defaults as $paragraph_default) {
      paragraph_defaults_save($paragraph_default);
    }
  }
}

function paragraph_defaults_save($default) {
  $existing_defaults = stanford_ptd_load_default_paragraphs($default['#type'], $default['#bundle'], $default['#machine_name']);
  foreach ($existing_defaults as $paragraph_item) {
    dpm($paragraph_item);
//    entity_delete('paragraphs_item', $paragraph_item);
  }
}
