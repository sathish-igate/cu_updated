(function (window, $, Drupal) {
  "use strict";
  Drupal.behaviors.pub_thePlatform = {
    attach: function (context) {

      function bindClicks() {

        var pub_theplatform_media_browser_tab = $('#media-tab-pub_theplatform', context);

        $('.view-id-' + Drupal.settings.media.browser.pub_theplatform.pub_theplatform_view_id + ' table tr', pub_theplatform_media_browser_tab).filter(':not(:first)').once('theplatform_click', function () {
          $(this).click(function () {

            var selected_element = $(this);
            var guid = $.trim(selected_element.find('.views-field-guid').text()).replace(/^[-a-zA-Z]*(\d+)[-a-zA-Z]*$/, '$1');

            selected_element.parent().children().each(function () {
                $(this).removeClass('selected');
            });
            selected_element.addClass('selected');

            // Use the selected img for the preview. Also this is a hack :-(
            // The thumbnail image is too damn big! I can't do it with css because
            // the css is not loaded on the page on the original load.
            var thumbnailImage = $('img', selected_element).css('width', '100px');

            // Setting the media here prevents a rather obtrusive JS alert from
            // appearing telling the user they have not selected anything.
            $.getJSON(Drupal.settings.media.browser.pub_theplatform.theplatform_info_api + guid, function (data, textStatus) {
              if (textStatus === 'success') {
                // Inject our img into the preview property.
                data.preview = thumbnailImage;
                Drupal.media.browser.selectMedia([data]);
              }
            });
          });
        });

        $('.form-actions .fake-submit', pub_theplatform_media_browser_tab).click(function () {

          // If for some reason the selected media hasn't been set, try again
          // before submitting the form.
          if (Drupal.media.browser.selectedMedia.length < 1) {
            var guid = $.trim(pub_theplatform_media_browser_tab.find('.selected').first().find('.views-field-guid').text()).replace(/^[-a-zA-Z]*(\d+)[-a-zA-Z]*$/, '$1');
            var thumbnailImage = $('.selected img', pub_theplatform_media_browser_tab).css('width', '100px');
            $.getJSON(Drupal.settings.media.browser.pub_theplatform.theplatform_info_api + guid, function (data, textStatus) {
              if (textStatus === 'success') {
                data.preview = thumbnailImage;
                Drupal.media.browser.selectMedia([data]);
                Drupal.media.browser.submit();
              }
            });
            // We don't want to actually trigger the submit yet.
            return false;
          }
        });
      }
      bindClicks();

      $(window.document).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
        if (ajaxOptions.url.indexOf('views/ajax') > -1) {
          bindClicks();
        }
      });
    }
  };
}(this, this.jQuery, this.Drupal));
