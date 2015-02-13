;
(function($, window) {
  'use strict';

  var getTimestamp = function() {
    return Date.now ? Date.now() : Number(new Date);
  };

  // LocalStorage wrapper to provide MVPD data cache.
  var appCache = {
    storage: window.localStorage || window.sessionStorage,
    get: function(key) {
      var data;

      try {
        data = JSON.parse(this.storage.getItem(key));
      }
      catch(e) {}

      return data;
    },
    set: function(key, value) {
      try {
        this.storage.setItem(key, JSON.stringify(value));
      }
      catch(e) {}

      return this;
    },
    remove: function(key) {
      var value;

      try {
        value = JSON.parse(this.storage.getItem(key));
        this.storage.removeItem(key);
        return value;
      }
      catch(e) {}

      return value;
    }
  };

  // Safe initialization for global tve.mvpdService namespace
  var tve = (window.tve = window.tve || {}),
    instance = tve.mvpdService || (tve.mvpdService = {exists: false});

  instance.getInstance = $.proxy(function(config) {
    if (instance.exists) {
      return instance;
    }
    else {
      $.extend(this, new MvpdService(config));
      this.exists = true;

      return this;
    }
  }, instance);

  function MvpdService(config) {
    var DEFAULT_PLATFORM_KEY = 'pc',
      mvpdSet = {};

    // creating a closure to store memorized search results
    var getProviderById = (function() {
      var savedProviders = {};

      /**
       * @doc function
       * @description returns provider found by id
       *
       * @param {string} id of the provider
       * @param {string} platformId is a platform id to look for in cache default is `pc`
       *
       * @returns  {Object|null}
       */
      return function getProviderById(id, platformId) {
        var result, platformKey, platformFromMemory, context;

        if (!id) {
          return null;
        }

        result = null;
        platformKey = getPlatformKey(platformId);
        platformFromMemory = savedProviders[platformKey] = savedProviders[platformKey] || {};

        // Returns provider from memory.
        if (result = platformFromMemory[id]) {
          return result;
        }

        context = mvpdSet[platformKey] && mvpdSet[platformKey].all;

        if (!context || !context.length) {
          return null;
        }

        $.each(context, function(index, provider) {

          // mvpd_id is a unique field.
          if (provider.mvpd_id === id) {

            // semorizing found provider
            platformFromMemory[id] = result = provider;
            // stop looping
            return false;
          }
        });

        return result;
      };
    })();

    this.config = config = $.extend({

      path: getBasePath() + 'mvpd',
      // 10 minutes cache valid timeout (in milliseconds).
      cacheTimeout: 600000,
      logError: function() {}

    }, config);

    this.getMvpd = (function() {
      var requestStack = {};

      function loadFromCache(platformConfig) {
        var platformKey = getPlatformKey(platformConfig && platformConfig.platformId),
          platformProviders = mvpdSet[platformKey] = appCache.get(platformKey);

        if (platformProviders && !isCacheValid(platformProviders.timestamp)) {
          appCache.remove(platformKey);
          mvpdSet[platformKey] = null;
        }
      }

      function getMvpd(id, platformConfig) {
        var getFirstIfIdProvided = getSecondIfTrue(id),
          dataKey = getFirstIfIdProvided('all', id),
          pendingRequest = requestStack[dataKey],
          fetchFromMvpdServiceDirectly = Boolean(platformConfig),
          platformMvpdUrl, platformId, providerInfo, platformKey;

        if (fetchFromMvpdServiceDirectly) {
          platformMvpdUrl = platformConfig.url;
          platformId = platformConfig.platformId;
        }
        else {
          platformMvpdUrl = config.path;
        }

        platformKey = getPlatformKey(platformId);
        providerInfo = getFirstIfIdProvided(mvpdSet[platformKey], getFuncWrap(getProviderById, [id, platformId]));

        if (getFirstIfIdProvided(providerInfo && providerInfo.fullList, providerInfo)) {
          return $.when(providerInfo);
        }
        else if (pendingRequest) {
          return pendingRequest;
        }
        else {
          var deferred = $.Deferred(),
            url = platformMvpdUrl + getFirstIfIdProvided('', '/' + id);

          $.get(url).then(function(data) {
              var mvpdData;

              if ('status' in data && !data.status) {
                deferred.reject(data);
              }
              else {
                mvpdData = getFirstIfIdProvided(getFuncWrap(processProviders, [data, platformId]), data.mvpd);
                deferred.resolve(mvpdData);

                if (id) {
                  mvpdSet[platformKey] = mvpdSet[platformKey] || {
                    all: [],
                    fullList: false,
                    timestamp: getTimestamp()
                  };

                  mvpdSet[platformKey].all.push(mvpdData);
                  appCache.set(platformKey, mvpdSet[platformKey]);
                }
                else {
                  mvpdData.timestamp = getTimestamp();
                  mvpdData.fullList = true;
                  appCache.set(platformKey, mvpdData);
                }
              }
            }, function(response) {
              config.logError.apply(config, arguments);
              deferred.reject.apply(deferred, arguments);
            })
            .always(function() {
              delete requestStack[dataKey];
            });

          return requestStack[dataKey] = deferred.promise();
        }
      }

      return function(id, platformConfig) {
        loadFromCache(platformConfig);
        return getMvpd.call(this, id, platformConfig);
      };
    })();

    this.addPlatform = function(config) {
      var self = this;

      this.platforms = this.platforms || {};

      return this.platforms[config.platformId] = this.platforms[config.platformId] || {
        url: config.url,
        getMvpd: function(id) {
          return self.getMvpd(id, config);
        }
      };
    };

    function isFunction(value) {
      return typeof value == 'function';
    }

    function existy(value) {
      return value != null;
    }

    function getFuncWrap(func, args) {
      if (!isFunction(func)) {
        throw new TypeError;
      }

      return function() {
        return func.apply(this, args);
      };
    }

    function getPlatformKey(suffix) {
      var MVPD_LIST_KEY = 'tveMvpdList';

      return [MVPD_LIST_KEY, '.', suffix || DEFAULT_PLATFORM_KEY].join('');
    }

    function getSecondIfTrue(value) {
      return function(options) {
        var result = (arguments.length > 1 ? arguments : options)[Number(existy(value))];
        return isFunction(result) ? result() : result;
      };
    }

    /**
     * @doc function
     * @description Returns base path. Safely parses Drupal.settings or use root '/' path
     * @returns {string}
     */
    function getBasePath() {
      var drupalSettings = (Drupal && Drupal.settings) || {};

      return drupalSettings.basePath || '/';
    }

    /**
     * @doc function
     * @description Compares current timestamp with provided cache timestamp.
     *              Returns true if diff between timestamps is lower than configured timeout
     *
     * @param {number} timestamp cache timestamp
     *
     * @returns {boolean}
     */
    function isCacheValid(timestamp) {
      return getTimestamp() - timestamp < config.cacheTimeout;
    }

    function processProviders(providers, converterId) {
      var push = Array.prototype.push,
        concat = Array.prototype.concat,
        coverters = {
          'false': function(providers) {
            var processedProviders = [];
            // Flatten featured and non-featured arrays with apply with apply.
            push.apply(processedProviders, concat.apply([], [providers.featured, providers.not_featured]));

            // Sorting providers list by titles to display alphabetically sorted in dropdown of all providers.
            // Using Array.prototype.sort.
            processedProviders.sort(alphabeticalSort);

            return {
              all: processedProviders,
              featured: providers.featured
            };
          },
          'true': function(providers) {
            var processedProviders = [],
              featuredProviders = [],
              mappingRules = {
                mvpd: 'mvpd_id',
                title: 'title',
                is_new_window: 'isNewWindow',
                pickerImage: 'mvpd_logo',
                pickerImage_2x: 'mvpd_logo_2x'
              },
              isMvpdFeatured = function(mvpd) {
                // not featured tier is 2
                var FEATURED_MVPD_TIER_VALUE = 1;

                return mvpd.tier === FEATURED_MVPD_TIER_VALUE;
              },
              isFeatured, current;

            providers = providers.mvpdWhitelist;

            for (var i = 0, length = providers.length; i < length; i++) {
              current = providers[i];
              isFeatured = isMvpdFeatured(current);

              current = processObjectFields(current, mappingRules);

              processedProviders.push(current);
              if (isFeatured) {
                featuredProviders.push(current);
              }
            }

            // Sorting providers list by titles to display alphabetically sorted in dropdown of all providers.
            // Using Array.prototype.sort.
            processedProviders.sort(alphabeticalSort);

            return {
              all: processedProviders,
              featured: featuredProviders
            };
          }
        };

      if (!providers) return;

      /**
       * @doc function
       * @description Comparator for Array.sort which sorts object by `title` key
       *              `title` is lowercased before comparison
       *
       * @param {Object} a is the first object in comparison
       * @param {Object} b is the second object in comparison
       *
       * @returns {number}
       */
      function alphabeticalSort(a, b) {
        var aTitleNormalized = a.title.toLowerCase(),
          bTitleNormalized = b.title.toLowerCase();

        if (aTitleNormalized > bTitleNormalized) {
          return 1;
        }
        else if (aTitleNormalized < bTitleNormalized) {
          return -1;
        }
        else {
          return 0;
        }
      }

      /**
       * @doc function
       * @description Processes the object and formates the output
       *
       * @param {Object} obj initial object to be mapped
       * @param {Object} mappingRules mapping rules with the following style {key: value}
       *                 key is the new object key for the value field in the obj
       *
       * @throws {TypeError} if obj is null or undefined
       * @returns {Object}
       */
      function processObjectFields(obj, mappingRules) {
        var mappedResult = {};

        if (!existy(obj)) {
          throw new TypeError;
        }
        for (var key in obj) {
          if (mappingRules.hasOwnProperty(key)) {
            mappedResult[mappingRules[key]] = obj[key];
          }
          else {
            mappedResult[key] = obj[key];
          }
        }

        return mappedResult;
      }

      // Returns object with limited featured mvpd-list and full list of entitled mvpds.
      return providers ? coverters[existy(converterId)](providers) : undefined;
    }
  }

})(jQuery, this);
