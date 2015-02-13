TVE Adobe Pass
=====================================
The module is used to integrate with Adobe Pass Service. In the login process provides an opportunity to login on providers sites.

The module utilizes the following components:
SWFObject library, situated in /lib folder - swfobject.js.
TVE Adobe Pass javascript file, situated in /js folder - tve_adobe_pass.js.
Once activated the Adobe Pass library will be loaded on all pages if Requestor ID and Resource ID are set.

The module provides settings in the admin panel (admin/config/services/adobe-pass) after installation.
They have default settings after installing. Can be changed for current environment:
  Adobe Pass Access Enabler Location
  Adobe Pass Request Timeout (Determines the number of millis for authentication check timeout)
  Required Flash Version For Adobe Pass (Minimum supported flash player version)
  Adobe Pass Requestor ID
  Adobe Pass Resource ID
  Authentication Status messages (Descriptions for error messages, which will be shown into player section when error occurs)

Adobe Pass Requestor ID and Adobe Pass Resource ID fields should be filled on settings page(admin/config/services/adobe-pass) after the module installing.
