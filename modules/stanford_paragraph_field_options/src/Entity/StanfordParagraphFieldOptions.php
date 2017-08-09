<?php

namespace Drupal\stanford_paragraph_field_options\Entity;

use Drupal\Core\Config\Entity\ConfigEntityBase;

/**
 * Defines the Stanford paragraph field options entity.
 *
 * @ConfigEntityType(
 *   id = "stanford_paragraph_field_options",
 *   label = @Translation("Stanford paragraph field options"),
 *   handlers = {
 *     "form" = {
 *       "edit" = "Drupal\stanford_paragraph_field_options\Form\StanfordParagraphFieldOptionsForm",
 *     },
 *   },
 *   config_prefix = "stanford_paragraph_field_options",
 *   admin_permission = "administer site configuration",
 *   entity_keys = {
 *     "id" = "id",
 *     "label" = "label",
 *     "uuid" = "uuid"
 *   }
 * )
 */
class StanfordParagraphFieldOptions extends ConfigEntityBase implements StanfordParagraphFieldOptionsInterface {

  /**
   * The Stanford paragraph field options ID.
   *
   * @var string
   */
  protected $id;

  /**
   * The Stanford paragraph field options label.
   *
   * @var string
   */
  protected $label;

}
