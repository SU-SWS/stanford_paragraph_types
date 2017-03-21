<?php

/**
 * @file
 * Stanford_paragraphs_defaults.features.inc.
 */

/**
 * Implements hook_features_export_files().
 */
function stanford_paragraphs_defaults_features_export_files($module_name, $export) {
  $export_files = &drupal_static('stanford_paragraphs_defaults_files');
  if (!$export_files) {
    return array();
  }

  $files = array();
  foreach ($export_files as $file) {
    $file_name = drupal_basename($file);
    $files["assets/$file_name"] = array(
      'file_path' => $file,
    );
  }
  return $files;
}

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
      $paragraph_item = _stanford_paragraphs_defaults_prepare_entity($paragraph_item, 'paragraphs_item');
    }
    $item['paragraphs'] = array_values($item['paragraphs']);

    $code[] = "  \$paragraphs_defaults['{$uid}'] = " . features_var_export($item, '  ') . ";";
    $code[] = '';
  }

  $code[] = '  return $paragraphs_defaults;';
  return array('paragraphs_defaults' => implode("\n", $code));
}

/**
 * Prepare a given entity to produce a basic object with all field data.
 *
 * @param object $entity
 *   The entity to process.
 * @param string $entity_type
 *   The type of the entity.
 *
 * @return \stdClass
 *   The prepared and processed entity as a standard object for easy export.
 */
function _stanford_paragraphs_defaults_prepare_entity($entity, $entity_type) {
  $entity_info = entity_get_info($entity_type);
  $bundle_key = $entity_info['entity keys']['bundle'];

  $fields = field_read_fields(array(
    'entity_type' => $entity_type,
    'bundle' => $entity->{$bundle_key},
  ));

  foreach ($fields as $field_name => $field) {
    // Prepare specific field data depending on the field type.
    $prepare_function = '_stanford_paragraphs_defaults_prepare_' . $field['type'];

    if (function_exists($prepare_function)) {
      $field_items = field_get_items($entity_type, $entity, $field_name);

      if ($field_items) {
        $field_items = $prepare_function($field_items);
        $entity->{$field_name}[LANGUAGE_NONE] = $field_items;
      }
    }
  }

  // Clone and get just the properties we care about.
  $new_object = new stdClass();
  foreach ($entity as $property => $value) {
    if (!empty($value)) {
      $new_object->{$property} = $value;
    }
  }

  foreach ($entity_info['entity keys'] as $key) {
    unset($new_object->{$key});
  }
  unset($new_object->uuid, $new_object->default_revision);

  $new_object->entity_type = $entity_type;
  $new_object->entity_bundle = $entity->{$bundle_key};
  if ($entity_type = 'paragraphs') {
    $new_object->field_name = $entity->field_name;
  }
  return $new_object;
}

/**
 * Prepare image field type items.
 *
 * @param array $field_items
 *   Field items provided by field_get_items().
 *
 * @return array
 *   Prepared field_items.
 */
function _stanford_paragraphs_defaults_prepare_image(array $field_items) {
  $files = &drupal_static('stanford_paragraphs_defaults_files');
  foreach ($field_items as &$item) {
    $files[$item['uri']] = $item['uri'];
    $item = array(
      'filemime' => $item['filemime'],
      'alt' => $item['alt'],
      'title' => $item['title'],
      'uri' => drupal_basename($item['uri']),
      'filesize' => $item['filesize'],
    );
  }
  return $field_items;
}

/**
 * Prepare file field type items.
 *
 * @param array $field_items
 *   Field items provided by field_get_items().
 *
 * @return array
 *   Prepared field_items.
 */
function _stanford_paragraphs_defaults_prepare_file(array $field_items) {
  $files = &drupal_static('stanford_paragraphs_defaults_files');
  foreach ($field_items as &$item) {
    $files[$item['uri']] = $item['uri'];
    $item = array(
      'filemime' => $item['filemmime'],
      'display' => $item['display'],
      'description' => $item['description'],
      'uri' => drupal_basename($item['uri']),
      'filesize' => $item['filesize'],
    );
  }
  return $field_items;
}

/**
 * Prepare video embed field type items.
 *
 * @param array $field_items
 *   Field items provided by field_get_items().
 *
 * @return array
 *   Prepared field_items.
 */
function _stanford_paragraphs_defaults_prepare_video_embed_field(array $field_items) {
  foreach ($field_items as &$item) {
    unset($item['thumbnail_path']);
  }
  return $field_items;
}

/**
 * Prepare paragraphs field type items.
 *
 * @param array $field_items
 *   Field items provided by field_get_items().
 *
 * @return array
 *   Prepared field_items.
 */
function _stanford_paragraphs_defaults_features_prepare_paragraphs(array $field_items) {
  foreach ($field_items as &$item) {
    $paragraph_item = paragraphs_item_load($item['value']);
    $item = _stanford_paragraphs_defaults_prepare_entity($paragraph_item, 'paragraphs_item');
  }
  return $field_items;
}

/**
 * Prepare field collection field type items.
 *
 * @param array $field_items
 *   Field items provided by field_get_items().
 *
 * @return array
 *   Prepared field_items.
 */
function _stanford_paragraphs_defaults_prepare_field_collection(array $field_items) {
  foreach ($field_items as &$item) {
    $item = field_collection_item_load($item['value']);
    $item = _stanford_paragraphs_defaults_prepare_entity($item, 'field_collection_item');
  }
  return $field_items;
}

/**
 * Implements hook_features_rebuild().
 */
function paragraphs_defaults_features_rebuild($module_name) {
  $paragraphs_defaults = module_invoke($module_name, 'paragraphs_defaults');
  if (!empty($paragraphs_defaults)) {
    foreach ($paragraphs_defaults as $paragraph_default) {
      paragraphs_defaults_save($paragraph_default, $module_name);
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
      paragraphs_defaults_save($paragraph_default, $module_name);
    }
  }
}

/**
 * Save the features exported default settings.
 *
 * @param array $default
 *   Paragraph default exported.
 */
function paragraphs_defaults_save(array $default, $module_name) {
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
  if (!$entity_info || !isset($entity_info['bundles'][$default['bundle']])) {
    return;
  }

  $item_ids = array();
  foreach ($default['paragraphs'] as $weight => $item) {
    $item_id = _paragraphs_defaults_save_entity($item['entity_type'], $item['entity_bundle'], $item, $module_name);
    $item_ids[$item_id] = $weight;
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

/**
 * Create and save an entity with its field data.
 *
 * @param string $entity_type
 *   Type of the entity.
 * @param string $bundle
 *   Bundle of the entity.
 * @param array $fields
 *   Fields and properties to set in the entity.
 * @param string $module_name
 *   Module that defines the default setting.
 *
 * @return int
 *   Entity id of the entity.
 */
function _paragraphs_defaults_save_entity($entity_type, $bundle, array $fields, $module_name, $host_entity = NULL, $host_type = NULL) {
  $entity_info = entity_get_info($entity_type);
  $entity_options = array(
    'bundle' => $bundle,
    'field_name' => $fields['field_name'],
  );
  $entity = entity_create($entity_type, $entity_options);
  $entity->{$entity_info['entity keys']['bundle']} = $bundle;
  unset($fields['entity_type'], $fields['entity_bundle']);

  foreach ($fields as $field_name => $values) {
    $entity->{$field_name} = $values;
  }
  $entity->is_new = TRUE;

  $fields = field_info_instances($entity_type, $bundle);

  foreach (array_keys($fields) as $field_name) {

    if (!empty($entity->{$field_name})) {
      $field_items = $entity->{$field_name}[LANGUAGE_NONE];
      _paragraphs_defaults_save_field_values($field_items, $module_name, $entity, $entity_type);
      $entity->{$field_name}[LANGUAGE_NONE] = $field_items;
    }
  }
  // Save paragraph item without setting host entity.
  switch ($entity_type) {
    case 'paragraphs_item':
      /* @param ParagraphsItemEntity $entity */
      $entity->save(TRUE);
      break;

    case 'field_collection_item':
      $entity->setHostEntity($host_type, $host_entity);
      $entity->save(TRUE);
      break;

    default:
      entity_save($entity_type, $entity);
      break;
  }

  list($entity_id, ,) = entity_extract_ids($entity_type, $entity);
  return $entity_id;
}

/**
 * Manipulate the field items before saving.
 *
 * @param array $field_items
 *   Field data.
 * @param string $module_name
 *   Module name of the feature.
 */
function _paragraphs_defaults_save_field_values(array &$field_items, $module_name, $host_entity = NULL, $host_type = NULL) {
  $dir = 'public://paragraphs_defaults';
  file_prepare_directory($dir, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);

  $dir = "public://paragraphs_defaults/$module_name";
  file_prepare_directory($dir, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);

  foreach ($field_items as &$item) {
    if (isset($item['entity_type'])) {
      $entity_id = _paragraphs_defaults_save_entity($item['entity_type'], $item['entity_bundle'], $item, $module_name, $host_entity, $host_type);
      $item = array('value' => $entity_id);
    }

    if (isset($item['uri'])) {
      $old_file = new stdClass();
      $old_file->uri = drupal_get_path('module', $module_name) . '/assets/' . $item['uri'];
      $file = file_copy($old_file, "$dir/{$item['uri']}", FILE_EXISTS_REPLACE);
      if ($file) {
        unset($item['uri']);
        foreach ($item as $key => $value) {
          $file->{$key} = $value;
        }
        file_save($file);
        $item = (array) $file;
      }
    }
  }
}
