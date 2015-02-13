
(function ($) {
  Drupal.behaviors.contextBreakpoint = {

    width: null,
    height: null,

    attach: function (context, settings) {
      var that = this;

      // Update cookies on each resize.
      $(window).resize(function() {
        that.onResize();
      });

      // Do a first manual cookie update to catch the current width.
      this.onResize();
    },

    // Set the cookie with the context states.
    // Then check if we need to reload.
    onResize: function() {
      var date = new Date();
      date.setTime(date.getTime() + 30*24*60*60*1000);

      var expires = date.toGMTString();

      $window = $(window);

      var value = this.setCookie();
      var existing_cookie = '';
      if ($.cookie('context_breakpoint')) {
        existing_cookie = $.cookie('context_breakpoint');
      }

      // Set cookie for contexts.
      document.cookie = 'context_breakpoint=' + value + '; expires=' + expires + '; path=/';

      // If the cookie has changed, then we need to reload.
      if ($.cookie('context_breakpoint') !== existing_cookie) {
        this.doReload();
      }
    },

    doReload: function() {
      window.location.reload(true);

      // FF prevents reload in onRsize event, so we need to do it
      // in a timeout. See issue #1859058
      if ('mozilla' in $.browser)  {
        setTimeout(function() {
          window.location.reload(true);
        }, 10);
      }
    },

    setCookie: function() {
      if (!('context_breakpoint' in Drupal.settings)) {
        return '';
      }
      var settings = Drupal.settings.context_breakpoint;
      var $window = $(window);
      var cookie = {};
      var match;

      // Test whether each context is active given the current window
      // properties, then build the cookie to store the active contexts.
      for (var key in settings) {
        match = true;
        for (var cmd in settings[key]) {
          var value = settings[key][cmd];
          var active = this.checkCondition(cmd, $window.width(), $window.height(), value);
          if (!active) {
            match = false;
            break;
          }
        }
        if (match) {
          cookie[key] = true;
        }
      }
      return JSON.stringify(cookie);
    },

    checkCondition: function(condition, width, height, value) {
      var flag = null;

      switch (condition) {
        case 'width':
          flag = width === value;
          break;

        case 'min-width':
          flag = width >= value;
          break;

        case 'max-width':
          flag = width <= value;
          break;

        case 'height':
          flag = height === value;
          break;

        case 'min-height':
          flag = height >= value;
          break;

        case 'max-height':
          flag = height <= value;
          break;

        case 'aspect-ratio':
          flag = width / height === value;
          break;

        case 'min-aspect-ratio':
          flag = width / height >= value;
          break;

        case 'max-aspect-ratio':
          flag = width / height <= value;
          break;

        default:
          break;
      }

      return flag;
    }
  };
})(jQuery);
