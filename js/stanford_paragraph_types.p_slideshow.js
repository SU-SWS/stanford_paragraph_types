/**
 * @file
 * Applies some functionality on the paragraph types.
 */

(function ($) {
  Drupal.behaviors.stanfordParagraphTypesSlideshow = {
    attach: function (context, settings) {
      $('.field-slideshow-wrapper', context).each(function () {
        $(this).find('.field-slideshow-pager a').each(function () {
          $(this).attr('title', 'Go to slide ' + $(this).text());
        });
      });
    }
  }
})(jQuery);
