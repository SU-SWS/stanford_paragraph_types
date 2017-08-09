<?php

namespace Drupal\stanford_paragraph_field_options\Form;

use Drupal\Core\Entity\EntityForm;
use Drupal\Core\Entity\EntityTypeBundleInfo;
use Drupal\Core\Form\FormStateInterface;

/**
 * Class StanfordParagraphFieldOptionsForm.
 */
class StanfordParagraphFieldOptionsForm extends EntityForm {

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state, $entity_type_id = NULL, $bundle = NULL) {
    $form = [];

    if (!$form_state->get('entity_type_id')) {
      $form_state->set('entity_type_id', $entity_type_id);
    }
    if (!$form_state->get('bundle')) {
      $form_state->set('bundle', $bundle);
    }

//    EntityTypeBundleInfo

    $form['label'] = [
      '#type' => 'textfield',
      '#title' => $this->t('Label'),
      '#maxlength' => 255,
      '#default_value' => $this->entity->label(),
      '#description' => $this->t("Label for the Stanford paragraph field options."),
      '#required' => TRUE,
    ];

    $form['id'] = [
      '#type' => 'machine_name',
      '#default_value' => $this->entity->id(),
      '#machine_name' => [
        'exists' => '\Drupal\stanford_paragraph_field_options\Entity\StanfordParagraphFieldOptions::load',
      ],
      '#disabled' => !$this->entity->isNew(),
    ];

    $form['actions'] = ['#type' => 'actions'];
    $form['actions']['submit'] = [
      '#type' => 'submit',
      '#value' => $this->t('Save and continue'),
      '#button_type' => 'primary',
    ];

    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function save(array $form, FormStateInterface $form_state) {
    $stanford_paragraph_field_options = $this->entity;
    $status = $stanford_paragraph_field_options->save();

    switch ($status) {
      case SAVED_NEW:
        drupal_set_message($this->t('Created the %label Stanford paragraph field options.', [
          '%label' => $stanford_paragraph_field_options->label(),
        ]));
        break;

      default:
        drupal_set_message($this->t('Saved the %label Stanford paragraph field options.', [
          '%label' => $stanford_paragraph_field_options->label(),
        ]));
    }
    $form_state->setRedirectUrl($stanford_paragraph_field_options->toUrl('collection'));
  }

}
