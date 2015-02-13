
Context Resolution for Drupal 7.x
--------------------------
This module extends the Context module with two additional conditions that
enable developers to adapt the site to the users current screen resolution
or browser width by using context reactions.

For example, you could use Context and the Delta module to change the template
depending on screen resolution.

Adaping to resolution should mostly be done with CSS and media queries,
but sometimes you just can not do everything you need to do in CSS.

IMPORTANT NOTE:

This module detects screen and browser size with Javascript and
sets a cookie accordingly.

This means that Javascript and cookies must be enabled.
Also, after changing the browser size, a reload will obviously be required
for the changes to show up.

Installation
------------
Context Resolution can be installed like any other Drupal module -- place it in
the modules directory for your site and enable it (and its requirements,
CTools and Context) on the `admin/modules` page.

You will probably also want to install Context UI which provides a way for
you to edit contexts through the Drupal admin interface.


Configuration
-------------

-) Create a new or edit an existing context under admin/structure/context.
-) Add a "Screen resolution" or "Browser window resolution" condition.
-) For the chosen condition, configure the width and height settings as you
  require.
  Enter pixel values into the "Widht/height from/until" fields.
  Leave empty to add no boundary.

  Examples:
    -) Enable on all resolutions wider than 1024px and higher than 600px:
        Width from: 1024, Height from: 600

Hooks
-----
None.


Maintainers
-----------

- theduke (Christoph Herzog)


Contributors
------------

- theduke (Christoph Herzog)
