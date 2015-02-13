(function ($) {

    /**
     * Update the summary for the module's vertical tab.
     *
     * @todo Make this work with all social fieldsets.
     */
    Drupal.behaviors.vertical_tabs_exampleFieldsetSummaries = {
        attach: function (context) {
            // Use the fieldset ID to identify the vertical tab element
            $('#twitter', context).drupalSetSummary(function (context) {
                // Set the text of the vertical tab summary.
                if ($("[id^=edit-twitter-enabled]", context).attr('checked')) {
                    return Drupal.t('Active');
                }
                else {
                    return Drupal.t('Not active');
                }
            });

            $('#facebook', context).drupalSetSummary(function (context) {
                // Set the text of the vertical tab summary.
                if ($("[id^=edit-facebook-enabled]", context).attr('checked')) {
                    return Drupal.t('Active');
                }
                else {
                    return Drupal.t('Not active');
                }
            });
        }
    };

})(jQuery);
