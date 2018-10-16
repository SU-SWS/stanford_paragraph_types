/**
 * @file
 * Applies some functionality on the paragraph types.
 */

(function ($) {
  Drupal.behaviors.stanfordParagraphPHero = {

    attach: function (context, settings) {

      // Loop through each hero video fields and add a unique ID.
      $('.field-name-field-p-hero-video iframe', context).each(function (i, iframe) {
        // Make sure the video has an ID attribute.
        if (typeof $(iframe).attr('id') == 'undefined') {
          $(this).attr('id', 'hero-video-' + i);
        }
      });

      // If there is a youtube player, add the player api script.
      if ($('.field-name-field-p-hero-video iframe[src*="youtube"]', context).length) {
        $.getScript('https://www.youtube.com/iframe_api');
      }

      // If there is a vimeo video add the player api script.
      if ($('.field-name-field-p-hero-video iframe[src*="vimeo"]', context).length) {
        $.getScript('https://player.vimeo.com/api/player.js', function () {
          Drupal.behaviors.stanfordParagraphPHero.vimeoReady();
        });
      }
    },

    /**
     * Called after YouTubes API is ready and adds event reactions to videos.
     */
    youTubeReady: function () {
      // For each of the hero images, but only once, add onload/onready events
      // to its sibling video player.
      $('.field-name-field-p-hero-image').once('youtube', function (i, heroImage) {

        // Look for a hero video.
        var $video = $(heroImage).siblings('.field-name-field-p-hero-video').find('iframe[src*="youtube"]');

        // End if none. The user might have only wanted an image, or it might
        // be a vimeo video.
        if (!$video.length) {
          return;
        }

        // On each of the video elements attach an onReady event and set the
        // title for accessibility reasons.
        $video.attr('onload', 'this.contentWindow.focus()')
          .attr('title', Drupal.t('Video Player'));

        // Initialze the Youtube api.
        new YT.Player($video.attr('id'), {
          events: {
            'onReady': onYoutubePlayerReady
          }
        });
        // Force the iframe to allow the api event listeners.
        $video.attr('src', $video.attr('src') + '&enablejsapi=1');
      });


      /**
       * When the youtube video is ready to play, we'll add a play button over
       * the image and add the click listener.
       *
       * @param event
       */
      function onYoutubePlayerReady(event) {
        $fieldWrapper = $(event.target.a.closest('.field-name-field-p-hero-video'));
        $imageOverlay = $fieldWrapper.siblings('.field-name-field-p-hero-image');

        var $play = Drupal.behaviors.stanfordParagraphPHero.getPlayerButton(event.target.getVideoUrl());

        // Add a click event to hide the hero image and play the video.
        $play.click(function (e) {
          // Mouse has eventPhase 3, keyboard has 2. we only add the mouse
          // event so that a keyboard will navigate the user to the respective
          // YouTube page.
          if (e.eventPhase == 3) {
            e.preventDefault();

            // Dad is the hero image.
            $dad = $(this).parent();
            $dad.hide();
            $dad.siblings('.group-overlay-text').hide();

            // Play and show the video.
            $fieldWrapper.show();
            event.target.playVideo();
          }
        });

        // Prepend the play button to the DOM.
        $imageOverlay.prepend($play);
      }
    },

    /**
     * After vimeo API is loaded, add the play button and listener to iframes.
     */
    vimeoReady: function () {
      $('.field-name-field-p-hero-video iframe[src*="vimeo"]').each(function (i, iframe) {
        var player = new Vimeo.Player($(iframe));

        $fieldWrapper = $($(iframe).closest('.field-name-field-p-hero-video'));
        $imageOverlay = $fieldWrapper.siblings('.field-name-field-p-hero-image');

        var $play = Drupal.behaviors.stanfordParagraphPHero.getPlayerButton($(iframe).attr('src'));

        $play.click(function (e) {
          // Mouse has eventPhase 3, keyboard has 2. we only add the mouse
          // event so that a keyboard will navigate the user to the respective
          // Vimeo page.
          if (e.eventPhase == 3) {
            e.preventDefault();

            // Dad is the hero image.
            $dad = $(this).parent();
            $dad.hide();
            $dad.siblings('.group-overlay-text').hide();

            // Show and play the video.
            $fieldWrapper.show();
            player.play();
          }
        });

        // Prepend the play button to the DOM.
        $imageOverlay.prepend($play);
      });
    },

    /**
     * Get a generic play button link.
     *
     * @param hrefUrl
     *   The url of the given video iframe.
     * @returns {*|HTMLElement}
     *   The A tag element.
     */
    getPlayerButton: function (hrefUrl) {
      return $('<a>', {
        class: 'play-video',
        href: hrefUrl,
        title: Drupal.t('Play Video'),
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
