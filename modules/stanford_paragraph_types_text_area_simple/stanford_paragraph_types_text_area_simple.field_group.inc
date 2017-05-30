<?php
/**
 * @file
 * stanford_paragraph_types_text_area_simple.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function stanford_paragraph_types_text_area_simple_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_p_wnt_style|paragraphs_item|p_wysiwyg_no_title|form';
  $field_group->group_name = 'group_p_wnt_style';
  $field_group->entity_type = 'paragraphs_item';
  $field_group->bundle = 'p_wysiwyg_no_title';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'WYSIWYG',
    'weight' => '3',
    'children' => array(
      0 => 'field_p_wnt_body',
      1 => 'field_p_wnt_image',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'WYSIWYG',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-p-wnt-style field-group-fieldset wnt-container',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_p_wnt_style|paragraphs_item|p_wysiwyg_no_title|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('WYSIWYG');

  return $field_groups;
}
