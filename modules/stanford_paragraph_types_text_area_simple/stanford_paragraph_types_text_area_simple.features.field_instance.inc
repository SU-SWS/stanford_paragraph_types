<?php
/**
 * @file
 * stanford_paragraph_types_text_area_simple.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function stanford_paragraph_types_text_area_simple_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'paragraphs_item-p_wysiwyg_no_title-field_p_wnt_body'.
  $field_instances['paragraphs_item-p_wysiwyg_no_title-field_p_wnt_body'] = array(
    'bundle' => 'p_wysiwyg_no_title',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_p_wnt_body',
    'label' => 'Body',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'content_editor_text_format' => 'content_editor_text_format',
          'filtered_html' => 'filtered_html',
          'full_html' => 'full_html',
          'minimal_html' => 'minimal_html',
          'plain_text' => 'plain_text',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'content_editor_text_format' => array(
              'weight' => -10,
            ),
            'filtered_html' => array(
              'weight' => 0,
            ),
            'full_html' => array(
              'weight' => 1,
            ),
            'minimal_html' => array(
              'weight' => 0,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'paragraphs_item-p_wysiwyg_no_title-field_p_wnt_image'.
  $field_instances['paragraphs_item-p_wysiwyg_no_title-field_p_wnt_image'] = array(
    'bundle' => 'p_wysiwyg_no_title',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_p_wnt_image',
    'label' => 'Image',
    'required' => 0,
    'settings' => array(
      'alt_field' => 1,
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '3200x3200',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'insert' => 1,
        'insert_absolute' => 0,
        'insert_class' => '',
        'insert_default' => 'auto',
        'insert_styles' => array(
          'auto' => 0,
          'colorbox__3-col-header' => 0,
          'colorbox__4-col-header' => 0,
          'colorbox__6-col-banner' => 0,
          'colorbox__6-col-banner-short' => 0,
          'colorbox__6-col-banner-tall' => 0,
          'colorbox__6-col-photo-landscape' => 0,
          'colorbox__8-col-banner' => 0,
          'colorbox__8-col-banner-short' => 0,
          'colorbox__8-col-banner-tall' => 0,
          'colorbox__9-col-banner' => 0,
          'colorbox__9-col-banner-short' => 0,
          'colorbox__12-col-banner' => 0,
          'colorbox__12-col-banner-tall' => 0,
          'colorbox__banner-850x400' => 0,
          'colorbox__full-width-banner' => 0,
          'colorbox__full-width-banner-short' => 0,
          'colorbox__full_width_banner_tall' => 0,
          'colorbox__half-page-profile' => 0,
          'colorbox__header_scale_850x400' => 0,
          'colorbox__huge-landscape' => 0,
          'colorbox__icon-profile' => 0,
          'colorbox__icon-scaled' => 0,
          'colorbox__icon-square' => 0,
          'colorbox__large' => 0,
          'colorbox__large-landscape' => 0,
          'colorbox__large-landscape-scaled' => 0,
          'colorbox__large-profile' => 0,
          'colorbox__large-profile-scaled' => 0,
          'colorbox__large-scaled' => 0,
          'colorbox__large-square' => 0,
          'colorbox__med-landscape' => 0,
          'colorbox__med-landscape-scaled' => 0,
          'colorbox__med-profile' => 0,
          'colorbox__med-profile-scaled' => 0,
          'colorbox__med-square' => 0,
          'colorbox__medium' => 0,
          'colorbox__page-width' => 0,
          'colorbox__sm-landscape' => 0,
          'colorbox__sm-landscape-scaled' => 0,
          'colorbox__sm-profile' => 0,
          'colorbox__sm-profile-scaled' => 0,
          'colorbox__sm-scaled' => 0,
          'colorbox__sm-square' => 0,
          'colorbox__thmb-landscape' => 0,
          'colorbox__thmb-profile' => 0,
          'colorbox__thmb-square' => 0,
          'colorbox__thumbnail' => 0,
          'icon_link' => 0,
          'image' => 'image',
          'image_3-col-header' => 0,
          'image_4-col-header' => 0,
          'image_6-col-banner' => 0,
          'image_6-col-banner-short' => 0,
          'image_6-col-banner-tall' => 0,
          'image_6-col-photo-landscape' => 0,
          'image_8-col-banner' => 0,
          'image_8-col-banner-short' => 0,
          'image_8-col-banner-tall' => 0,
          'image_9-col-banner' => 0,
          'image_9-col-banner-short' => 0,
          'image_12-col-banner' => 0,
          'image_12-col-banner-tall' => 0,
          'image_banner-850x400' => 0,
          'image_full-width-banner' => 0,
          'image_full-width-banner-short' => 0,
          'image_full_width_banner_tall' => 0,
          'image_half-page-profile' => 0,
          'image_header_scale_850x400' => 0,
          'image_huge-landscape' => 0,
          'image_icon-profile' => 0,
          'image_icon-scaled' => 0,
          'image_icon-square' => 0,
          'image_large' => 0,
          'image_large-landscape' => 0,
          'image_large-landscape-scaled' => 0,
          'image_large-profile' => 0,
          'image_large-profile-scaled' => 0,
          'image_large-scaled' => 'image_large-scaled',
          'image_large-square' => 'image_large-square',
          'image_med-landscape' => 0,
          'image_med-landscape-scaled' => 0,
          'image_med-profile' => 0,
          'image_med-profile-scaled' => 0,
          'image_med-square' => 'image_med-square',
          'image_medium' => 0,
          'image_page-width' => 'image_page-width',
          'image_sm-landscape' => 0,
          'image_sm-landscape-scaled' => 0,
          'image_sm-profile' => 0,
          'image_sm-profile-scaled' => 0,
          'image_sm-scaled' => 0,
          'image_sm-square' => 'image_sm-square',
          'image_thmb-landscape' => 0,
          'image_thmb-profile' => 0,
          'image_thmb-square' => 0,
          'image_thumbnail' => 0,
          'link' => 0,
        ),
        'insert_width' => '',
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Body');
  t('Image');

  return $field_instances;
}
