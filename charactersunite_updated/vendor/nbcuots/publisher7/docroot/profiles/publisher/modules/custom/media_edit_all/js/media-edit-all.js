(function($, Drupal) {
  Drupal.behaviors.mediaEditAll = {
    url: '/admin/content/file/media-edit-all/ajax/',
    button: false,
    $mediaWrapper: null,
    getFids: function () {
      var fids = [];
      var $media_items = $('.media-item', Drupal.behaviors.mediaEditAll.$mediaWrapper);
      $.each($media_items, function (i, val) {
        fids.push($(val).data('fid'));
      })
      return fids;
    },
    getUrl: function() {
      return Drupal.behaviors.mediaEditAll.url + Drupal.behaviors.mediaEditAll.getFids().join(" ");
    },
    attach: function(context, settings) {
      // We need to do a "start with" selector because drupal will change the ID
      // every new ajax request :-/.
      if (!context || typeof(context.attr) !== 'function' || !context.attr('id').match(/^edit-field-media-items.*ajax-wrapper/) || !context.length) {
        return;
      }
      if (this.getFids().length >=2) {
        // 1st we must add our "Edit All" button.
        $editAll = $('<a class="media-edit-all button ctools-use-modal" id="media-edit-all-button">').text(Drupal.t('Edit All'));
        $('.multi-browse', context).after($editAll);
        // Always add the new fids.
        $editAll.attr('href', Drupal.behaviors.mediaEditAll.getUrl());
      }
    }
  }
})(jQuery, Drupal);
