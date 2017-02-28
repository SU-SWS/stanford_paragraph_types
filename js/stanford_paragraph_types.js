/**
 * @file
 * Applies some functionality on the paragraph types.
 */

(function ($) {
  Drupal.behaviors.stanfordParagraphTypes = {
    attach: function (context, settings) {
      $('.field-name-field-p-hero-image', context).each(function () {
        if ($(this).siblings('.field-name-field-p-hero-video').length) {
          var play = $('<a>', {
            class: 'play-video',
            href: '#',
            html: $('<i>', {class: 'fa fa-youtube-play icon-youtube-play', html: 'Play'})
          }).click(function (e) {
            e.preventDefault();
            $dad = $(this).parent();
            $dad.hide();
            $dad.siblings('.group-overlay-text').hide();
            $dad.siblings('.field-name-field-p-hero-video').show();
            $dad.siblings('.field-name-field-p-hero-video').find('iframe')[0].src += "&autoplay=1";
          });
          $(this).prepend(play);
        }
      });

      $('.group-p-card-cta .form-radio', context).each(function () {
        console.log($(this).val());
      })
    }
  }
})(jQuery);
