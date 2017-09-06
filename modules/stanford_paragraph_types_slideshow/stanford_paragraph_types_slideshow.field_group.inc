<?php
/**
 * @file
 * stanford_paragraph_types_slideshow.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function stanford_paragraph_types_slideshow_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_slideshow|paragraphs_item|p_slideshow|form';
  $field_group->group_name = 'group_slideshow';
  $field_group->entity_type = 'paragraphs_item';
  $field_group->bundle = 'p_slideshow';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Slideshow',
    'weight' => '0',
    'children' => array(
      0 => 'field_p_slideshow_slides',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-slideshow field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups[''] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Slideshow');

  return $field_groups;
}
