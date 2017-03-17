<?php

/**
 * @file
 * stanford_paragraph_types_defaults.features.inc
 */

/**
 * Implements hook_features_export_options().
 */
function paragraph_defaults_features_export_options() {
  $defaults = stanford_paragraphs_defaults_load_multiple();
  $items = array();
  foreach ($defaults as $uid => $default) {
    $items[$uid] = $default['label'];
  }
  return $items;
}

/**
 * Implements hook_features_export().
 */
function paragraph_defaults_features_export($data, &$export, $module_name) {
  $export['dependencies']['stanford_paragraph_types_defaults'] = 'stanford_paragraph_types_defaults';
  foreach ($data as $uid) {
    $export['features']['paragraph_defaults'][$uid] = $uid;
  }
  return array();
}

/**
 * Implements hook_features_export_render().
 */
function paragraph_defaults_features_export_render($module_name, $data, $export = NULL) {
  $defaults = stanford_paragraphs_defaults_load_multiple($data);
  $code = array('  $paragraph_defaults = array();');

  foreach ($defaults as $uid => $item) {
    unset($item['uid'], $item['item_ids']);

    foreach ($item['paragraphs'] as &$paragraph_item) {
      unset($paragraph_item->item_id, $paragraph_item->revision_id);
      unset($paragraph_item->default_revision, $paragraph_item->archived);

      $new_object = new stdClass();
      foreach ($paragraph_item as $property => $value) {
        if (!empty($value)) {
          $new_object->{$property} = $value;
        }
      }
      $paragraph_item = $new_object;
    }
    $item['paragraphs'] = array_values($item['paragraphs']);

    $code[] = "  \$paragraph_defaults['{$uid}'] = " . features_var_export($item, '  ') . ";";
    $code[] = '';
  }

  $code[] = '  return $paragraph_defaults;';
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
  // Clear out old default configuration.
  $uid = "{$default['entity_type']}-{$default['bundle']}-{$default['field_name']}-{$default['machine_name']}";

  if ($original_default = stanford_paragraphs_defaults_load($uid)) {
    $item_ids = array();
    foreach ($original_default['paragraphs'] as $paragraph_item) {
      $item_ids[] = $paragraph_item->item_id;
    }
    entity_delete_multiple('paragraphs_item', $item_ids);
  }

  $item_ids = array();
  foreach ($default['paragraphs'] as $weight => $item) {
    $paragraph = new ParagraphsItemEntity(array(
      'field_name' => $item['field_name'],
      'bundle' => $item['bundle'],
    ));
    $paragraph->is_new = TRUE;

    $fields = field_info_instances('paragraphs_item', $item['bundle']);
    foreach (array_keys($fields) as $field_name) {
      if (isset($item[$field_name])) {
        $paragraph->{$field_name} = $item[$field_name];
      }
    }
    $paragraph->save(TRUE);
    $item_ids[$paragraph->item_id] = $weight;
  }

  db_merge('stanford_paragraphs_defaults')
    ->insertFields(array(
      'label' => $default['label'],
      'machine_name' => $default['machine_name'],
      'entity_type' => $default['entity_type'],
      'field_name' => $default['field_name'],
      'bundle' => $default['bundle'],
      'item_ids' => serialize($item_ids),
    ))
    ->updateFields(array(
      'item_ids' => serialize($item_ids),
    ))
    ->key(array(
      'uid' => $uid,
    ))
    ->execute();
}
