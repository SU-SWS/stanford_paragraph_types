<?php

/**
 * @file
 * Field Icon Block Template.
 */
?>

<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div class="field-label"<?php print $title_attributes; ?>><?php print $label ?>:&nbsp;</div>
  <?php endif; ?>

  <?php foreach ($items as $delta => $item): ?>
    <?php if(!($delta % 3)): ?>
      <div class="field-items row-fluid clearfix"<?php print $content_attributes; ?>>
    <?php endif; ?>
        <div class="field-item <?php print $delta % 2 ? 'odd' : 'even'; ?>"<?php print $item_attributes[$delta]; ?>><?php print render($item); ?></div>
    <?php if($delta % 3 == 2 || $delta == count($items) - 1): ?>
      </div>
    <?php endif; ?>

  <?php endforeach; ?>
</div>
