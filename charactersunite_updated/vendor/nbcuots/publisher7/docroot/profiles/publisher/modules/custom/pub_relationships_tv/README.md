Pub Relationships TV

# Known Issues

If you have a decent amount of TV Shows & TV Seasons (over 6,000) it is possible
you might run into a memory issue. This is a common problem with EntityReference
and the select widget (https://drupal.org/node/1344784).

To work around this, this module ships with an Alternate EntityReference Plugin.
This plugin is a bit more performant then the default EntityReference Select
widget.

You can enable this new plugin by enabling it for which ever field you have
too much content over at the individual field settings for the Pub Relationship
TV shows (admin/structure/field-collections/field-pub-relation-tv-shows/fields).

