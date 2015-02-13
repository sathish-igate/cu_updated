Program Guide
=================================

This module allows sites to import electronic program guide data from ROVI via a
JSON feed provided by MPX.

Setup
---------------
After enabling the Program Guide visit ```admin/config/services/program_guide```
. The feed URL can be obtained by contacting the NBCUOTS Video Team. **Make sure
they provide the JSON version of the feed.** The two other options that can be
configured are how often the site should check for new data (**this is specified
in hours**) and how old a piece program guide content should be before being
auto-deleted (**this is specified in days**).

Example feed:
http://feed.entertainment.tv.theplatform.com/f/dCK2IC/stage_usa_listing?range=1-*&form=json

How it works
---------------
Once the feed is specified, the site will check for updated data every 8 hours
(by default) when the site's cron runs. If updated data is found it is added to
an import queue and the items in that queue will be imported in chunks over the
next several cron runs. For example, let's assume your site's cron runs every 5
minutes and let's assume that your site is configured to check for updated data
every 8 hours. You might see this behavior:

* 02:35 - 7 hours and 55 minutes have passed so we do not check for updates.
There is no queued data to import.
* 02:40 - 8 hours have passed so we check for updated data. There are 300 new
pieces of program data and they are added to the import queue. 112 are
immediately imported.
* 02:45 - 5 minutes have passed so we do not check for updates. There are still
188 pieces of program data in the import queue. 119 are immediately imported.
* 02:50 - 10 minutes have passed so we do not check for updates. There are still
69 pieces of program data in the import queue. All 69 are immediately imported.
* 02:55 - 15 minutes have passed so we do not check for updates. There is no
queued data to import.
* ...
* 10:35 - 7 hours and 55 minutes have passed so we do not check for updates.
There is no queued data to import.
* 10:40 - 8 hours have passed so we check for updated data. There are 105 new
pieces of program data and they are added to the import queue. All 105 are
immediately imported.
* 10:45 - 5 minutes have passed so we do not check for updates. There is no
queued data to import.
* ...

**The number of items that will be imported from the queue on a given cron run
will be as many as possible in 15 seconds which can vary based on the current
site traffic.**
