
(function ($) {
  /**
   * Event Countdown Drupal behavior.
   *
   * This overrides behavior in jQuery Countdown.
   */
  Drupal.jQueryCountdownEvent = function() {
    var clsname = 'countdown-timer-terminated';
    $(this).closest('.event-countdown').removeClass(clsname).addClass(clsname);

    $.ajax({
      url: Drupal.settings.basePath + 'ajax/jquery-countdown-terminate',
      dataType: 'json',
      success: function(res) {
        // res.response === true
      }
    });
  }
}) (jQuery);
