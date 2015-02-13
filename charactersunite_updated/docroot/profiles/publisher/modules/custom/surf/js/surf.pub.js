(function($) {
  'use strict';

  /**
   * Drupal Surf object.
   */
  Drupal.surf = {
    debug: false,
    session: null,
    events: {
      sessionReady: 'onSessionReady',
      ready: function (e) {
        Drupal.surf.session = Drupal.session();
        var user = Drupal.surf.session.load();
        SURF.event.trigger(Drupal.surf.events.sessionReady, [user]);
      },
      signIn: function(e, user) {
        Drupal.surf.session.set(user);
      },
      signInSocial: function(e, user) {
        Drupal.surf.session.set(user);
      },
      createAccount: function(e, user) {
        // Do Account creation, analytics.
      },
      editAccount: function(e, user) {
        Drupal.surf.session.set(user);
      },
      accountUpdated: function(e, user) {
        Drupal.surf.session.set(user);
      },
      error: function(e) {
        // Simple hack for logs.
        if (Drupal.surf.debug) {
          // Set debug to true if you want errors.
          if (typeof console != 'undefined' && 'error' in console && 'trace' in console) {
            console.error("Error: Drupal Surf error: %e", e);
            console.trace();
          }
        }
      }
    }
  };

/**
 * Surf Drupal behavior.
 *
 * Any brand can decide to overwrite this method.
 */
Drupal.behaviors.surfPub = {
    attach: function (context, settings) {
      var element = '#' + settings.surf.element;
      if ($(element).length != 0) {

        // Init Surf
        SURF.init(settings.surf);

        // Bind Surf Events. Leave these in tact so we can handle the session data.
        SURF.event.bind(SURF.events.READY, Drupal.surf.events.ready);
        SURF.event.bind(SURF.events.SIGNIN, Drupal.surf.events.signIn);
        SURF.event.bind(SURF.events.SIGNIN_WITH_SOCIAL_PROVIDER, Drupal.surf.events.signInSocial);
        SURF.event.bind(SURF.events.CREATE_ACCOUNT, Drupal.surf.events.createAccount);
        SURF.event.bind(SURF.events.EDIT_ACCOUNT, Drupal.surf.events.editAccount);
        SURF.event.bind(SURF.events.ACCOUNT_UPDATED, Drupal.surf.events.accountUpdated);

        SURF.event.bind(SURF.events.SIGNIN_ERROR, Drupal.surf.events.error);
        SURF.event.bind(SURF.events.SIGNOUT_ERROR, Drupal.surf.events.error);
        SURF.event.bind(SURF.events.SIGNIN_WITH_SOCIAL_PROVIDER_ERROR, Drupal.surf.events.error);
        SURF.event.bind(SURF.events.CREATE_ACCOUNT_ERROR, Drupal.surf.events.error);
        SURF.event.bind(SURF.events.EDIT_ACCOUNT_ERROR, Drupal.surf.events.error);
        SURF.event.bind(SURF.events.LINK_ACCOUNT_ERROR, Drupal.surf.events.error);
      }
    }
 };

})(jQuery);

