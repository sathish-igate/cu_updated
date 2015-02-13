(function($) {

  Drupal.admin = Drupal.admin || {};
  Drupal.admin.behaviors = Drupal.admin.behaviors || {};

  /**
   * Bind a click handler to #preview-site to return the
   * sps_condition_preview_form.
   */
  Drupal.admin.behaviors.pubSpsPreviewSite = function (context, settings, $adminMenu) {
    var $spsConditionPreviewForm1 = $('#pub-sps-sps-condition-preview-form-alias', context);
    var $spsConditionPreviewForm2 = $('#sps-condition-preview-form', context);
    var $spsPreviewSiteToggle = $('#preview-site');

    if (($spsConditionPreviewForm1.length || $spsConditionPreviewForm2.length) == 0) {
      var base = "preview-site";
      var element = $("#preview-site");
      var element_settings = {};
      element_settings.url = "/pub_sps/sps_condition_preview_form";
      element_settings.wrapper = "toolbar";
      element_settings.event = "click";

      new Drupal.ajax(base, element, element_settings);
    }
    else if ($spsPreviewSiteToggle != 0) {
      $spsPreviewSiteToggle.click(function (e) {
        e.preventDefault();
        $('.page-iib').toggle();
      });
    }
  };

  /**
   * Unbind the click handler after we have pulled in the forms. Then
   * toggle it back and forth so we don't request anymore new forms.
   */
  Drupal.behaviors.pubSpsPreviewSite = {
    attach: function (context, settings) {
      // Passing context caused this to not work so make sure to test if added.
      var $spsPreviewSiteToggle = $('#preview-site');
      var $spsConditionPreviewForm1 = $('#pub-sps-sps-condition-preview-form-alias', context);
      var $spsConditionPreviewForm2 = $('#sps-condition-preview-form', context);

      if (($spsConditionPreviewForm1.length || $spsConditionPreviewForm2.length) != 0){
        $spsPreviewSiteToggle.unbind();
        $spsPreviewSiteToggle.click(function (e) {
          e.preventDefault();
          $('.page-iib').toggle();
        });
      }
    }
  };

})(jQuery);
