<?php

/**
 * @file
 * Stanford Paragraph Types Defaults Forms.
 */

/**
 * Overview list page of existing defaults.
 */
function stanford_ptd_overview() {
  $path = 'admin/structure/paragraphs/stanford-defaults';
  $output = array();
  foreach (field_read_fields(array('type' => 'paragraphs')) as $field_name => $field) {
    $rows = array();

    $field = field_info_field($field_name);
    foreach ($field['bundles'] as $type => $bundles) {
      $entity_info = entity_get_info($type);

      foreach ($bundles as $bundle) {
        $defaults = stanford_ptd_load_defaults($type, $bundle, $field_name);
        $table_caption = $entity_info['label'] . ' - ';
        $table_caption .= $entity_info['bundles'][$bundle]['label'];
        $table_caption .= ' - ' . $field_name;

        foreach ($defaults[$field_name] as $item_id => $label) {
          $key = bin2hex("$type:$bundle:$item_id");
          $actions = l(t('Edit'), "$path/edit/$key") . ' | ';
          $actions .= l(t('Delete'), "$path/delete/$key");
          $rows[] = array(
            $type,
            $bundle,
            $label,
            $actions,
          );
        }

        $add_link = l(t('Add New Default'), "$path/add/$type/$bundle/$field_name");
        $rows[] = array(
          'data' => array(array('data' => $add_link, 'colspan' => 4)),
        );
        $output[$type][$bundle][$field_name] = array(
          '#theme' => 'table',
          '#caption' => $table_caption,
          '#header' => array(
            t('Entity Type'),
            t('Entity Bundle'),
            t('Name'),
            t('Operations'),
          ),
          '#rows' => $rows,
        );
      }
    }
  }
  return $output;
}

/**
 * Implements hook_form().
 */
function stanford_paragraph_types_defaults_form($form, &$form_state) {
  $form = array();
  return $form;
}

function stanford_ptd_add($form, &$form_state, $entity_type, $bundle, $field_name) {
  if ((!$field = field_info_field($field_name)) || $field['type'] != 'paragraphs') {
    drupal_not_found();
    drupal_exit();
  }
  $form_state['entity_info'] = array(
    'entity_type' => $entity_type,
    'bundle' => $bundle,
    'field_name' => $field_name,
  );
  $form = array();

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#required' => TRUE,
  );
  $form['machine_name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Machine Name'),
    '#machine_name' => array(
      'exists' => '_stanford_ptd_machine_name',
    ),
  );

  $form['#parents'] = array();

  // Add the paragraphs field.
  $field = field_info_field($field_name);
  $instance = field_info_instance($entity_type, $field_name, $bundle);
  $host_entity = entity_create($entity_type, array('type' => $bundle));

  $items = array();
  $paragraphs_field = field_default_form($entity_type, $host_entity, $field, $instance, LANGUAGE_NONE, $items, $form, $form_state);
  $form += (array) $paragraphs_field;

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 50,
  );

  return $form;
}

function stanford_ptd_add_submit($form, &$form_state) {
  $entity_type = $form_state['entity_info']['entity_type'];
  $bundle = $form_state['entity_info']['bundle'];
  $field_name = $form_state['entity_info']['field_name'];
  $label = $form_state['values']['name'];
  $machine_name = $form_state['values']['machine_name'];
  stanford_ptd_save_defaults($entity_type, $bundle, $field_name, $label, $machine_name, $form_state['values'][$field_name]);
  $form_state['redirect'] = 'admin/structure/paragraphs/stanford-defaults';
}

function _stanford_ptd_machine_name($string, $form, &$form_state) {
  $query = db_select('stanford_paragraphs_defaults', 's')
    ->fields('s')
    ->condition('entity_type', $form_state['entity_info']['entity_type'])
    ->condition('bundle', $form_state['entity_info']['bundle'])
    ->condition('field_name', $form_state['entity_info']['field_name'])
    ->condition('machine_name', $string)
    ->execute()
    ->rowCount();
  return $query;
}

function stanford_ptd_edit($form, &$form_state, $item) {
  list($type, $bundle, $machine_name) = explode(':', hex2bin($item));
  $name = db_select('stanford_paragraphs_defaults', 's')
    ->fields('s', array('label'))
    ->condition('entity_type', $type)
    ->condition('bundle', $bundle)
    ->condition('machine_name', $machine_name)
    ->execute()->fetchField();

  $defaults = stanford_ptd_load_default_paragraphs($type, $bundle, $machine_name);
  $field_name = $defaults[key($defaults)]->field_name;

  $form = stanford_ptd_add($form, $form_state, $type, $bundle, $field_name);
  $form['name']['#default_value'] = $name;
  $form['machine_name']['#default_value'] = $machine_name;
  $form['machine_name']['#attributes'] = array('disabled' => TRUE);

  $host_entity = entity_create($type, array('type' => $bundle));
  $field = field_info_field($field_name);
  $instance = field_info_instance($type, $field_name, $bundle);

  $items = array();
  foreach ($defaults as $item_id => $paragraph_item) {
    $items[]['entity'] = $paragraph_item;
  }

  unset($form[$field_name]);
  unset($form_state['field'][$field_name]);

  $paragraphs_field = field_default_form($type, $host_entity, $field, $instance, LANGUAGE_NONE, $items, $form, $form_state);
  $form += (array) $paragraphs_field;
  $form['#submit'][] = 'stanford_ptd_add_submit';

  return $form;
}

function stanford_ptd_delete($form, &$form_state, $item_id) {
  list($type, $bundle, $machine_name) = explode(':', hex2bin($item_id));
  $form_state['#entity_type'] = $type;
  $form_state['#entity_bundle'] = $bundle;
  $form_state['#machine_name'] = $machine_name;
  $defaults = stanford_ptd_load_default_paragraphs($type, $bundle, $machine_name);
  $form_state['#default_paragraphs'] = $defaults;
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#name' => 'delete',
  );
  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#name' => 'cancel',
  );
  return $form;
}

function stanford_ptd_delete_submit($form, &$form_state) {
  if ($form_state['triggering_element']['#name'] == 'delete') {
    foreach ($form_state['#default_paragraphs'] as $paragraph_item) {
      entity_delete('paragraphs_item', $paragraph_item->item_id);
    }
    drupal_set_message(t('Default Configuration deleted'));
  }
  $form_state['redirect'] = 'admin/structure/paragraphs/stanford-defaults';
}
