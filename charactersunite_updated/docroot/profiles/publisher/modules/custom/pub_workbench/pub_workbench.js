(function ($) {

Drupal.behaviors.pubWorkbenchFieldsetSummaries = {
  attach: function (context) {

    $('fieldset.node-form-options', context).drupalSetSummary(function (context) {
      var vals = [];

      $('input:checked', context).parent().each(function () {
        vals.push(Drupal.checkPlain($.trim($(this).text())));
      });

      $('#edit-event option', context).each(function() {
        if ($(this).val() == $(this).parent().val()) {
          vals.push(Drupal.t($.trim($(this).text())));
        }
      });

      return vals.join(', ');
    });
  }
};

})(jQuery);
