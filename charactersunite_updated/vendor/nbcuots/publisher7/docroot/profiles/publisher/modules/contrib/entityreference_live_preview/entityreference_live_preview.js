(function($) {
  Drupal.behaviors.entityreferenceLivePreview = {
    attach: function (context, settings) {
      $('.entityreference-live-preview-container', context).once('entityreference-live-preview').bind('focusout change', function() {
        var container = $(this);
        var element = container.find('input[type=text]');
        var classList = container.attr('class').split(/\s+/);
        var callback;
        $.each(classList, function(index, item) {
          if (item.match(/^entityreference-live-preview-id-/)) {
            var itemSettings = settings.entityreference_live_preview[item];
            callback = itemSettings.callback;
          }
        });
        var matches = element.val().match(/\((\d+)\).?$/);
        if (matches) {
          var targetId = matches[1];

          var path = callback + '/' + targetId;
          $.get(path, function (data) {
            container.find('.entityreference-live-preview').html(data);
          });
        } else {
          container.find('.entityreference-live-preview').html('');
        }
      });
    }
  };
})(jQuery);
