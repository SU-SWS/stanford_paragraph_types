<?php

/**
 * @file
 * Stanford_paragraphs_defaults.features.inc.
 */

/**
 * Implements hook_features_export_options().
 */
function paragraphs_defaults_features_export_options() {
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
function paragraphs_defaults_features_export($data, &$export, $module_name) {
  $export['dependencies']['stanford_paragraphs_defaults'] = 'stanford_paragraphs_defaults';
  foreach ($data as $uid) {
    $export['features']['paragraphs_defaults'][$uid] = $uid;
  }
  return array();
}

/**
 * Implements hook_features_export_render().
 */
function paragraphs_defaults_features_export_render($module_name, $data, $export = NULL) {
  $defaults = stanford_paragraphs_defaults_load_multiple($data);
  $code = array('  $paragraphs_defaults = array();');

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

    $code[] = "  \$paragraphs_defaults['{$uid}'] = " . features_var_export($item, '  ') . ";";
    $code[] = '';
  }

  $code[] = '  return $paragraphs_defaults;';
  $code = implode("\n", $code);

  return array('paragraphs_defaults' => $code);
}

/**
 * Implements hook_features_rebuild().
 */
function paragraphs_defaults_features_rebuild($module_name) {
  $paragraphs_defaults = module_invoke($module_name, 'paragraphs_defaults');
  if (!empty($paragraphs_defaults)) {
    foreach ($paragraphs_defaults as $paragraph_default) {
      paragraphs_defaults_save($paragraph_default);
    }
  }
}

/**
 * Implements hook_features_revert().
 */
function paragraphs_defaults_features_revert($module_name) {
  $paragraphs_defaults = module_invoke($module_name, 'paragraphs_defaults');
  if (!empty($paragraphs_defaults)) {
    foreach ($paragraphs_defaults as $paragraph_default) {
      paragraphs_defaults_save($paragraph_default);
    }
  }
}

/**
 * Save the features exported default settings.
 *
 * @param array $default
 *   Paragraph default exported.
 */
function paragraphs_defaults_save(array $default) {
  // Clear out old default configuration.
  $uid = "{$default['entity_type']}-{$default['bundle']}-{$default['field_name']}-{$default['machine_name']}";

  if ($original_default = stanford_paragraphs_defaults_load($uid)) {
    $item_ids = array();
    foreach ($original_default['paragraphs'] as $paragraph_item) {
      $item_ids[] = $paragraph_item->item_id;
    }
    entity_delete_multiple('paragraphs_item', $item_ids);
  }

  // Check if entity type and bundle exist before saving.
  $entity_info = entity_get_info($default['entity_type']);
  if (!$entity_info || !isset($entity_info[$default['bundle']])) {
    return;
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

  $fields = array(
    'label' => $default['label'],
    'machine_name' => $default['machine_name'],
    'entity_type' => $default['entity_type'],
    'field_name' => $default['field_name'],
    'bundle' => $default['bundle'],
    'item_ids' => serialize($item_ids),
  );

  db_merge('stanford_paragraphs_defaults')
    ->insertFields($fields)
    ->updateFields(array(
      'item_ids' => $fields['item_ids'],
    ))
    ->key(array(
      'uid' => $uid,
    ))
    ->execute();
}
