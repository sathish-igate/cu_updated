(function($, Drupal) {
  Drupal.behaviors.mediaEditAllModal = {
    attach: function(context, settings) {
      var $cancelBtn = $(".media-edit-all-cancel", context);
      if ($cancelBtn.length !== 0) {
        $cancelBtn.click(function (e) {
          e.preventDefault();
          if (Drupal.CTools.Modal.dismiss) {
            Drupal.CTools.Modal.dismiss();
          }
        })
      }
    }
  }
})(jQuery, Drupal);
