;(function($, undefined) {
  Drupal.behaviors.mediaMultiselect = {
    attach: function(context, settings) {
      for (var base in settings.ajax) {
        var element_settings = settings.ajax[base];
        if (element_settings.event == 'media_select' && !$('#' + base + '.media-multiselect-processed').length) {
          $('#' + base).show();
          // Bind a click-event to the 'add more' button.
          $('#' + base).click((function(element) { return function(event) {
            var media_settings = settings.media.multi_select.elements[element];

            // Add a new beforeSerialize that adds in our fids.
            Drupal.ajax[element].beforeSerialize = function(element, options) {
              // Add the fids to the form_values.
              $(this.media_multiselect_files).each(function() {
                options.data['media_multiselect_fids[' + this.fid + ']'] = this.fid;
              });

              // Call the prototype, so we preseve any existing functionality in there.
              Drupal.ajax.prototype.beforeSerialize.call(this, element, options);
            };

            var wrapper = $(this).closest('div.form-wrapper');
            // Launch the Media Browser.
            Drupal.media.popups.mediaBrowser(function(files) {
              Drupal.ajax[element].media_multiselect_files = files;
              for (var i = 0; i < files.length; i++) {
                var button = wrapper.find('.multi-browse').first();
                var uploadField = button.siblings('.upload');

                // Set the value of the hidden file ID field and trigger a change.
                uploadField.val(files[i].fid);
                uploadField.trigger('change');

                // Find the attach button and automatically trigger it.
                var attachButton = uploadField.siblings('.attach');
                Drupal.ajax[attachButton.attr('id')].options.async = false;
                attachButton.trigger('mousedown');
              }
            }, media_settings.global);

            // Aaaand prevent default.
            event.preventDefault();
          }})(base));

          $('#' + base).addClass('media-multiselect-processed');
        }
      }
    }
  };
})(jQuery);
