/**
 * The basic backbone application components for the unified navigation bar
 * tray.
 */
(function (Drupal, $, _, Backbone) {

  var startPath = Drupal.settings.basePath + 'admin/structure/acquia_lift/start/';

  /**
   * Returns the Backbone View of the Visitor Actions add action controller.
   *
   * @return Backbone.View
   */
  function getVisitorActionsAppModel () {
    return Drupal.visitorActions && Drupal.visitorActions.ui && Drupal.visitorActions.ui.models && Drupal.visitorActions.ui.models.appModel;
  }

  /**
   * Common view functionality to ensure clean removal of views.
   */
  var ViewBase = Backbone.View.extend({

    /**
     * Builds HTML and themes it.
     */
    build: function () {},
    /**
     * {@inheritdoc}
     */
    remove: function (releaseElement) {
      if (this.undelegateEvents) {
        this.undelegateEvents();
      }
      if (this.stopListening) {
        this.stopListening();
      }
      this.$el
        .removeData()
        .off()
        .empty()
        .removeClass('acquia-lift-processed');

      if (releaseElement) {
        this.setElement(null);
      }

      Backbone.View.prototype.remove.call(this);
    }
  });

  /***************************************************************
   *
   *            M A I N  M E N U
   *
   ***************************************************************/

  /**
   * View/controller for full menu list.
   */
  Drupal.acquiaLiftUI.MenuView = ViewBase.extend({

    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      // The campaign collection.
      this.collection = options.collection;
      this.collection.on('change', this.render, this);
      this.render();
    },

    /**
     * {@inheritdoc}
     */
    render: function() {
      var hasCampaigns = this.collection.length > 0;
      var activeCampaign = this.collection.findWhere({'isActive': true});
      var supportsGoals = activeCampaign && activeCampaign.get('supportsGoals');
      // Show or hide relevant menus.
      if (hasCampaigns && activeCampaign) {
        if (supportsGoals) {
          this.$el.find('[data-acquia-lift-personalize="goals"]').parents('li').show();
        } else {
          this.$el.find('[data-acquia-lift-personalize="goals"]').parents('li').hide();
        }
        this.$el.find('[data-acquia-lift-personalize="option_sets"]').parents('li').show();
      } else {
        this.$el.find('[data-acquia-lift-personalize="goals"]').parents('li').hide();
        this.$el.find('[data-acquia-lift-personalize="option_sets"]').parents('li').hide();
      }
    },

    getMenuActive: function() {
      return this.$el.hasClass('navbar-active');
    },

    setMenuActive: function(isActive) {
      if (isActive) {
        this.$el.addClass('navbar-active');
      } else {
        this.$el.removeClass('navbar-active');
      }
    }
  });

  /***************************************************************
   *
   *            C A M P A I G N S
   *
   ***************************************************************/

  /**
   * View/controller for the campaign menu header.
   */
  Drupal.acquiaLiftUI.MenuCampaignsView = ViewBase.extend({

    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      this.collection = options.collection;
      this.collection.on('change', this.render, this);
    },

    /**
     * {@inheritdoc}
     *
     * @todo: Move count into this view instead of detaching and re-adding.
     */
    render: function () {
      var activeCampaign = this.collection.findWhere({'isActive': true});
      var $count = this.$el.find('i.acquia-lift-personalize-type-count').detach();
      if (!activeCampaign) {
        var label = Drupal.t('All campaigns');
      } else {
        var label = Drupal.theme.acquiaLiftSelectedContext({'label': activeCampaign.get('label'), 'category': Drupal.t('Campaign')});
      }
      this.$el.html(label);
      if ($count.length > 0) {
        this.$el.prepend($count);
      }
    }
  });

  /**
   * Backbone View/Controller for a single campaigns.
   */
  Drupal.acquiaLiftUI.MenuCampaignView = ViewBase.extend({

    events: {
      'click': 'onClick'
    },

    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      if (this.model) {
        this.model.on('change:isActive', this.render, this);
        this.model.on('destroy', this.remove, this);
        this.listenTo(this.model, 'change:optionSets', this.render);
        this.listenTo(this.model, 'change:variations', this.render);
      }

      this.build();
      this.render();
    },

    /**
     * {@inheritdoc}
     */
    render: function () {
      var isActive = this.model ? this.model.get('isActive') : false;
      this.$el.toggle(this.model.includeInNavigation());
      // The menu li element.
      this.$el.toggleClass('acquia-lift-active', isActive);
      // The link element.
      this.$el.find('.acquia-lift-campaign').attr('aria-pressed', isActive);
    },

    /**
     * {@inheritdoc}
     */
    build: function () {
      var html = '';
      if (this.model) {
        html += Drupal.theme('acquiaLiftPersonalizeCampaignMenuItem', {
          link: {
            'id': this.model.get('name'),
            'label': this.model.get('label'),
            'href': this.model.get('links').view
          },
          edit: {
            'href': this.model.get('links').edit
          }
        });
      } else {
        html += Drupal.theme('acquiaLiftPersonalizeNoMenuItem', {
          'type': 'campaigns'
        });
      }
      this.$el.html(html);
    },

    /**
     * {@inheritdoc}
     */
    remove: function () {
      ViewBase.prototype.remove.call(this, true);
    },

    /**
     * Responds to clicks.
     *
     * @param jQuery.Event event
     */
    onClick: function (event) {
      if ($(event.target).hasClass('acquia-lift-campaign')) {
        // @todo Finish styling a throbber for campaign links that fire an
        // ajax event.
        //$(Drupal.theme('acquiaLiftThrobber')).insertAfter(this.$el.find('.acquia-lift-campaign'));
        Drupal.acquiaLiftUI.setActiveCampaignAjax.call(null, this.model.get('name'), this);
        event.preventDefault();
        event.stopPropagation();
      }
    }
  });

  /***************************************************************
   *
   *            C O N T E N T  V A R I A T I O N S
   *
   ***************************************************************/


  /**
   * View for the top-level content variations menu.
   */
  Drupal.acquiaLiftUI.MenuContentVariationsMenuView = ViewBase.extend({

    /**
     * {@inheritDoc}
     */
    initialize: function(options) {
      this.campaignCollection = options.campaignCollection;
      this.listenTo(this.campaignCollection, 'change:isActive', this.render);
      this.listenTo(this.campaignCollection, 'change:activeVariation', this.render);
      this.listenTo(this.campaignCollection, 'change:variations', this.render);
    },

    /**
     * {@inheritDoc}
     */
    render: function() {
      var currentCampaign = this.campaignCollection.findWhere({'isActive': true});
      var text = Drupal.t('Variation Sets');
      var $count = this.$el.find('i.acquia-lift-personalize-type-count').detach();
      if (!currentCampaign) {
        return;
      }
      if (currentCampaign instanceof Drupal.acquiaLiftUI.MenuCampaignABModel) {
        var currentVariation = currentCampaign.getCurrentVariationLabel();
        if (currentVariation) {
          text = Drupal.theme.acquiaLiftSelectedContext({'label': currentVariation, 'category': Drupal.t('Variation')});
        } else {
          text = Drupal.t('Variations');
        }
      }
      this.$el.html(text);
      if ($count) {
        this.$el.prepend($count);
      }
    }
  });

  /**
   * View for all content variations in a campaign.
   *
   * The model in this view is actually the campaign model.
   */
  Drupal.acquiaLiftUI.MenuContentVariationsView = ViewBase.extend({

    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      this.listenTo(this.model, 'change:isActive', this.render);
      this.listenTo(this.model, 'change:optionSets', this.render);
      this.listenTo(this.model, 'change:variations', this.render);
      this.render();
    },

    /**
     * {@inheritdoc}
     */
    render: function () {
      this.$el
        // Toggle visibility of the option set based on the active status of the
        // associated campaign.
        .toggle(this.model.get('isActive'));
    }
  });

  /**
   * Backbone View/Controller for an option set within a campaign.
   */
  Drupal.acquiaLiftUI.MenuOptionSetView = ViewBase.extend({

    events: {
      'click .acquia-lift-preview-option': 'onClick'
    },

    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      var that = this;

      this.listenTo(this.model, 'change', this.render);
      this.listenTo(this.model, 'remove', this.remove);
      this.listenTo(this.model, 'reset', this.remove);
      this.listenTo(this.model, 'change:options', this.rebuild);

      this.onOptionShowProxy = $.proxy(this.onOptionShow, this);
      $(document).on('personalizeOptionChange', function (event, $option_set, choice_name, osid) {
        that.onOptionShowProxy(event, $option_set, choice_name, osid);
      });

      this.rebuild();
    },

    /**
     * Regenerates the list HTML and adds to the element.
     * This is necessary when the option set collection changes.
     *
     * @param model
     */
    rebuild: function () {
      this.build();
      this.render();
      // Re-run navbar handling to pick up new menu options.
      _.debounce(Drupal.acquiaLiftUI.utilities.updateNavBar, 300);
    },


    /**
     * {@inheritdoc}
     */
    render: function () {
      this.$el
        .find('[data-acquia-lift-personalize-option-set-option]')
        .removeClass('acquia-lift-active')
        .attr('aria-pressed', 'false');
      this.$el
        .find('[data-acquia-lift-personalize-option-set-option="' + this.model.get('activeOption') + '"]')
        .addClass('acquia-lift-active')
        .attr('aria-pressed', 'true');
    },

    /**
     * {@inheritdoc}
     */
    build: function () {
      var html = '';
      html += Drupal.theme('acquiaLiftOptionSetItem', {
        osID: this.model.get('osid'),
        os: this.model.attributes
      });
      this.$el.html(html);
    },

    /**
     * {@inheritdoc}
     */
    remove: function () {
      $(document).off('personalizeOptionChange', this.onOptionShowProxy);
      ViewBase.prototype.remove.call(this);
    },

    /**
     * Responds to clicks.
     *
     * @param jQuery.Event event
     */
    onClick: function (event) {
      if (!$(event.target).hasClass('acquia-lift-preview-option')) {
        return;
      }

      var optionid = $(event.target).data('acquia-lift-personalize-option-set-option');
      this.model.set('activeOption', optionid);
      event.preventDefault();
      event.stopPropagation();
    },

    /**
     * Responds to personalizeOptionChange change events.
     *
     * @param jQuery event
     * @param jQuery $option_set
     *   A reference to the jQuery-wrapped option set DOM element.
     * @param string choice_name
     *   The name of the selected choice.
     * @param string osid
     *   The id of the option set to which this choice belongs.
     */
    onOptionShow: function (event, $option_set, choice_name, osid) {
      if (this.model.get('osid') === osid) {
        this.model.set('activeOption', choice_name);
      }
    }
  });

  /**
   * View to show when there are no option sets for a campaign.
   */
  Drupal.acquiaLiftUI.MenuOptionSetEmptyView = ViewBase.extend({
    initialize: function (options) {
      this.listenTo(this.model, 'change:isActive', this.render);
      this.listenTo(this.model, 'change:optionSets', this.render);
      this.listenTo(this.model, 'change:variations', this.render);

      this.build();
      this.render();
    },

    build: function () {
      var html = '';
      html += Drupal.theme('acquiaLiftPersonalizeNoMenuItem', {
        type: 'variation sets'
      });
      this.$el.html(html);
    },

    render: function () {
      this.$el.toggle(this.model.get('isActive'));
    }
  });

  /**
   * Backbone View/Controller for the page variations of a campaign.
   */
  Drupal.acquiaLiftUI.MenuPageVariationsView = ViewBase.extend({
    events: {
      'click .acquia-lift-preview-option': 'onClick'
    },

    /**
     * {@inheritDoc}
     */
    initialize: function (options) {
      var that = this;

      // the model is the campaign model.
      this.listenTo(this.model, 'destroy', this.remove);
      this.listenTo(this.model, 'change:isActive', this.render);
      this.listenTo(this.model, 'change:variations', this.rebuild);
      this.listenTo(this.model, 'change:activeVariation', this.onActiveVariationChange);

      this.onOptionShowProxy = $.proxy(this.onOptionShow, this);
      this.onPageVariationEditModeProxy = $.proxy(this.onPageVariationEditMode, this);

      $(document).on('personalizeOptionChange', function (event, data) {
        that.onOptionShowProxy(event, data);
      });
      $(document).on('acquiaLiftPageVariationMode', function (event, data) {
        that.onPageVariationEditModeProxy(event, data);
      });

      this.rebuild();
    },

    /**
     * {@inheritDoc}
     */
    render: function () {
      this.$el
        .find('[data-acquia-lift-personalize-page-variation]')
        .removeClass('acquia-lift-active')
        .attr('aria-pressed', 'false');
      var activeVariation = this.model.get('activeVariation');
      var variationData = (isNaN(activeVariation) || activeVariation == -1) ? 'new' : activeVariation;
      this.$el.find('[data-acquia-lift-personalize-page-variation="' + variationData + '"]')
        .addClass('acquia-lift-active')
        .attr('aria-pressed', 'true');
    },

    /**
     * When the selected variation changes, we should also update the preview
     * such that the previewed variation matches what is shown.
     */
    onActiveVariationChange: function () {
      this.render(this.model);
    },

    /**
     * Regenerates the list HTML and adds to the element.
     * This is necessary when the option set collection changes.
     *
     * @param model
     */
    rebuild: function () {
      this.build();
      this.render();
      // Re-run navbar handling to pick up new menu options.
      _.debounce(Drupal.acquiaLiftUI.utilities.updateNavBar, 300);
    },

    /**
     * {@inheritDoc}
     */
    build: function () {
      var html = '';
      html += Drupal.theme('acquiaLiftPageVariationsItem', this.model);
      this.$el.html(html);
    },

    /**
     * {@inheritdoc}
     */
    remove: function () {
      $(document).off('personalizeOptionChange', this.onOptionShowProxy);
      $(document).off('acquiaLiftPageVariationMode', this.onPageVariationEditModeProxy);
      ViewBase.prototype.remove.call(this);
    },

    /**
     * Responds to clicks.
     *
     * @param jQuery.Event event
     */
    onClick: function (event) {
      if (!$(event.target).hasClass('acquia-lift-preview-option')) {
        return;
      }
      var variation_index = $(event.target).data('acquia-lift-personalize-page-variation');
      // Clicked new variation name when in add mode.
      if (isNaN(variation_index)) {
        return;
      }

      this.model.set('activeVariation', variation_index);

      event.preventDefault();
      event.stopPropagation();
    },

    /**
     * Select a specific variation to show.
     *
     * @param number variationIndex
     *   The variation index to show.
     */
    selectVariation: function (variationIndex) {
      var variationData = variationIndex < 0 ? 'new' : variationIndex;
      _.defer(function($context, variationId) {
        $context.find('[data-acquia-lift-personalize-page-variation="' + variationId + '"]').trigger('click');
      }, this.$el, variationData)
    },

    /**
     * Responds to personalizeOptionChange change events.
     *
     * @param jQuery event
     * @param jQuery $option_set
     *   A reference to the jQuery-wrapped option set DOM element.
     * @param string choice_name
     *   The name of the selected choice.
     * @param string osid
     *   The id of the option set to which this choice belongs.
     */
    onOptionShow: function (event, $option_set, choice_name, osid) {
      var optionSets = this.model.get('optionSets');
      var optionSet = optionSets.findWhere({osid: osid});
      if (!optionSet) {
        return;
      }
      var options = optionSet.get('options');
      var option = options.findWhere({'option_id': choice_name});
      var variationIndex = options.indexOf(option);
      if (variationIndex < 0) {
        return;
      }
      this.model.set('activeVariation', variationIndex);
    },

    /**
     * Response to a change in edit mode for the page variation application.
     *
     * @param event
     *   The jQuery event object
     * @param data
     *   An object of event data including the keys:
     *   - start: true if edit mode started, false if ended.
     *   - campaign: the machine name of the campaign holding variations.
     *   - variationIndex: the index of the variation for editing or -1
     *     if adding a new variation.
     */
    onPageVariationEditMode: function (event, data) {
      // Make sure it's for this campaign.
      if (this.model.get('name') !== data.campaign) {
        return;
      }
      if (data.start) {
        if (data.variationIndex < 0) {
          // If add mode, then create a temporary variation listing.
          var nextIndex = this.model.getNextVariationNumber();
          // The first option is always control so the numbering displayed
          // actually matches the index number.
          var variationNumber = Math.max(nextIndex, 1);
          if (nextIndex == 0) {
            // Add a control variation display as well.
            this.$el.find('ul.menu').append(Drupal.theme('acquiaLiftNewVariationMenuItem', -1));
          }
          this.$el.find('ul.menu').append(Drupal.theme('acquiaLiftNewVariationMenuItem', variationNumber));
          this.$el.find('ul.menu li.acquia-lift-empty').hide();
          // Indicate in the model that we are adding.
          this.model.set('activeVariation', -1);
          this.render(this.model);
        } else {
          // If in edit mode, make sure that the edited variation index is
          // indicated.
          // Make it seem as if the item was clicked without triggering
          // any other click events that may be listening on the link.
          var $li = this.$el.find('[data-acquia-lift-personalize-page-variation="' + data.variationIndex + '"]');
          var event = new Event('click');
          event.currentTarget = event.target = $li.get('0');
          this.onClick(event);
        }
        Drupal.acquiaLiftUI.utilities.updateNavbar();
      } else {
        // If exiting, remove any temporary variation listings.
        this.$el.find('ul.menu li.acquia-lift-empty').show();
        this.$el.find('.acquia-lift-page-variation-new').closest('li').remove();
        // If the model is set at adding, change it back to the control option.
        if (this.model.get('activeVariation') == -1) {
          this.model.set('activeVariation', 0);
        }
      }
    }
  });

  /**
   * The toggle functionality for editing page variations.
   */
  Drupal.acquiaLiftUI.MenuPageVariationsToggleView = ViewBase.extend({
    events: {
      'click': 'onClick'
    },

    /**
     * @{inheritDoc}
     *
     * The model is the page variations mode model.
     */
    initialize: function (options) {
      this.campaignCollection = options.campaignCollection;
      this.listenTo(this.campaignCollection, 'change:isActive', this.render);
      this.listenTo(this.campaignCollection, 'change:activeVariation', this.render);
      this.listenTo(this.model, 'change:isActive', this.render);
      this.build();
      this.render();
    },

    /**
     * {@inheritDoc}
     */
    render: function() {
      var currentCampaign = this.campaignCollection.findWhere({'isActive': true});
      if (!currentCampaign) {
        return;
      }
      this.$el
        .toggleClass('acquia-lift-page-variation-toggle-disabled', currentCampaign.get('activeVariation') == 0) // There is no toggle available for the control variation.
        .toggleClass('acquia-lift-page-variation-toggle-active', this.model.get('isActive'))
        .toggleClass('acquia-lift-page-variation-toggle-hidden', currentCampaign instanceof Drupal.acquiaLiftUI.MenuCampaignABModel === false);
    },

    /**
     * {@inheritDoc}
     */
    build: function() {
      this.$el.text(Drupal.t('Toggle edit variation'));
    },

    /**
     * Event handler for clicking on the toggle link.
     * @param event
     */
    onClick: function (event) {
      var currentCampaign = this.campaignCollection.findWhere({'isActive': true});
      if (!currentCampaign) {
        return;
      }
      if (this.model.get('isActive')) {
        this.model.endEditMode();
      } else {
        var currentVariationIndex = currentCampaign.get('activeVariation');
        if (currentVariationIndex == 0) {
          // Cannot edit the control variation.
          return;
        }
        this.model.startEditMode(currentVariationIndex);
      }
    }
  });

  /**
   * Display the content variation count for the active campaign.
   */
  Drupal.acquiaLiftUI.MenuContentVariationsCountView = ViewBase.extend({
    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      this.listenTo(this.model, 'change:isActive', this.render);
      this.listenTo(this.model, 'change:optionSets', this.render);
      this.listenTo(this.model, 'change:variations', this.render);
      this.listenTo(this.model, 'change:activeVariation', this.render);

      this.build();
      this.render();
    },

    /**
     * {@inheritdoc}
     */
    render: function () {
      var variations = this.model.getNumberOfVariations();
      if (this.model instanceof Drupal.acquiaLiftUI.MenuCampaignABModel && this.model.get('activeVariation') == -1) {
        // We are in add mode so adjust the number to show.
        variations++;
      }
      if (this.model.get('isActive')) {
        this.$el
          .toggleClass('acquia-lift-empty', !variations)
          .css('display', 'inline-block')
          .find('span').text(variations);
      } else {
        this.$el.css('display', 'none');
      }
    },

    /**
     * {@inheritdoc}
     */
    build: function() {
      if (this.model) {
        this.$el.attr('id', 'acquia-lift-menu-option-sets-count--' + this.model.get('name'));
      }
    }
  });

  /**
   * A "view" for the variation preview.
   *
   * This does not map to a specific
   * element in the DOM, but rather triggers updates to the view via
   * personalize executors in reaction to changes in the model.
   *
   * It receives the campaign collection as the "collection" in the initialize
   * function.  The model is always set to the currently active campaign.
   */
  Drupal.acquiaLiftUI.MenuVariationPreviewView = ViewBase.extend({
    /**
     * {@inheritDoc}
     */
    initialize: function (options) {
      this.collection = options.collection;

      this.listenTo(this.collection, 'change:isActive', this.onActiveCampaignChange);
      // Call the campaign change function to initialize the first campaign.
      this.onActiveCampaignChange(this.collection.findWhere({'isActive': true}));
    },

    onActiveCampaignChange: function (changed) {
      if (!changed) {
        if (this.model) {
          this.stopListening(this.model);
        }
        this.model = undefined;
        return;
      }
      if (changed.get('isActive')) {
        // Bind to change events from the new model.
        this.model = changed;
        this.listenTo(this.model, 'change:activeVariation', this.onVariationChange);
        this.listenTo(this.model.get('optionSets'), 'change:activeOption', this.onVariationChange);
      } else {
        this.stopListening(changed);
      }
    },

    onVariationChange: function(changedModel) {
      if (!this.model) {
        return;
      }
      if (this.model instanceof Drupal.acquiaLiftUI.MenuCampaignABModel) {
        // Simple A/B campaigns need to call the executor for each of the
        // options within the selected page variation.
        var variation_index = this.model.get('activeVariation');
        var variations = this.model.get('optionSets').getVariations();
        var variation = _.find(variations, function(obj) {
          return obj.original_index == variation_index;
        });

        if (!variation) return;
        var i, num = variation.options.length, current;
        // Run the executor for each option in the variation.
        for (i=0; i < num; i++) {
          current = variation.options[i];
          Drupal.personalize.executors[current.executor].execute($(current.selector), current.option.option_id, current.osid);
        }
      } else {
        // Standard tests just call the executors on the selected option.
        // Note that the model passed into this callback will be the
        // changed option set model.
        if (changedModel instanceof Drupal.acquiaLiftUI.MenuOptionSetModel) {
          var activeOption = changedModel.get('activeOption');
          if (!activeOption) {
            return;
          }
          var current = changedModel.get('options').findWhere({'option_id': activeOption});
          if (!current) {
            return;
          }
          Drupal.personalize.executors[changedModel.get('executor')].execute($(changedModel.get('selector')), current.get('option_id'), changedModel.get('osid'));
        }
      }
    }
  });

  /***************************************************************
   *
   *            G O A L S
   *
   ***************************************************************/

  /**
   * Renders the goals for a campaign.
   */
  Drupal.acquiaLiftUI.MenuGoalsView = ViewBase.extend({
    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      this.listenTo(this.model, 'change:isActive', this.render);
      this.listenTo(this.model, 'change:goals', this.rebuild);
      this.rebuild();
    },

    /**
     * Regenerates the list HTML and adds to the element.
     */
    rebuild: function() {
      this.build();
      this.render();
      // Re-run navbar handling to pick up new menu options.
      _.debounce(Drupal.acquiaLiftUI.utilities.updateNavBar, 300);
    },

    /**
     * {@inheritdoc}
     */
    render: function () {
      this.$el
        // Toggle visibility of the goal set based on the active status of the
        // associated campaign.
        .toggle(this.model.get('isActive'));
    },

    /**
     * {@inheritdoc}
     */
    build: function () {
      var html = Drupal.theme('acquiaLiftCampaignGoals', this.model, Drupal.settings.acquia_lift.customActions);
      this.$el.html(html);
    }
  });

  /**
   * Displays the number of goals in a campaign.
   */
  Drupal.acquiaLiftUI.MenuGoalsCountView = ViewBase.extend({
    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      this.model.on('change:goals', this.render, this);
      this.model.on('change:isActive', this.render, this);

      this.build();
      this.render();
    },

    /**
     * {@inheritdoc}
     */
    render: function () {
      var count = this.model.get('goals').length;
      if (this.model.get('isActive')) {
        this.$el
          .toggleClass('acquia-lift-empty', !count)
          .css('display', 'inline-block')
          .find('span').text(count);
      } else {
        this.$el.css('display', 'none');
      }
    },

    /**
     * {@inheritdoc}
     */
    build: function() {
      if (this.model) {
        this.$el.attr('id', 'acquia-lift-menu-goals-count--' + this.model.get('name'));
      }
    }
  });

  /**
   * The "add a goal" link.
   */
  Drupal.acquiaLiftUI.MenuGoalAddView = ViewBase.extend({
    events: {
      'click': 'onClick'
    },

    /**
     * {@inheritDoc}
     */
    initialize: function(options) {
      var that = this;

      this.addLabel = this.$el.text();
      this.onVisitorActionsEditModeProxy = $.proxy(this.onVisitorActionsEditMode, this);
      $(document).on('visitorActionsUIEditMode', function (event, data) {
        that.onVisitorActionsEditModeProxy(event, data);
      });

      // Give the goals model a chance to load and then check for the initial
      // state.
      _.delay(function() {
        var visitorActionsModel = getVisitorActionsAppModel();
        var startingInEdit = visitorActionsModel && visitorActionsModel.get('editMode');
        that.onVisitorActionsEditMode(null, startingInEdit);
      })
    },

    /**
     * {@inheritDoc}
     */
    render: function() {
      var visitorActionsModel = getVisitorActionsAppModel();
      if (visitorActionsModel && visitorActionsModel.get('editMode')) {
        this.$el.text(Drupal.t('Exit goals mode'));
      } else {
        this.$el.text(this.addLabel);
      }
    },

    /**
     * Responds when the visitor actions edit mode is triggered.
     */
    onVisitorActionsEditMode: function(event, editMode) {
      this.render();
      if (editMode) {
        // The next time we click the link we want it to just shut down
        // visitor actions and not open a modal window.
        this.$el.off();
        this.$el.on('click', this.onClick);
        // It has been essentially "unprocessed" so let it get re-processed
        // again later.
        this.$el.removeClass('ctools-use-modal-processed');
      } else {
        // Next time this link is clicked it should open the modal.
        this.$el.off('click', this.onClick);
        Drupal.attachBehaviors(this.$el.parent());
      }
    },

    /**
     * Responds to clicks on the link.
     *
     * If goal selection is currently on, then trigger and event to turn it
     * off - otherwise let the default handling take care of things.
     */
    onClick: function(e) {
      var visitorActionsModel = getVisitorActionsAppModel();
      if (visitorActionsModel && visitorActionsModel.get('editMode')) {
        // Note that sending shutdown here causes a loop of events so
        // we work through a connector toggle process.
        // @see acquia_lift.modal.js
        $(document).trigger('acquiaLiftVisitorActionsConnectorToggle');
      }
      e.preventDefault();
      e.stopImmediatePropagation();
    }
  });

  /***************************************************************
   *
   *            R E P O R T S
   *
   ***************************************************************/

  /**
   * Updates the results link to reflect the active campaign.
   */
  Drupal.acquiaLiftUI.MenuReportsView = ViewBase.extend({

    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      this.collection = options.collection;
      if (!this.model) {
        return;
      }
      this.model.on('change', this.render, this);
      this.render();
    },

    /**
     * {@inheritdoc}
     */
    render: function () {
      var activeCampaign = this.collection.findWhere({'isActive': true});
      if (!activeCampaign) {
        this.$el
          .find('a[href]')
          .attr('href', '')
          .end()
          .hide();
      }
      else {
        // The report link will be empty if reports are not available for this
        // campaign agent type.
        var reportLink = activeCampaign.get('links').report;
        if (reportLink.length == 0) {
          reportLink = 'javascript:void(0);';
          this.$el.find('a[href]').addClass('acquia-lift-menu-disabled');
        } else {
          this.$el.find('a[href]').removeClass('acquia-lift-menu-disabled');
        }
        var name = activeCampaign.get('name');
        var label = activeCampaign.get('label');
        this.$el
          .find('a[href]')
          .attr('href', reportLink)
          .text(Drupal.t('Reports'))
          .end()
          .show();
      }
    }
  });

  /***************************************************************
   *
   *            S T A T U S
   *
   ***************************************************************/

  /**
   * Updates the status link to the correct verb for each campaign.
   *
   * Also handles Ajax submission to change the status of the selected campaign.
   */
  Drupal.acquiaLiftUI.MenuStatusView = ViewBase.extend({

    events: {
      'click .acquia-lift-status-update': 'updateStatus'
    },

    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      _.bindAll(this, "updateStatus");
      this.collection = options.collection;
      if (!this.model) {
        return;
      }
      this.model.on('change', this.render, this);
      this.build();
      this.render();
    },

    /**
     * {@inheritdoc}
     */
    render: function () {
      var activeCampaign = this.collection.findWhere({'isActive': true});
      if (!activeCampaign) {
        this.$el.hide();
      }
      else {
        var nextStatus = activeCampaign.get('nextStatus');
        this.$el
          .find('a[href]')
          .text(Drupal.t('@status campaign', {'@status': nextStatus.text}))
          .data('acquia-lift-campaign-status', nextStatus.status)
          .removeClass('acquia-lift-menu-disabled')
          .end()
          .show();
        // The campaign must be verified in order to change the status.
        if (activeCampaign.get('verified') == true) {
          this.$el.find('a[href]').removeClass('acquia-lift-menu-disabled');
        } else {
          this.$el.find('a[href]').addClass('acquia-lift-menu-disabled');
        }
        this.updateListeners();
      }
    },

    /**
     * {@inheritdoc}
     */
    build: function() {
      this.$el
        .find('a[href]')
        .attr('href', 'javascript:void(0)')
        .addClass('acquia-lift-status-update');
    },

    /**
     * Update click listeners based on the status of a campaign.
     */
    updateListeners: function() {
      var activeCampaign = this.collection.findWhere({'isActive': true});
      if (!activeCampaign) {
        return;
      }

      if (activeCampaign.get('status') == 1) {
        // Not yet started.
        this.$el
          .find('a')
          .addClass('acquia-lift-menu-status-advanced')
          .attr('href', startPath + activeCampaign.get('name'));

        if (this.$el.find('a').hasClass('ctools-use-modal')) {
          this.$el.find('a').removeClass('ctools-use-modal-processed');
        } else {
          this.$el
            .find('a')
            .addClass('ctools-use-modal')
            .addClass('ctools-modal-acquia-lift-style')
            .off();
        }
        // Re-attach ctools-modal behaviors so that the element settings for
        // Drupal ajax forms get reset to the new campaign url.
        Drupal.attachBehaviors(this.$el.parent());
      } else {
        // All other status can just get immediately changed.
        if (!this.$el.find('a').hasClass('ctools-use-modal')) {
          // Already set up as a plain click handler.
          return;
        }
        this.$el
          .find('a')
          .attr('href', 'javascript:void(0);')
          .removeClass('acquia-lift-menu-status-advanced')
          .removeClass('ctools-use-modal')
          .removeClass('ctools-modal-acquia-lift-style')
          .removeClass('ctools-use-modal-processed')
          .off()
          .bind('click', this.updateStatus);
      }
    },

    /**
     * Update the status of the current campaign to its next status value.
     *
     * @param event
     *   Click event that triggered this function.
     */
    updateStatus: function(event) {
      var newStatus = $(event.target).data('acquia-lift-campaign-status');
      var activeModel = this.collection.findWhere({'isActive': true});
      if (!newStatus || !activeModel || activeModel.get('verified') == false) {
        return;
      }
      // Make link disabled while update happens.
      // The disabled class will be removed when re-rendered.
      this.$el.find('a[href]').addClass('acquia-lift-menu-disabled');
      activeModel.updateStatus(newStatus);
    }
  });

  /***************************************************************
   *
   *      C O N T E N T  T R I G G E R S / C A N D I D A T E S
   *
   ***************************************************************/

  /**
   * Toggles the 'add content variation' trigger.
   */
  Drupal.acquiaLiftUI.MenuContentVariationTriggerView = ViewBase.extend({
    events: {
      'click': 'onClick'
    },

    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      var that = this;

      this.contentVariationModel = options.contentVariationModel;
      this.pageVariationModel = options.pageVariationModel;
      this.campaignCollection = options.campaignCollection;

      // Model property holds a reference to the relevant type of creation
      // mode model based on the type of campaign selected.
      if (this.campaignCollection.findWhere({'isActive': true}) instanceof Drupal.acquiaLiftUI.MenuCampaignABModel) {
        this.model = this.pageVariationModel;
      } else {
        this.model = this.contentVariationModel;
      }

      this.listenTo(this.contentVariationModel, 'change:isActive', this.render);
      this.listenTo(this.pageVariationModel, 'change:isActive', this.render);
      this.listenTo(this.campaignCollection, 'change:isActive', this.onCampaignChange);

      this.onPageVariationEditModeProxy = $.proxy(this.onPageVariationEditMode, this);
      $(document).on('acquiaLiftPageVariationMode', function (event, data) {
        that.onPageVariationEditModeProxy(event, data);
      });

      this.render();
    },

    /**
     * {@inheritdoc}
     */
    render: function () {
      var isActive = this.model.get('isActive');
      this.$el.toggleClass('acquia-lift-active', isActive);

      if (this.$el.parents('.acquia-lift-controls').length == 0) {
        return;
      }
      // Update the text if within the menu.
      var text = '';
      if (isActive) {
        text = Drupal.t('Exit edit mode');
      } else {
        text = this.model instanceof Drupal.acquiaLiftUI.MenuPageVariationModeModel ? Drupal.t('Add a variation') : Drupal.t('Add a variation set');
      }
      this.$el.text(text);
    },

    /**
     * Responds to clicks.
     *
     * @param jQuery.Event event
     */
    onClick: function (event) {
      event.preventDefault();

      if (this.model.get('isActive')) {
        this.model.endEditMode();
      } else {
        this.model.startAddMode();
      }
    },

    /**
     * Change handler when a new campaign is selected.
     *
     * @param model
     *   The campaign model that was selected.
     * @param isActive
     *   The new active status.
     */
    onCampaignChange: function(model, isActive) {
      this.model.endEditMode();
      if (isActive) {
        if (model instanceof Drupal.acquiaLiftUI.MenuCampaignABModel) {
          this.model = this.pageVariationModel;
        } else {
          this.model = this.contentVariationModel;
        }
        this.render(this.model);
      }
    },

    /**
     * Listens to changes broadcast from the page variation application.
     */
    onPageVariationEditMode: function (event, data) {
      this.pageVariationModel.set('isActive', data.start);
    }
  });

  /**
   * Adds an identifying class to elements on the page that can be varied.
   */
  Drupal.acquiaLiftUI.MenuContentVariationCandidateView = ViewBase.extend({
    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      this.model.on('change', this.render, this);
    },

    /**
     * {@inheritdoc}
     */
    render: function () {
      var isActive = this.model.get('isActive');
      this.$el.toggleClass('acquia-lift-content-variation-candidate', isActive);
      // Pull the Personalize contextual link out of the list and highlight it.
      if (isActive) {
        var $wrapper = this.$el.find('.contextual-links-wrapper:first');
        var $link = $wrapper.find('.personalize-this-contextual-link').detach();
        $wrapper.children('.contextual-links-trigger').addClass('acquia-lift-hidden');
        $wrapper.prepend($link);
      }
      // Repair the contextual links.
      else {
        var $wrapper = this.$el.find('.contextual-links-wrapper:first');
        var $link = $wrapper.find('.personalize-this-contextual-link')
        $wrapper.find('.contextual-links .personalize').append($link);
        $wrapper.children('.contextual-links-trigger').removeClass('acquia-lift-hidden');
      }
    },

    /**
     * {@inheritdoc}
     */
    remove: function () {
      ViewBase.prototype.remove.call(this, true);
    }
  });

}(Drupal, Drupal.jQuery, _, Backbone));
