/**
 * @file
 * Applies some functionality on the paragraph types.
 */

(function ($) {
  Drupal.behaviors.stanfordParagraphPHero = {

    attach: function (context, settings) {
      var i = 0;
      $('.field-name-field-p-hero-video iframe').each(function (i, iframe) {
        // Make sure the video has an ID attribute.
        if (typeof $(iframe).attr('id') == 'undefined') {
          $(this).attr('id', 'hero-video-' + i);
        }
        i++;
      });


      var tag = document.createElement('script');
      var firstScriptTag = document.getElementsByTagName('script')[0];

      if ($('.field-name-field-p-hero-video iframe[src*="youtube"]').length) {
        tag.src = '//www.youtube.com/iframe_api';
        firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);
      }

      if ($('.field-name-field-p-hero-video iframe[src*="vimeo"]').length) {
        $.getScript('//player.vimeo.com/api/player.js', function () {
          Drupal.behaviors.stanfordParagraphPHero.vimeoReady();
        });
      }
    },

    /**
     * Called after YouTubes API is ready and adds event reactions to videos.
     */
    youTubeReady: function () {

      $('.field-name-field-p-hero-image').once('youtube', function (i, heroImage) {
        var $fieldWrapper = $(heroImage).siblings('.field-name-field-p-hero-video');
        var $video = $fieldWrapper.find('iframe[src*="youtube"]');

        if (!$video.length) {
          return;
        }
        $video.attr('onload', 'this.contentWindow.focus()')
          .attr('title', Drupal.t('Video Player'));
        var ytPlayer = new YT.Player($video.attr('id'));

        var play = Drupal.behaviors.stanfordParagraphPHero.getPlayerButton($video.attr('src'));

        play.click(function (e) {
          // Mouse has eventPhase 3, keyboard has 2.
          if (e.eventPhase == 3) {
            e.preventDefault();
            $dad = $(this).parent();
            $dad.hide();
            $dad.siblings('.group-overlay-text').hide();

            $fieldWrapper.show();
            try {
              ytPlayer.playVideo()();
            }
            catch (e) {
            }
          }
        });

        $(heroImage).prepend(play);
      });
    },

    /**
     * After vimeo API is loaded, add the play button and listener to iframes.
     */
    vimeoReady: function () {
      $('.field-name-field-p-hero-video iframe[src*="vimeo"]').each(function (i, iframe) {
        var player = new Vimeo.Player($(iframe));

        $fieldWrapper = $($(iframe).closest('.field-name-field-p-hero-video'));
        $imageOverlay = $fieldWrapper.siblings('.field-name-field-p-hero-image');

        var play = Drupal.behaviors.stanfordParagraphPHero.getPlayerButton($(iframe).attr('src'));

        play.click(function (e) {
          // Mouse has eventPhase 3, keyboard has 2.
          if (e.eventPhase == 3) {
            e.preventDefault();
            $dad = $(this).parent();
            $dad.hide();
            $dad.siblings('.group-overlay-text').hide();
            $fieldWrapper.show();
            player.play();
          }
        });

        $imageOverlay.prepend(play);
      });
    },

    /**
     * Get a generic play button link.
     *
     * @param hrefUrl
     * @returns {*|HTMLElement}
     */
    getPlayerButton: function (hrefUrl) {
      return $('<a>', {
        class: 'play-video',
        href: hrefUrl,
        html: $('<i>', {
          class: 'fa fa-youtube-play icon-youtube-play',
          html: 'Play Video',
          'aria-label': Drupal.t('Play Video - Opens to the video website')
        })
      });
    }

  }
})(jQuery);

/**
 * Called automatically by YouTube's API.
 */
function onYouTubeIframeAPIReady() {
  // After Youtube API is loaded, we can do what we need.
  Drupal.behaviors.stanfordParagraphPHero.youTubeReady();
}
