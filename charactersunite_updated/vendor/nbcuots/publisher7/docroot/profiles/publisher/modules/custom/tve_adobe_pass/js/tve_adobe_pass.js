/**
 * @file
 * Adobe Pass javascript API.
 */
;
(function($, window, Drupal) {

  /**
   * @doc module
   * @name tve
   * @description
   * TVE global namespace
   */
  var tve = (window.tve = window.tve || {});

  /**
   * @doc object
   * @name tve.adobePass
   */
  var instance = tve.adobePass || (tve.adobePass = {});

  /**
   * @doc property
   * @name tve.adobePass:exists
   * @type {boolean}
   * @description
   * Use this variable to define if the service is already created.
   */
  instance.exists = false;

  /**
   * @doc function
   * @name tve.adobePass:getInstance
   *
   * @description initiates Adobe Pass service with the provided configuration and returns the service instance.
   *              tve.adobePass is exposed as singleton. getInstance recall returns the previously instantiated instance.
   *
   * @param {Object=} config for new instance.
   * @returns {tve.adobePass.AdobePassConnector} Adobe Pass service instance.
   */
  instance.getInstance = $.proxy(function(config) {

    // tve.adobePass instance is singleton
    if (instance.exists) {
      return instance;
    }
    else {

      // Also extending the origin object(tve.adobePass).
      // So you can use the new reference returned by method or continue using tve.adobePass.
      $.extend(this, new AdobePassConnector(config));
      // Mark service as created.
      this.exists = true;

      // Returns newly created singleton.
      return this;
    }
  }, instance);

  /**
   * @doc function
   * @name tve.adobePass:AdobePassConnector
   * @constructor
   * @param {Object=} config configuration for Adobe Pass service instance.
   * @description
   * ##Default config which can be extended with your options:
   * * `accessEnablerId` - {@type string} Access Enabler swf object id
   * * `mvpdFrameId` - {@type string} MVPD login-iframe id
   * * `adobePassIframeContainerId` - {@type string} MVPD login-iframe container id.
   *                                                 Iframe will be appended to this wrapper.
   * * `authNCheckedSuccessCallback` - {@type function({
   *                                      isAuthenticated: {@type boolean},
   *                                      mvpdId: {@type string | null
   *                                   }})} callback will be fired after AccessEnabler getAuthentication check.
   *                                   It becomes user authentication status object with mvpdId and auth-status.
   * * `authNCheckedFailedCallback` - {@type function} will be fired in case of any error while AccessEnabler processes.
   *                                                   1. embed object creation failed
   *                                                   2. timeout expired before response
   *
   */
  function AdobePassConnector(config) {
    var NONE_URL = 'none',
      EXPIRED_DATE = -1,
      TRUE_FLAG = '1';

    var basePath = (Drupal && Drupal.settings.basePath) || '/',
      noop = function() {},

      /**
       * Analytics obj, uses tveAnalytics if module is enabled.
       * Implements the following interface {
       *   trackMvpdSelected: function({Object=}),
       *   trackPassSignIn: function({Object=}),
       *   trackAuthentication: function({Object=})
       * }
       */
      tveAnalytics = tve.analytics ? {
        trackMvpdSelected: tve.analytics.trackAuthEvents.bind(tve.analytics, tve.analytics.events.MVPD_SELECTED),
        trackPassSignIn: tve.analytics.trackAuthEvents.bind(tve.analytics, tve.analytics.events.PASS_SIGNIN),
        trackAuthentication: tve.analytics.trackAuthEvents.bind(tve.analytics, tve.analytics.events.AUTHN_TRACK)
      } : {
        trackMvpdSelected: noop,
        trackPassSignIn: noop,
        trackAuthentication: noop
      },

      // Default configuration, can be extended by user configuration.
      defaults = {
        accessEnablerId: 'accessEnabler',
        mvpdFrameId: 'mvpdframe',
        adobePassIframeContainerId: 'adobePassIframeContainer',

        authNCheckedSuccessCallback: noop,
        authNCheckedFailedCallback: noop,
        openAdobePassFrame: noop,

        cookie: {
          path: basePath,
          user: 'nbcu_user_settings',
          loginPending: 'nbcu_ap_loginpending',
          adobePassUserGuid: 'instance_user_guid'
        },

        // Using tve.mvpdService with default configuration if it's not overriden.
        mvpdService: tve.mvpdService && tve.mvpdService.getInstance() || {

          // We are assuming getMvpd to return object which implements jQuery Promise API
          getMvpd: function() {
            return $.Deferred().promise();
          }
        },

        logger: {
          useWatchDog: true,
          url: basePath + 'adobe-pass/log',

          // Your custom logger callback.
          log: noop,
          messages: {
            INITIALIZATION_ERROR: Drupal.t('AccessEnabler Initialization Failed'),
            SWF_OBJECT_FAILURE: Drupal.t('swf object creation failed'),
            TIMEOUT: Drupal.t('Adobe Pass authn/authz process could not be completed due to some technical Issue'),
            NON_ENTITLED_MVPD: Drupal.t('User is authenticated with non-entitled MVPD')
          },
          errorLvl: {
            INFO: 'info',
            WARNING: 'warning',
            ERROR: 'error'
          }
        },

        analytics: tveAnalytics
      },

      // tve.adobePass events listener, for pub/sub functionality.
      pubSub = $({}),
      selectedProvider, redirect, authzCallback, metadataStatusCallback, mvpdWindow, aeCheckTimeoutId, accessEnabler;

    // Constructing tve.adobePass instance. Exposing API, embedding swf.
    init.call(this);

    function init() {
      var getUserStatus = function() {
          var userCookie;

          try {
            userCookie = JSON.parse($.cookie(config.cookie.user));
          }
          catch(e) {
            logError({
              errorId: e.name,
              message: e.message
            });
          }

          return userCookie;
        },
        userCookie;

      this.config = config = $.extend(defaults, Drupal.settings.adobePass, config);

      this.ACCESS_ENABLER_ID = config.accessEnablerId;
      this.events = {
        AUTHN_CHECKED: 'authChecked.adobePass'
      };

      // Safely parsing user cookie.
      userCookie = getUserStatus();

      // Exposing user authentication status as global properties. This data can be approved only after
      // getAuthentication in your authNCheckedSuccessCallback, but properties will be also updated by tve.adobePass.
      this.isAuthenticated = userCookie && userCookie.authn;
      this.currentProvider = userCookie && userCookie.selectedProvider;

      // Exposing public methods.
      publishApi(this);

      // Embedding AccessEnabled swg, adding handler.
      // Initialization entry point.
      loadAccessEnabler();
    }

    /**
     * Embeds AccessEnabler swf object into specific container.
     *
     * @param {Object} settings
     *    Configuration object exposed from adobe_pass.module.
     */
    function loadAccessEnabler() {
      var params = {
          menu: 'false',
          quality: 'low',
          AllowScriptAccess: 'always',
          swliveconnect: 'true',
          wmode: 'transparent',
          align: 'middle'
        },
        attributes = {
          id: config.accessEnablerId,
          name: config.accessEnablerId,
          style: "position: fixed; z-index: 9999; display: inline-block; " +
            "visibility: visible; left: 0px !important; top: 0px !important;"
        },
        ACCESS_ENABLER_CONTAINER_ID = 'contentAccessEnabler',
        container = document.createElement('div');
      container.id = ACCESS_ENABLER_CONTAINER_ID;
      
      // Avoids loading access enabler swf file if flash is disabled.
      if (!swfobject.hasFlashPlayerVersion(config.adobePassFlashVer)) {
        config.authNCheckedFailedCallback(false);
        return;
      }

      $(document.body).append(container);

      swfobject.embedSWF(
        // AccessEnabler.swf location.
        config.adobePassAccessEnablerLoc,
        // Container ID to embed AccessEnabled.swf.
        ACCESS_ENABLER_CONTAINER_ID,
        // Object size 1pxx1px.
        1, 1,
        // Minimum flash version.
        config.adobePassFlashVer,
        // XiSwfUrlStr.
        null,
        // Flash variables.
        null,
        // Parameters.
        params,
        // Object attributes.
        attributes,
        // Onload callback.
        accessLoadedCheck
      );
    }

    /**
     * Creates timeout for swf loaded event.
     *
     * Logs an error, if timeout expired before onload event.
     */
    function accessLoadedCheck(status) {

      // Checking for swf object successfull creation
      if (status.success) {

        // Setting timeout for AccessEnabler init process. Timeout is configured via admin. Default is 30seconds.
        aeCheckTimeoutId = setTimeout(function() {
          if (accessEnabler == null) {
            logError({
              message: config.logger.messages.INITIALIZATION_ERROR
            });
          }

          config.authNCheckedFailedCallback(config.logger.messages.TIMEOUT);
        }, config.adobePassTimeoutLength);
      }
      else {
        logError({
          message: config.logger.messages.SWF_OBJECT_FAILURE
        });
        config.authNCheckedFailedCallback(status);
      }
    }

    /**
     * Clears accessLoadedCheck timeout.
     */
    function stopAECheck() {
      if (aeCheckTimeoutId) {
        clearTimeout(aeCheckTimeoutId);
        aeCheckTimeoutId = null;
      }
    }

    /**
     * Initiates the check authentication process on load of the page.
     */
    function initiateCheckAuthProcess() {
      stopAECheck();
      accessEnabler = document.getElementById(config.accessEnablerId);

      // Logging error and exit if AccessEnabler is not found.
      if (accessEnabler == null) {
        logError({
          message: config.logger.messages.INITIALIZATION_ERROR
        });

        return;
      }

      // Enabler configuration.
      accessEnabler.setProviderDialogURL(NONE_URL);
      accessEnabler.setRequestor(config.adobePassRequestorId, null, config.refreshlessConfig);
      accessEnabler.checkAuthentication();

      return this;
    }

    /**
     * Start the authentication flow if no valid authentication token
     * is found in the local shared object.
     */
    function getAuthentication(redirectUrl) {
      redirect = redirectUrl || document.URL || window.location.href;
      accessEnabler.getAuthentication(redirect);

      return this;
    }

    /**
     * Start the authorization flow.
     */
    function getAuthorization(resource, callback) {
      authzCallback = callback;
      accessEnabler.getAuthorization(resource);

      return this;
    }

    /**
     * Checks if the current user has authorization to view the asset.
     *
     * @param {string} resourceID
     * @param {function():} callback
     * @returns {?Object} chains tve.adobePass if called in it's context.
     */
    function checkAuthorization(resourceID, callback) {
      authzCallback = callback;
      accessEnabler.checkAuthorization(resourceID);

      return this;
    }

    /**
     * Performs authentication with the provided MVPD ID.
     * You can pass optional redirectUrl to perform redirect after login process.
     * @param {string } id the MVPD id to authenticate.
     * @param {string=} redirectUrl the optional redirect url to go to after login process.
     *
     * @return {?Object} chains tve.adobePass instance if called in this context.
     */
    function login(id, redirectUrl) {
      getAuthentication(redirectUrl);
      setSelectedProvider(id);

      return this;
    }

    /**
     * Clear all authentication and authorization for the client.
     */
    function logout() {
      _deleteCookie();
      accessEnabler.logout();

      return this;
    }

    /**
     * Set the ID of the selected provider.
     *
     * @param providerId A provider identifier.
     */
    function setSelectedProvider(providerId) {
      var args = {
          'authnStatus': 'Not Authenticated',
          'mvpd_id': providerId
        },
        selectedProviderInfo = config.mvpdService.getMvpd(providerId);

      if (selectedProviderInfo) {
        selectedProviderInfo.then(function(data) {
            if (data['is_new_window'] == TRUE_FLAG) {
              createMVPDWindow();
            }
          }, null)
          .always(setProvider);
      }
      else {
        setProvider();
      }

      function setProvider() {
        aeCheckTimeoutId = setTimeout(function() {
          if (!mvpdWindow) {
            logError({
              message: config.logger.messages.TIMEOUT
            });
          }

          stopAECheck();
        }, config.adobePassTimeoutLength);

        config.analytics.trackMvpdSelected(args);
        $.cookie(config.cookie.loginPending, TRUE_FLAG, {
          expires: 1,
          path: config.cookie.path
        });
        selectedProvider = providerId;
        accessEnabler.setSelectedProvider(providerId);
      }

      return this;
    }

    /**
     * Find the currently selected provider.
     * @return An object with two properties:
     * - MVPD: contains the currently selected provider ID, or null if no MVPD was selected;
     * - AE_State: contains the Access Enabler's current authentication status for the user,
     *             one of 'New User', 'User Not Authenticated' or 'User Authenticated')
     */
    function getSelectedProvider() {
      return accessEnabler.getSelectedProvider();
    }

    /**
     * Perform the post auth check actions.
     */
    function performPostAuthCheckActions(isAuthenticated) {
      var selected = getSelectedProvider();

      isAuthenticated = !!isAuthenticated;

      if (isAuthenticated) {
        // Adding a check to avoid user getting access to the site using shared token for non entitled mvpds.
        config.mvpdService.getMvpd(selected.MVPD)
          .then(function(mvpdConfig) {
            if (mvpdConfig) {
              setAuthCookies(isAuthenticated, selected.MVPD);
              runCallback();
            }
            else {
              trackNonEntitledMvpd();
            }
          }, function(error, status) {
            var errorMsg = status || config.logger.messages.NON_ENTITLED_MVPD;

            if (status) {
              runCallback();
            }
            else {
              trackNonEntitledMvpd();
            }

            logError({message: errorMsg});
          });
      }
      else {
        _deleteCookie();
        
        if (selected.MVPD != null) {
          accessEnabler.setSelectedProvider(null);
        }
        runCallback();
      }

      function runCallback(nonEntitledMvpd) {
        var status;

        instance.isAuthenticated = nonEntitledMvpd ? false : isAuthenticated,
        instance.currentProvider = nonEntitledMvpd ? null : selected.MVPD;

        status = {
          isAuthenticated: instance.isAuthenticated,
          mvpdId: instance.currentProvider
        };

        instance.publish(instance.events.AUTHN_CHECKED, status);
        config.authNCheckedSuccessCallback(status);
      }

      function trackNonEntitledMvpd() {
        logout();
        runCallback(true);
      }
    }

    function setAuthCookies(isAuthenticated, providerId) {
      _setCookie({
        authn: isAuthenticated,
        selectedProvider: providerId
      });
    }

    function cancelAuthentication() {
      var mvpdFrame = document.getElementById(config.mvpdFrameId);
      accessEnabler.setProviderDialogURL(NONE_URL);

      stopAECheck();

      if (accessEnabler.getSelectedProvider().MVPD != null) {
        accessEnabler.setSelectedProvider(null);
      }

      if (mvpdFrame) {
        mvpdFrame.src = 'about:blank';
      }
      mvpdWindow = null;
    }

    /**
     * Creates a iframe from mvpd login screen to load
     */
    function createIframe(width, height) {
      var selected = getSelectedProvider(),
        args = {
          'authnStatus' : 'Not Authenticated',
          'mvpd_id' : selected.MVPD
        };
      // This call needs to be triggered for new window/iframe workflow.
      config.analytics.trackPassSignIn(args);

      // if mvpd is opened in new window
      if (mvpdWindow) {
        mvpdWindow.resizeTo(width,height);
        return false;
      }

      stopAECheck();
      config.openAdobePassFrame();
      create();

      function create() {
        var container = document.getElementById(config.adobePassIframeContainerId),
          iframe = document.getElementById(config.mvpdFrameId);

        // Create the iframe to the specified width and height for the MVPD login page.
        if (!iframe) {
          iframe = document.createElement('iframe');
          iframe.id = iframe.name = config.mvpdFrameId;
          iframe.style.width = width + 'px';
          iframe.style.height = height + 'px';
        }

        container.appendChild(iframe);
        // Force the name into the DOM since it is still not refreshed, for IE.
        window.frames[config.mvpdFrameId].name = config.mvpdFrameId;
      }
    }

    /**
     * Destroy iframe opened for MVPD login.
     */
    function destroyIframe() {
      config.destroyIframe();
    }

    /**
     * MVPD Login screen in a new window rather than iframe workflow.
     */
    function createMVPDWindow() {
      mvpdWindow = window.open(null, config.mvpdFrameId, 'width=300, height=300', true);
      setTimeout(_checkClosed, 200);
    }

    /**
     *  Reopens the mvpd login screen if the user has kept the login screen open
     */
    function reopenMVPDWindow() {
      if (mvpdWindow && !mvpdWindow.closed) {
        mvpdWindow.focus();
        return true;
      }
      else{
        return false;
      }
    }

    /**
     * Watch when the Pop-up window is closed (either by the user or by finishing the authentication flow).
     */
    function _checkClosed() {
      try {
        if (mvpdWindow && mvpdWindow.closed) {
          window.location.href = redirect;
        }
        else {
          setTimeout(_checkClosed, 200);
        }
      }
      catch (error) {

      }
    }

    /**
     * Returns the adobe pass GUID.
     */
    function getUserGuid() {
      return $.cookie(config.cookie.adobePassUserGuid);
    }

    /**
     * Send Tracking Data function implementation
     * @public
     */
    function sendAuthnEvents(trackingEventType, trackingData) {
      var AUTH_DETECTION_EVENT = 'authenticationDetection';

      // Getting the selected mvpd id from tracking data since after authn success page gets reloaded.
      if (trackingData[0] && trackingEventType === AUTH_DETECTION_EVENT) {
        selectedProvider = trackingData[1];
      }
      var args = {'authnStatus' : trackingData[0] ? 'Authenticated' : 'Not Authenticated', 'mvpd_id' : selectedProvider };
      $.cookie(config.cookie.adobePassUserGuid, trackingData[2], { path: config.cookie.path });

      if (trackingEventType === AUTH_DETECTION_EVENT && $.cookie(config.cookie.loginPending) != null) {
        config.analytics.trackAuthentication(args);
        $.cookie(config.cookie.loginPending, '', { expires: EXPIRED_DATE, path: config.cookie.path });
      }
    }

    /**
     * Logs the error message into drupalis watch dog
     */
    function logError(error) {
      var loggerConfig = config.logger;

      error.level = error.level || loggerConfig.errorLvl.ERROR;

      if (error.level == 'info') {
        return false;
      }

      if (loggerConfig.useWatchDog) {
        $.ajax({
          type: 'POST',
          url: loggerConfig.url,
          dataType: 'json',
          data: {
            error: error
          }
        });
      }

      if (typeof loggerConfig.log === 'function') {
        loggerConfig.log(error);
      }

      return error;
    }

    /**
     * Sets adobe cookies.
     *
     * @param input parameters
     */
    function _setCookie(input) {
      $.cookie(config.cookie.user, JSON.stringify(input), {
        path: config.cookie.path
      });
    }

    /**
     * Deletes adobe auth cookies.
     */
    function _deleteCookie() {
      $.cookie(config.cookie.user, '', {
        expires: EXPIRED_DATE,
        path: config.cookie.path
      });
    }

    /**
     * Process the recieved metadata from adobe.
     */
    function processUserMetadata(key, encrypted, data) {
      var callbackFunction = (typeof metadataStatusCallback == 'function') ?
          metadataStatusCallback :
          eval(metadataStatusCallback);

      callbackFunction(key, encrypted, data);
    }

    /**
     * Gets user metadata from adobe.
     */
    function getUserMetadata(key, callback) {
      metadataStatusCallback = callback;
      accessEnabler.getMetadata(key);
    }

    /**
     * implementation for authz success.
     */
    function setToken(requestedResourceID, token) {
      var callbackFunction = (typeof authzCallback == 'function') ? authzCallback : eval(authzCallback);
      callbackFunction(true, {requestedResourceID: requestedResourceID, token: token});
    }

    /**
     * implementation for authz failure.
     */
    function tokenRequestFailed(requestedResourceID, requestErrorCode, requestErrorDetails) {
      var callbackFunction = (typeof authzCallback == 'function') ? authzCallback : eval(authzCallback);

      callbackFunction(false, {
        requestedResourceID: requestedResourceID,
        requestErrorCode: requestErrorCode,
        requestErrorDetails: requestErrorDetails
      });
    }

    /**
     * Publish/subscribe implementation for tve.adobePass obj
     * @returns {tve.adobePass.subscribe}
     */
    function subscribe() {
      pubSub.on.apply(pubSub, arguments);
      return this;
    }

    function unsubscribe() {
      pubSub.off.apply(pubSub, arguments);
      return this;
    }

    function publish() {
      pubSub.trigger.apply(pubSub, arguments);
      return this;
    }

    function publishApi(instance) {
      $.extend(instance, {
        'initiateCheckAuthProcess': initiateCheckAuthProcess,
        'stopAECheck': stopAECheck,
        'createIframe': createIframe,
        'destroyIframe' : destroyIframe,
        'performPostAuthCheckActions': performPostAuthCheckActions,
        'getAuthentication': getAuthentication,
        'login': login,
        'logout': logout,
        'setSelectedProvider': setSelectedProvider,
        'cancelAuthentication': cancelAuthentication,
        'sendAuthnEvents': sendAuthnEvents,
        'reopenMVPDWindow': reopenMVPDWindow,
        'getUserGuid': getUserGuid,
        'getUserMetadata': getUserMetadata,
        'processUserMetadata': processUserMetadata,
        'setToken': setToken,
        'tokenRequestFailed': tokenRequestFailed,
        'getAuthorization': getAuthorization,
        'checkAuthorization': checkAuthorization,
        'logError': logError,
        'subscribe': subscribe,
        'unsubscribe': unsubscribe,
        'publish': publish
      });
    }
  }

  /**
   * Global Callbacks
   */

  /**
   * Called when the Access Enabler is successfully loaded and initialized.
   * This is the entry point for your communication with the AE.
   */
  window.swfLoaded = function() {
    accessEnabler.bind('errorEvent', 'tveAdobePassLogError');
    tve.adobePass.initiateCheckAuthProcess();
  };

  /**
   * Callback that receives the list of available providers for the current requestor ID.
   */
  window.displayProviderDialog = function(providers) {
    tve.adobePass.stopAECheck();
  };

  /**
   * Callback that creates an iFrame to use for login if the MVPD requires it.
   */
  window.createIFrame = function(width, height) {
    tve.adobePass.createIframe(width, height);
  };

  /**
   * accessEnabler `errorEvent` handler
   * @returns {*}
   */
  window.tveAdobePassLogError = function() {
    return tve.adobePass.logError.apply(null, arguments);
  };

  /**
   * Callback that destroys an MVPD's iFrame.
   */
  window.destroyIFrame = function() {
    tve.adobePass.destroyIframe();
  };

  /**
   * Callback that receives the result of a successful authorization token request.
   * Your implementation sets the authorization token.
   */
  window.setToken = function(requestedResourceID, token) {
    tve.adobePass.setToken(requestedResourceID, token);
  };

  /**
   * Callback that indicates a failed authorization token request.
   * @param requestedResourceID The resource ID for which the token request failed.
   * @param requestErrorCode  The error code for the failure.
   * @param requestErrorDetails The custom error message that describes the failure.
   */
  window.tokenRequestFailed = function(requestedResourceID, requestErrorCode, requestErrorDetails) {
    tve.adobePass.tokenRequestFailed(requestedResourceID, requestErrorCode, requestErrorDetails);
  };

  /** Callback that customizes the size of the provided selector dialog. **/
  window.setMovieDimensions = function(width, height) {
    //TODO: Set the dimension for the provider selector.
  };

  /**
   * Callback that indicates the authentication status for the user.
   *  @param isAuthenticated Authentication status is one of 1 (Authenticated) or 0 (Not authenticated).
   *  @param errorCode Any error that occurred when determining the authentication status,
   *                   or an empty string if no error occurred.
   */
  window.setAuthenticationStatus = function(isAuthenticated, errorCode) {
    tve.adobePass.performPostAuthCheckActions(isAuthenticated, errorCode);
  };

  /**
   * Callback that sends a tracking data event and associated data
   *  @param trackingEventType The type of event that triggered this tracking event
   *  @param trackingData An array of all the tracking data/variables associated with the tracking event
   *
   * There are three possible tracking events types:
   *    authorizationDetection    - any time an authorization token request returns
   *    authenticationDetection    - any time an authentication check occurs
   *    mvpdSelection                - when the user selects an mvpd in the mvpd selection dialog
   * trackingData values:
   * For trackingEventType 'authorizationDetection'
   *     [0] Whether the token request was successful [true/false]
   *       and if true:
   *       [1] MVPD ID [string]
   *       [2] User ID (md5 hashed) [string]
   *       [3] Whether it was cached or not [true/false]
   *
   * For trackingEventType 'authenticationDetection'
   *     [0] Whether the token request was successful (false)
   *       and if successful is true:
   *       [1] MVPD ID
   *       [2] User ID (md5 hashed)
   *       [3] Whether it was cached or not (true/false)
   *
   * For trackingEventType 'mvpdSelection'
   *       [0] MVPD ID
   *
   * MVPD Example: MVPD ID for Comcast is 'Comcast'
   */
  window.sendTrackingData = function(trackingEventType, trackingData) {
    tve.adobePass.sendAuthnEvents(trackingEventType,trackingData);
  };

  /**
   * Called when a get-metadata request has completed successfully.
   * Passes back property key for the requested value, an array containing the resource ID for an AuthZ
   * token TTL (or null for any other key), and the property value retrieved from Access Enabler.
   *
   * @param key the Metadata key for which a value has been requested
   * @param encrypted true if value is encrypted
   * @param value the values associated with the Metadata key or null if no value is associated with the key.
   */
  window.setMetadataStatus = function(key, encrypted, value) {
    tve.adobePass.processUserMetadata(key, encrypted, value);
  };

})(jQuery, this, this.Drupal);
