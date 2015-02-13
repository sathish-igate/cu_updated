# Pub Relationship TV Enhanced

A replacement module for pub_relationships_tv. This module does everything
in a custom field (Field API) instead of relying on Field Collection.

##Testing
If you make any changed please run ```phpunit test``` and make sure all test pass.


###Installation
This module works with/or without Pub Relationship TV. If both modules are enable
this module will hide the Pub Relationship TV field and make sure the data is kept in sync.

If you no longer have any need for the old Pub Relationship TV Module feel free to disable
it and delete the field_pub_relation_tv_shows. Once you disable Pub Relationship TV
the data sync will stop and this module will just handle its own data.

