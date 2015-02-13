#Pub mpx API
General instructions for using the Publisher7 mpx API.

##Instructions for importing MPX videos with a specific player based on rulesets.

1. Copy the module pub_mpx_example.module & .info files into a new module
directory.
1. Rename the file names to your_module_name.module and .info.
1. Open the .module file and replace the name to match.
i.e. pub_mpx_example_pub_mpx_player_id_rulesets_info will be =>
your_module_name_pub_mpx_player_id_rulesets_info()
1. Customize the rulesets found in this function to match your preferences.
1. Enable your module.
1. Go to /admin/config/media/theplatform, login and select your account.
1. Go to /admin/content/file/mpxplayer and import players.
1. Go to /admin/content/file/mpxmedia and select a default player for videos
that don't match a ruleset under "Import new mpxMedia with mpxPlayer:".
1. Click "Sync mpxMedia now".
1. Your videos should all have the correct player set.

###Example
Lets take the following example:

    function your_module_name_pub_mpx_player_id_rulesets_info() {
      $rulesets = array(
        array(
          'fields' => array(
            'entitlement' => 'free',
            'fullEpisode' => FALSE,
          ),
          // Set the player for the video with the key 'guid'. This is the
          // 'Reference ID' in the history section of the player at
          // http://mpx.theplatform.com.

          // thePlatform - VOD Global Player
          'guid' => 'GClP1BxPBHo87Bi5oymyrI4xnBqwaL9Zz',
        ),
        array(
          'fields' => array(
            'entitlement' => 'auth',
            'fullEpisode' => TRUE,
          ),
          // [DEV] - MVPD Live Player (tP Support)
          'guid' => 'gd_DUKrut8dURN8bzZaA7y0BDtbJG_6sz',
        ),
        array(
          'fields' => array(
            // Use media$name to specify a category. Currently case-sensitive.
            'media$name' => 'Live',
          ),
          // thePlatform - Linear Global Player
          'guid' => 'Ypj4ZTiYGkwy5iCRdLQMgzX1CyhnqYHjz',
        ),
      );

      return $rulesets;
    }

In the above example we have three arrays each acting as a ruleset. Each ruleset
consists of the 'fields' key (which is another array) and the 'guid' key. The
'fields' key can contain the 'entitlement', 'fullEpisode' and 'media$name' key.
If all those match the metadata of the video being imported then the API will
set the player to the 'guid' that you specify. You can get the 'guid' from the
History section of the video at http://mpx.theplatform.com, it is the
'Reference ID'.

The last matching ruleset wins in the case where two competing rulesets match.

The system should handle any field the mpx offers, to get exact naming of that
field on our end please contact the Publisher7 team. A partial list of valid
fields are below:

'entitlement' => 'free' | 'auth'
'fullEpisode' => TRUE | FALSE
'media$name' => 'Live' | 'Comedy' | 'etc...'

@todo Provide more comprehensive list.

##Instructions for altering rulesets.
Use hook_pub_mpx_player_id_rulesets_info_alter(&$rulesets).
@todo Write more about how to use this.
