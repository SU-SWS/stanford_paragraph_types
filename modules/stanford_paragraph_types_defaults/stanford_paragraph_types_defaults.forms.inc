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
  $defaults = stanford_paragraphs_defaults_load_multiple();
  $output = array();
  foreach (field_read_fields(array('type' => 'paragraphs')) as $field_name => $field) {
    $rows = array();

    $field = field_info_field($field_name);
    foreach ($field['bundles'] as $type => $bundles) {
      $entity_info = entity_get_info($type);

      foreach ($bundles as $bundle) {
        $table_caption = $entity_info['label'] . ' - ';
        $table_caption .= $entity_info['bundles'][$bundle]['label'];
        $table_caption .= ' - ' . $field_name;

        foreach ($defaults as $uid => $default) {
          if ($default['entity_type'] == $type && $default['bundle'] == $bundle && $default['field_name'] == $field_name) {
            $actions = l(t('Edit'), "$path/edit/$uid") . ' | ';
            $actions .= l(t('Delete'), "$path/delete/$uid");
            $rows[] = array(
              $type,
              $bundle,
              $default['label'],
              $actions,
            );
          }
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

function stanford_ptd_edit($form, &$form_state, $default) {
  $form = stanford_ptd_add($form, $form_state, $default['type'], $default['bundle'], $default['field_name']);
  $form['name']['#default_value'] = $default['label'];
  $form['machine_name']['#default_value'] = $default['machine_name'];
  $form['machine_name']['#attributes'] = array('disabled' => TRUE);

  $host_entity = entity_create($default['entity_type'], array('type' => $default['bundle']));
  $field = field_info_field($default['field_name']);
  $instance = field_info_instance($default['entity_type'], $default['field_name'], $default['bundle']);

  $items = array();
  foreach ($default['paragraphs'] as $item_id => $paragraph_item) {
    $items[]['entity'] = $paragraph_item;
  }

  unset($form[$default['field_name']]);
  unset($form_state['field'][$default['field_name']]);

  $paragraphs_field = field_default_form($default['entity_type'], $host_entity, $field, $instance, LANGUAGE_NONE, $items, $form, $form_state);
  $form += (array) $paragraphs_field;
  $form['#submit'][] = 'stanford_ptd_add_submit';

  return $form;
}

function stanford_ptd_delete($form, &$form_state, $default) {
  $form_state['#default'] = $default;
  $path = 'admin/structure/paragraphs/stanford-defaults';
  $question = t('Delete default setting %label', array('%label' => $default['label']));
  $description = t('This action cannot be undone.');
  $form = confirm_form($form, $question, $path, $description, t('Delete'));
  return $form;
}

function stanford_ptd_delete_submit($form, &$form_state) {
  foreach ($form_state['#default']['paragraphs'] as $paragraph_item) {
    entity_delete('paragraphs_item', $paragraph_item->item_id);
  }
  drupal_set_message(t('Default Configuration deleted'));
  $form_state['redirect'] = 'admin/structure/paragraphs/stanford-defaults';
}
