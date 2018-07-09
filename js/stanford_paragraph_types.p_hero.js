/**
 * @file
 * Applies some functionality on the paragraph types.
 */

var tag = document.createElement('script');
tag.src = 'https://www.youtube.com/iframe_api';
var firstScriptTag = document.getElementsByTagName('script')[0];
firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);

function onYouTubeIframeAPIReady() {
  // After Youtube API is loaded, we can do what we need.
  Drupal.behaviors.stanfordParagraphPHero.youTubeReady()
}

(function ($) {
  Drupal.behaviors.stanfordParagraphPHero = {
    youTubeReady: function () {

      var i = 0;

      $('.field-name-field-p-hero-image').once('youtube', function () {
        var $video = $(this).siblings('.field-name-field-p-hero-video').find('iframe');

        if (!$video.length) {
          return;
        }

        // Gives the video unique ID's and a title.
        $video.attr('id', 'hero-video-' + i)
          .attr('onload', 'this.contentWindow.focus()')
          .attr('title', Drupal.t('Video Player'));

        // Initialze the Youtube api.
        new YT.Player($video.attr('id'), {
          events: {
            'onReady': onPlayerReady,
            'onStateChange': onPlayerStateChange
          }
        });
        i++;
      });

      function onPlayerReady(event) {
        var fieldWrapper = event.target.a.closest('.field-name-field-p-hero-video');
        var imageOverlay = $(fieldWrapper).siblings('.field-name-field-p-hero-image');

        var play = $('<a>', {
          class: 'play-video',
          href: event.target.getVideoUrl(),
          html: $('<i>', {
            class: 'fa fa-youtube-play icon-youtube-play',
            html: 'Play Video',
            'aria-label': Drupal.t('Play Video - Opens to the video website')
          })
        }).click(function (e) {
          // Mouse has eventPhase 3, keyboard has 2.
          if (e.eventPhase == 3) {
            e.preventDefault();
            $dad = $(this).parent();
            $dad.hide();
            $dad.siblings('.group-overlay-text').hide();
            // $(iframe).attr('onload', 'this.contentWindow.focus()');
            event.target.playVideo();
            $(fieldWrapper).show();
          }
        });

        $(imageOverlay).prepend(play);


      }

      function onPlayerStateChange(event) {
        // changeBorderColor(event.data);
      }
    }
  }
})(jQuery);
