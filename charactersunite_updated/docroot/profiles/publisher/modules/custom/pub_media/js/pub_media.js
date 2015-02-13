(function ($) {

  Drupal.behaviors.pubmedia = {
    attach: function (context, settings) {

      // Here we setup functionality so we can link to the 'Edit Image Focus'
      // page/button since it doesn't currently work with a menu_callback and is
      // invoked via JavaScript.

      // Helper function.
      var urlParam = function(name){
        var results = new RegExp('[\\?&]' + name + '=([^&#]*)').exec(window.location.href);
        if (!results) { return 0; }
        return results[1] || 0;
      };

      // Check our parameter and if it is true then activate image focus.
      if (urlParam('image-focus') == 1) {
        $('#image-focus').click();
      }
    }
  };

})(jQuery);
