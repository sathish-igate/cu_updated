
(function (window, $, Drupal) {

  Drupal.behaviors.pub_mpx_video_media_browser = {

    attach: function (context) {
      // The passed in context was removed from the following function.
      // Passing in the context on Ajax calls caused the click() function
      // to not be applied.
      
      var media_browser_view_name = Drupal.settings.media.browser.pub_mpx_video.view_name;

      $('.view-id-' + media_browser_view_name + ' table tr')
          .filter(':not(:first)')
          .click(function () {

            selected_element = $(this);

            selected_element.parent().children().each(function () {
              $(this).removeClass('selected');
            });
            selected_element.addClass('selected');

            // Use the selected img for the preview. Also this is a hack :-(
            // The thumbnail image is too damn big! I can't do it with css because
            // the css is not loaded on the page on the original load.
            thumbnail_image = $('img', selected_element).css('width', '100px');
            video_title = $('.views-field-title', selected_element);

            file_json = $(this).find('td.views-field-fid').text();
            file_data = $.parseJSON(file_json);
            file_data.preview = thumbnail_image.length > 0 ? thumbnail_image : video_title;
            Drupal.media.browser.selectMedia([ file_data ]);
          });
    }
  };

}(this, this.jQuery, this.Drupal));
