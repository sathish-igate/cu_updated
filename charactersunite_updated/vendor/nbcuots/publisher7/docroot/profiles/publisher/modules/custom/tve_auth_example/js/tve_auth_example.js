/**
 * @file
 * Integration with TVE Auth API.
 */

(function ($) {
  // Lightweight pub/sub pattern implementation via jquery events.
  var o = $({}),
    mvpdService, adobePass;

  $.subscribe = function() {
    o.on.apply(o, arguments);
  };

  $.subscribeOnce = function() {
    o.one.apply(o, arguments);
  };

  $.unsubscribe = function() {
    o.off.apply(o, arguments);
  };

  $.publish = function() {
    o.trigger.apply(o, arguments);
  };

  // Example is not valid if required scripts are not added to the page.
  if (!tve || !tve.adobePass || !tve.mvpdService) return;

  mvpdService = tve.mvpdService.getInstance({
    // Caching MVPDs data to localStorage only for 1 minute in example
    // default value is 1 day.
    cacheTimeout: 60000
  });

  adobePass = tve.adobePass.getInstance({
    authNCheckedSuccessCallback: function(status) {
      console.log(arguments);
      // using your pub/sub implementation
      $.publish(adobePass.events.AUTHN_CHECKED, status);
    },
    // Error callback will be fired after swf load timeout or any adobe pass issues
    authNCheckedFailedCallback: function(error) {
      console.log(arguments);
    },
    // Is called after accessEnabler
    openAdobePassFrame: function() {
      $.publish('openMvpdFrame', status);
    },
    mvpdService: mvpdService
  });

  // you can also subscribe for adobePass events
  adobePass.subscribe(adobePass.events.AUTHN_CHECKED, function(event, status) {
    console.log(event, status);
  });

  // small plugin to highlight the user status
  $.fn.setBooleanColor = function(check) {
    var GREEN = '#0a0',
      RED = '#a00';

    return this.css('color', (check && check !== 'none') ? GREEN : RED);
  };

  // auth module example plugin
  $.fn.mvpdPicker = function() {
    return this.each(function() {
      // caching all selectors
      var $this = $(this),
        $authCancelBtn = $this.find('.authCancelBtn'),
        $loginWrap = $('.loginWrap'),
        $logoutWrap = $('.logoutWrap'),
        $logoutBtn = $('.logoutBtn', $logoutWrap),
        $loginBtn = $('.loginBtn', $loginWrap),
        $featuredMvpdList = $this.find('.featuredMvpds'),
        $allMvpds = $this.find('.allMvpds'),
        $authCheckStatus = $this.find('.authCheckStatus'),
        $isAuthenticatedStatus = $this.find('.authN'),
        $selectedMvpd = $this.find('.selectedMvpd');

      // setting initial data
      // getAuthentication is still in progress
      $authCheckStatus.text('false (loading...)');
      // status set relying on the cookies value
      $isAuthenticatedStatus
        .text(adobePass.isAuthenticated || 'false')
        .setBooleanColor(adobePass.isAuthenticated);
      // status set relying on the cookies value
      $selectedMvpd
        .text(adobePass.currentProvider || 'false')
        .setBooleanColor(adobePass.currentProvider);

      $.subscribeOnce(adobePass.events.AUTHN_CHECKED, function(e, data) {
        // setting real user auth-status returned by AccessEnabler
        $authCheckStatus.text('true').setBooleanColor(true);
        $isAuthenticatedStatus.text(data.isAuthenticated || 'false').setBooleanColor(data.isAuthenticated);
        $selectedMvpd.text(data.mvpdId || 'none').setBooleanColor(data.mvpdId);

        // show logout button for authN user
        (data.isAuthenticated ? $logoutWrap : $loginWrap).show();

        if (data.isAuthenticated) {
          // showing the current mvpd data, fetching it from mvpd admin
          mvpdService.getMvpd(data.mvpdId).then(function(data) {
            $selectedMvpd.append('<pre>' + syntaxHighlight(JSON.stringify(data, undefined, 2)) + '</pre>')
          });
        }
        else {
          // building mvpd-grid for featured and non-featured mvpds
          mvpdService.getMvpd().then(function(data) {
            var featuredMvpdsHtml = [],
              allMvpdsHtml = [];

            // straighforward templating here
            $.each(data.featured, function(index, mvpd) {
              featuredMvpdsHtml.push('<li data-mvpd-id="' + mvpd.mvpd_id + '"><img src="' + mvpd.mvpd_logo + '" /></li>');
            });

            $.each(data.all, function(index, mvpd) {
              allMvpdsHtml.push('<option value="' + mvpd.mvpd_id + '">' + mvpd.title + '</option>');
            });

            $featuredMvpdList.append(featuredMvpdsHtml.join(''));
            $allMvpds.append(allMvpdsHtml.join(''));
          });

          // adding login handlers for featured mvpds
          $featuredMvpdList.on('click.mvpd', 'li', function(e) {
            var $this = $(this);

            e.preventDefault();
            // MVPD id is stored in data attribute
            adobePass.login($this.data('mvpd-id'));
          });
        }

        // JSON syntax highlight-parser
        function syntaxHighlight(json) {
          if (typeof json != 'string') {
            json = JSON.stringify(json, undefined, 2);
          }
          json = json.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');

          return json.replace(/("(\\u[a-zA-Z0-9]{4}|\\[^u]|[^\\"])*"(\s*:)?|\b(true|false|null)\b|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?)/g, function(match) {
            var cls = 'number';
            if (/^"/.test(match)) {
              if (/:$/.test(match)) {
                cls = 'key';
              }
              else {
                cls = 'string';
              }
            }
            else if (/true|false/.test(match)) {
              cls = 'boolean';
            }
            else if (/null/.test(match)) {
              cls = 'null';
            }

            return '<span class="' + cls + '">' + match + '</span>';
          });
        }
      });

      $.subscribe('openMvpdFrame', function() {
        // creating iframe wrapper before login process
        $this.prepend('<div id="' + adobePass.config.adobePassIframeContainerId + '"></div>');

        // adding cancel authentication button handlers
        $authCancelBtn
          .show()
          .one('click.authCancel', function(e) {
            e.preventDefault();

            $authCancelBtn.hide();
            // removing iframe
            $(document.getElementById(adobePass.config.adobePassIframeContainerId)).remove();
            // running accessEnabler.cancelAuthentication
            adobePass.cancelAuthentication();
          });
        });

      $logoutBtn.on('click.logout', function(e) {
        e.preventDefault();

        // Calling adobePass logout, it will reload the page.
        adobePass.logout();
        $logoutBtn.text('Logging out...').prop('disabled', true);
      });

      $loginBtn.on('click.login', function(e) {
        var providerId = $allMvpds.val();

        e.preventDefault();

        if (providerId) {
          adobePass.login(providerId);
        }
      });

    });
  };

  // module initialization
  $(document).ready(function() {
    $('#authExample').mvpdPicker();
  });

})(jQuery);
