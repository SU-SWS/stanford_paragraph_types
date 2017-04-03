<?php

/**
 * @file
 * P_callout paragraph type.
 */
?>
<div <?php print $attributes; ?>>
  <div class="<?php print $classes; ?>"<?php print $attributes; ?>>
    <div class="content row-fluid"<?php print $content_attributes; ?>>
      <?php print render($content); ?>
    </div>
  </div>
</div>