/**
 * Drupal behaviors to initialize the Backbone applications to handle
 * the unified navigation bar tray.
 *
 * This requires the Backbone application classes to be defined first.
 */

(function (Drupal, $, _) {

  var reportPath = Drupal.settings.basePath + 'admin/structure/personalize/manage/acquia-lift-placeholder/report';
  var statusPath = Drupal.settings.basePath + 'admin/structure/personalize/manage/acquia-lift-placeholder/status';

  Drupal.behaviors.acquiaLiftPersonalize = {
    attach: function (context) {
      var settings = Drupal.settings.personalize;
      var ui = Drupal.acquiaLiftUI;
      var addedCampaigns = {};
      var activeCampaign = '';

      if (settings) {
        // Build models for campaigns that don't have them yet.
        if (!ui.collections.campaigns) {
          ui.collections.campaigns = new ui.MenuCampaignCollection([]);
        }
        Drupal.acquiaLiftUI.utilities.looper(settings.campaigns, function (obj, key) {
          var currentModel = ui.collections.campaigns.findWhere({name: obj.name});
          if (currentModel) {
            for (var prop in obj) {
              if (obj.hasOwnProperty(prop)) {
                currentModel.set(prop, obj[prop]);
              }
            }
          } else {
            var model = Drupal.acquiaLiftUI.factories.MenuFactory.createCampaignModel(obj);
            ui.collections.campaigns.add(model);
            addedCampaigns[obj.name] = model;
          }
        });

        // Clear the variations for all page variation campaigns.
        ui.collections.campaigns.each(function (model) {
          if (model instanceof Drupal.acquiaLiftUI.MenuCampaignABModel) {
            model.get('optionSets').resetVariations();
          }
        });
        Drupal.acquiaLiftUI.utilities.looper(settings.option_sets, function (obj, key) {
          if (!obj.hasOwnProperty('removed')) {
            var campaignModel = ui.collections.campaigns.findWhere({name: obj.agent});
            if (campaignModel) {
              var optionSets = campaignModel.get('optionSets');
              var optionSet = optionSets.findWhere({'osid': key});
              // Merge doesn't work in this case so we need to manually merge.
              if (optionSet) {
                for (var prop in obj) {
                  if (obj.hasOwnProperty(prop)) {
                    optionSet.set(prop, obj[prop]);
                  }
                }
              } else {
                optionSets.add(new Drupal.acquiaLiftUI.MenuOptionSetModel(obj));
              }
            }
          }
        });

        // Create a model for page variation management state
        if (!ui.models.pageVariationModeModel) {
          ui.models.pageVariationModeModel = new ui.MenuPageVariationModeModel();
        }

        // Create the menu view to handle general show/hide functionality for
        // whole menu sections.
        if (!ui.hasOwnProperty('menuView')) {
          var menu = $('.navbar-tray-acquia-lift', context).get(0);
          ui.menuView = new ui.MenuView({
            collection: ui.collections.campaigns,
            el: menu
          });
        }

        // Initialize the executor preview view functionality.
        if (!ui.views.previewView) {
          ui.views.previewView = new Drupal.acquiaLiftUI.MenuVariationPreviewView({'collection': ui.collections.campaigns});
        }

        // Process the Campaigns, Content Variations and Goals top-level links
        // in the Acquia Lift menu.
        // This is processing that runs only once for the lifetime of the page.
        _.each(['campaigns', 'option_sets', 'goals'], function (category) {
          $('[data-acquia-lift-personalize="' + category + '"]').once('acquia-lift-personalize-menu-controls').each(function (index, item) {
            // Option menus.
            var $link = $(item);
            var type = $link.data('acquia-lift-personalize');
            var $controls = $link.closest('li').removeClass('leaf').addClass('expanded');
            var $element, collection;
            // Load the preview assets.
            if (($controls.once('acquia-lift')).length) {
              $controls.children('ul')
                .addClass(['acquia-lift-' + type.replace('_', '-'), 'menu'].join(' '))
                .attr('data-acquia-lift-personalize-type', type);
            }
            // Attach a view that will report the number of campaigns
            // if this link is in the Navbar.
            if ($link.closest('.navbar-tray').length) {
              switch (category) {
                case 'campaigns':
                  collection = ui.collections[category];
                  // Create the view to show the selected name.
                  ui.views.push(new ui.MenuCampaignsView({
                    el: $link,
                    collection: collection
                  }));
                  if (collection.length == 0) {
                    // There are no campaigns.
                    element = document.createElement('li');
                    ui.views.noCampaignsView = new ui.MenuCampaignView({
                      el: element,
                      model: null
                    });
                    $('[data-acquia-lift-personalize-type="campaigns"]').prepend(element);
                  }
                  else {
                    // Create a new ul element to hold the list of campaigns so
                    // they can scroll independently of the "Add campaign"
                    // link.
                    var $menu = $('[data-acquia-lift-personalize-type="campaigns"]');
                    var scrollable = document.createElement('ul');
                    scrollable.className += "menu acquia-lift-scrollable";
                    $menu.wrap('<div class="menu-wrapper">').before(scrollable);
                  }
                  break;
                case 'option_sets': {
                  Drupal.acquiaLiftUI.views.variationSetsMenuView = new Drupal.acquiaLiftUI.MenuContentVariationsMenuView({
                    campaignCollection: ui.collections.campaigns,
                    el: $link[0]
                  });
                  $element = $(Drupal.theme('acquiaLiftPageVariationToggle'));
                  ui.views.pageVariationToggle = new ui.MenuPageVariationsToggleView({
                    model: ui.models.pageVariationModeModel,
                    campaignCollection: ui.collections.campaigns,
                    el: $element.get(0)
                  });
                  $link.wrap('<div class="navbar-box">');
                  $link.addClass('navbar-menu-item');
                  $link.after($element);
                }
              }
            }
          });
        });

        // Add the "Add a goal" functionality.
        $('.acquia-lift-goals-new').once('acquia-lift-personalize-menu-add-goal', function() {
          ui.views.push(new ui.MenuGoalAddView({
            el: this
          }))
        });

        // Add an option set count view for each newly added campaign model.
        $('[data-acquia-lift-personalize="option_sets"]').each(function (index, item) {
          var $link = $(item);
          if ($link.closest('.navbar-tray').length) {
            _.each(addedCampaigns, function (campaignModel, key) {
              // Add an empty count for each campaign's set of options.
              var $element = $(Drupal.theme('acquiaLiftCount'));
              ui.views.push((new ui['MenuContentVariationsCountView']({
                el: $element.get(0),
                model: campaignModel
              })));
              $element.prependTo($link);
            });
          }
        });

        // Add a goals count view for each newly added campaign model.
        $('[data-acquia-lift-personalize="goals"]').each(function (index, item) {
          var $link = $(item);
          if ($link.closest('.navbar-tray').length) {
            // Loop through the campaigns and add an empty count for each one.
            _.each(addedCampaigns, function (campaignModel, key) {
              var $element = $(Drupal.theme('acquiaLiftCount'));
              ui.views.push((new ui['MenuGoalsCountView']({
                el: $element.get(0),
                model: campaignModel
              })));
              $element.prependTo($link);
            });
          }
        });

        // Remove any empty campaign views if the campaigns are now populated.
        if (ui.collections.campaigns.length > 0 && ui.views.hasOwnProperty('noCampaignsView')) {
          ui.views.noCampaignsView.remove();
        }

        // Build Views for contents of the Campaigns, Content Variations and Goals
        // top-level links in the Acquia Lift menu.
        _.each(['campaigns', 'option_sets'], function (category) {
          var $typeMenus = $('[data-acquia-lift-personalize-type="' + category + '"]');
          var $scrollable = $typeMenus.siblings('.acquia-lift-scrollable');
          var campaignsWithOptions = {};
          var viewName = null;
          if ($typeMenus.length) {
            $typeMenus
              .each(function (index, element) {
                var $menu = $(element);
                var type = $menu.data('acquia-lift-personalize-type');
                var model, element, campaignName, campaignModel, optionSets;
                var $holder = $scrollable.length > 0 ? $scrollable : $menu;
                Drupal.acquiaLiftUI.utilities.looper(settings[type], function (obj, key) {
                  // Find the right model.
                  switch (type) {
                    case 'option_sets':
                      // If the menu already has a link for this setting, abort.
                      if (!$menu.find('[data-acquia-lift-personalize-agent="' + obj.agent + '"][data-acquia-lift-personalize-id="' + key + '"].acquia-lift-preview-page-variation').length) {
                        campaignName = obj.agent;
                        campaignsWithOptions[obj.agent] = obj.agent;
                        campaignModel = ui.collections.campaigns.findWhere({'name': campaignName});
                        if (campaignModel) {
                          optionSets = campaignModel.get('optionSets');
                          model = optionSets.findWhere({'osid': key});
                          viewName = 'MenuOptionView';
                        } else {
                          model = optionSets = viewName = null;
                        }
                      }
                      break;
                    case 'campaigns':
                      // If the menu already has a link for this setting, abort.
                      if (!$menu.find('[data-acquia-lift-personalize-agent="' + key + '"].acquia-lift-campaign').length) {
                        campaignName = key;
                        campaignModel = model = ui.collections[type].findWhere({'name': key});
                        viewName = 'MenuCampaignView';
                      }
                      break;
                  }
                  // Create views for the campaign model if it was just added.
                  if (model && addedCampaigns.hasOwnProperty(campaignName)) {
                    element = document.createElement('li');
                    if (type == 'campaigns') {
                      ui.views.push(new ui.MenuCampaignView({
                        el: element,
                        model: model
                      }));
                    } else {
                      ui.views.push(ui.factories.MenuFactory.createContentVariationView(model, campaignModel, element));
                    }

                    $holder.prepend(element);

                    // Build a view for campaign goals.
                    if (type === 'campaigns') {
                      var $goalsMenu = $('[data-acquia-lift-personalize-type="goals"]');
                      element = document.createElement('li');
                      var goalsView = new ui.MenuGoalsView({
                        model: model,
                        el: element
                      });

                      ui.views.push(goalsView);
                      $goalsMenu.prepend(goalsView.el);
                    }
                  }
                });

                if (category === 'option_sets') {
                  Drupal.acquiaLiftUI.utilities.looper(settings.campaigns, function (obj, key) {
                    if (addedCampaigns.hasOwnProperty(key) && !campaignsWithOptions.hasOwnProperty(key)) {
                      // Add a content variations view for any campaigns that don't have existing
                      // option sets (and therefore would have been missed).
                      model = ui.collections.campaigns.findWhere({'name': key});
                      element = document.createElement('li');
                      ui.factories.MenuFactory.createEmptyContentVariationView(model, element);
                      $menu.prepend(element);
                    }
                  })
                }
              });
          }
        });

        // Build Views for all content variations within the campaign.
        var $contentVariations = $('[data-acquia-lift-personalize-agent].acquia-lift-content-variation').once('acquia-lift-personalize-option-sets');
        if ($contentVariations.length) {
          $contentVariations
            .each(function (index, element) {
              var $group = $(element);
              var campaign = $group.data('acquia-lift-personalize-agent');
              var model = ui.collections['campaigns'].findWhere({'name': campaign});
              ui.views.push((new ui.MenuContentVariationsView({
                el: $group.closest('li').get(0),
                model: model
              })));
            });
        }

        // Create View for the Report link.
        if (ui.collections.campaigns.length > 0) {
          $('[href="' + reportPath + '"]')
            .once('acquia-lift-personalize-report')
            .each(function (index, element) {
              ui.views.push((new ui.MenuReportsView({
                el: element.parentNode,
                model: ui.collections['campaigns'],
                collection: ui.collections['campaigns']
              })));
            });
        } else {
          $('[href="' + reportPath + '"]').hide();
        }

        // Create a View for the Status link.
        if (ui.collections.campaigns.length > 0) {
          $('[href="' + statusPath + '"]')
            .once('acquia-lift-personalize-status')
            .each(function (index, element) {
              ui.views.push(new ui.MenuStatusView({
                el: element.parentNode,
                model: ui.collections['campaigns'],
                collection: ui.collections['campaigns']
              }));
            });
        } else {
          $('[href="' + statusPath + '"]').hide();
        }

        // Refresh event delegation. This is necessary to rebind event delegation
        // to HTML that's been moved inside a jQuery dialog.
        _.each(ui.views, function (view) {
          view.delegateEvents();
        });
        // Refresh the model data for option sets.
        ui.collections.campaigns.each(function (campaignModel) {
          campaignModel.refreshData();
        });
        if (!ui.collections['campaigns']) {
          return;
        }

        // Update the active campaign.
        // If it was just added and is set as the active campaign then it takes
        // priority over a campaign that was previously set as active.
        if (addedCampaigns.hasOwnProperty(settings.activeCampaign)) {
          activeCampaign = settings.activeCampaign;
        } else {
          // Use the current if set, otherwise read from settings.
          var current = ui.collections['campaigns'].findWhere({'isActive': true});
          if (current) {
            activeCampaign = current.get('name');
          } else {
            activeCampaign = settings.activeCampaign;
          }
        }
        // Make sure the activeCampaign requested is available on this page.
        var current = ui.collections['campaigns'].findWhere({'name': activeCampaign});
        if (!current || !current.includeInNavigation()) {
          activeCampaign = '';
        }

        Drupal.acquiaLiftUI.setActiveCampaign(activeCampaign);
        Drupal.acquiaLiftUI.utilities.setInitialized(true);
        Drupal.acquiaLiftUI.utilities.updateNavbar();
      }
    }
  };

  Drupal.behaviors.acquiaLiftContentVariations = {
    attach: function (context) {
      var ui = Drupal.acquiaLiftUI;
      // Create a model for a Content Variation management state.
      if (!ui.models.contentVariationModeModel) {
        ui.models.contentVariationModeModel = new ui.MenuContentVariationModeModel();
      }
      // Create a model for page variation management state
      if (!ui.models.pageVariationModeModel) {
        ui.models.pageVariationModeModel = new ui.MenuPageVariationModeModel();
      }

      // Keep the in-context content variation editing, page variation editing,
      // and in-context goal creation in mutually exclusive active states.
      $('body').once('acquia-lift-personalize', function () {
        // Turn off content variations highlighting if visitor actions editing
        // is enabled.
        $(document).bind('visitorActionsUIEditMode', function (event, isActive) {
          if (isActive) {
            // Prevent infinite loops of updating models triggering change events
            // by delaying this update to the next evaluation cycle.
            _.delay(function () {
              ui.models.contentVariationModeModel.endEditMode();
              ui.models.pageVariationModeModel.endEditMode();
            });
          }
        });
        // Signal when content variation highlighting is active.
        ui.models.contentVariationModeModel.on('change:isActive', function (model, isActive) {
          if (isActive) {
            _.delay(function() {
              $(document).trigger('visitorActionsUIShutdown');
              ui.models.pageVariationModeModel.endEditMode();
            });
          }
        });
        // Turn off content variation and visitor actions modes when entering
        // page variation mode.
        $(document).bind('acquiaLiftPageVariationMode', function (event, data) {
          if (data.start) {
            _.delay(function() {
              ui.models.contentVariationModeModel.endEditMode();
              $(document).trigger('visitorActionsUIShutdown');
            });
          }
        });
      });

      // Build Views for the Add Content Variation triggers.
      $('[data-acquia-lift-personalize-mode="content-variation"]')
        .once('acquia-lift-personalize-trigger')
        .each(function (index, element) {
          ui.views.push((new ui.MenuContentVariationTriggerView({
            el: element,
            contentVariationModel: ui.models.contentVariationModeModel,
            pageVariationModel: ui.models.pageVariationModeModel,
            campaignCollection: ui.collections.campaigns
          })));
        });
      // Find content variation candidates.
      $('[data-personalize-entity-id]')
        .once('acquia-lift-personalize-variation-candidate')
        .each(function (index, element) {
          ui.views.push((new ui.MenuContentVariationCandidateView({
            el: element,
            model: ui.models.contentVariationModeModel
          })));
        });
    }
  };

}(Drupal, Drupal.jQuery, _));
