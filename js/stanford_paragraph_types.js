/**
 * @file
 * Applies some functionality on the paragraph types.
 */

(function ($) {
  Drupal.behaviors.stanfordParagraphTypes = {
    attach: function (context, settings) {
      $('.field-name-field-p-hero-image', context).each(function () {
        var video = $(this).siblings('.field-name-field-p-hero-video');

        if (video.length) {
          var videoUrl = $(video).find('div[data-video-embed-url]').attr('data-video-embed-url');

          var play = $('<a>', {
            class: 'play-video',
            href: videoUrl,
            html: $('<i>', {class: 'fa fa-youtube-play icon-youtube-play', html: 'Play Video'})
          }).mouseup(function (e) {
            e.preventDefault();

            $dad = $(this).parent();
            $dad.hide();
            $dad.siblings('.group-overlay-text').hide();
            var iframe = $(video).find('iframe')[0];

            iframe.src += "&autoplay=1";
            $(iframe).attr('onload', 'this.contentWindow.focus()');
            $(video).show();

            return false;
          }).click(function(e){
            e.preventDefault();
            return false;
          });

          $(this).prepend(play);
        }
      });
    }
  }
})(jQuery);
