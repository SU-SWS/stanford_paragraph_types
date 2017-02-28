/**
 * @file
 * Applies some functionality on the paragraph types in the admin form.
 */

(function ($) {
  Drupal.behaviors.stanfordParagraphTypesAdmin = {
    attach: function (context, settings) {

      $('.group-p-card-cta', context).each(function () {
        var group = this;
        $(this).find('.form-radio').each(function () {
          if ($(this).is(':checked')) {
            teaserCardsCTA(group, $(this).val());
          }
          $(this).change(function () {
            teaserCardsCTA(group, $(this).val());
          });
        });

      });

      // Used this method vs conditional_fields since the contrib module failed to function correctly after a 2nd
      // item was added.
      function teaserCardsCTA(group, radioVal) {
        if (radioVal == 'link') {
          $(group).find('.field-name-field-p-card-cta').show();
          $(group).find('.field-name-field-p-card-file').hide();
        } else {
          $(group).find('.field-name-field-p-card-cta').hide();
          $(group).find('.field-name-field-p-card-file').show();
        }
      }
    }
  }
})(jQuery);
