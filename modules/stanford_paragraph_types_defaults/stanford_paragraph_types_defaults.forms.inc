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
      foreach ($bundles as $bundle) {
        $defaults = stanford_ptd_load_defaults($type, $bundle, $field_name);
        foreach ($defaults[$field_name] as $item_id => $label) {
          $actions = l(t('Edit'), "$path/edit/$item_id") . ' | ';
          $actions .= l(t('Delete'), "$path/delete/$item_id");
          $rows[] = array(
            $type,
            $bundle,
            $label,
            $actions,
          );
        }
      }
    }
    $output[$field_name] = array(
      '#theme' => 'table',
      '#caption' => $field_name,
      '#header' => array(
        t('Entity Type'),
        t('Entity Bundle'),
        t('Default Config'),
        t('Operations'),
      ),
      '#rows' => $rows,
    );
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
  $defaults = array();
//  $defaults = paragraphs_defaults_load_defaults($entity_type, $field_name, $bundle);
  $paragraphs = paragraphs_item_load_multiple($defaults);

  $host_entity = entity_create($entity_type, array('type' => $bundle));

  // Order any existing paragraphs in a form we can use to set the default
  // value.
  $items = array();
  foreach ($paragraphs as $paragraph_item) {
    $items[]['entity'] = $paragraph_item;
  }
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

function stanford_ptd_edit($form, &$form_state, $field) {
  $form = array();


  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

function stanford_ptd_delete($item_id) {

}
