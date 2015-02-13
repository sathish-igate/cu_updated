/*
 * Detect SVG support using Modernizr lib and fallback to PNG if not supported.
 */
(function ($) {
  $(document).ready(function(){
    if (!Modernizr.svg) {
      $("#logo img").attr("src", "../logo.png");
    }
   });
})(jQuery);
