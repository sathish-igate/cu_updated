/**
 * Surf session.
 */
(function($) {
  'use strict';

  var useLocalStorage = (function() {
    try {
      return 'localStorage' in window && window['localStorage'] !== null;
    }
    catch (e) {
      return false;
    }
  })();

  Drupal.session = function() {
    var data = null;
    var storage = (useLocalStorage ? $.localStorage : $.cookieStorage);
    var _sess = storage.get('surf')
    if (_sess !== null) {
      data = _sess;
    }

    return {
      load: function() {
        return data;
      },
      get: function() {
        if (data === null) {
          return data;
        }
        return {
          uid: data._id,
          signature: data._auth_signature
        }
      },
      set: function(user) {
        data = user;
        storage.set('surf', data);
      },
      remove: function() {
        data = null;
        storage.remove('surf')
      }
    }
  }

})(jQuery);
