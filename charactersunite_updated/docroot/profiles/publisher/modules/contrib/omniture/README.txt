$ID: $
Module: Omniture Integration
Author: Greg Knaddison http://knaddison.com
Co-Maintainer: Matthew Tucker
Based on Google Analytics module by Mike Carter www.ixis.co.uk


Description
===========
Adds the Omniture statistics system to your website.


Requirements
============

* Omniture user account


Installation
============
* Copy the 'omniture' module directory in to your Drupal
modules directory as usual.


Customization
=============
* You can customize the module to your site to create variables
more suited to tracking your needs by utilizing hook_omniture_variables.
For an implementation example, see the omniture_basic module included
in this package.


Usage
=====
You will also need to define what user roles should be tracked.
Simply tick the roles you would like to monitor.

You can also add JavaScript code in the "Advanced" section of the settings.

All pages will now have the required JavaScript added to the
HTML footer can confirm this by viewing the page source from
your browser.

'admin/' pages are automatically ignored by this module.
