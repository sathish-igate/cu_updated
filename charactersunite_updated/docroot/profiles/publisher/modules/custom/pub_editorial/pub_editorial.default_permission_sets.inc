<?php
/**
 * @file
 * pub_editorial.default_permission_sets.inc
 */

/**
 * Implements hook_default_permission_set().
 */
function pub_editorial_default_permission_set() {
  $export = array();

  $permission_set = new stdClass();
  $permission_set->disabled = FALSE; /* Edit this to true to make a default permission_set disabled initially */
  $permission_set->api_version = 1;
  $permission_set->machinename = 'publisher_admin_permissions_set';
  $permission_set->name = 'Publisher Admin Permissions Set';
  $permission_set->permissions = array(
    'access administration menu' => 'access administration menu',
    'access administration pages' => 'access administration pages',
    'access advanced_link autocomplete' => 'access advanced_link autocomplete',
    'access all views' => 'access all views',
    'access collection list' => 'access collection list',
    'access content' => 'access content',
    'access content overview' => 'access content overview',
    'access contextual links' => 'access contextual links',
    'access environment indicator' => 'access environment indicator',
    'access environment indicator default_environment' => 'access environment indicator default_environment',
    'access environment indicator overwritten_environment' => 'access environment indicator overwritten_environment',
    'access overlay' => 'access overlay',
    'access own authorizations' => 'access own authorizations',
    'access own consumers' => 'access own consumers',
    'access site in maintenance mode' => 'access site in maintenance mode',
    'access site reports' => 'access site reports',
    'access user profiles' => 'access user profiles',
    'access workbench' => 'access workbench',
    'add authenticated twitter accounts' => 'add authenticated twitter accounts',
    'add media from remote sources' => 'add media from remote sources',
    'add twitter accounts' => 'add twitter accounts',
    'administer actions' => 'administer actions',
    'administer blocks' => 'administer blocks',
    'administer checked out documents' => 'administer checked out documents',
    'administer collections' => 'administer collections',
    'administer consumers' => 'administer consumers',
    'administer content revisions' => 'administer content revisions',
    'administer content types' => 'administer content types',
    'administer environment indicator settings' => 'administer environment indicator settings',
    'administer fb apps' => 'administer fb apps',
    'administer features' => 'administer features',
    'administer field collections' => 'administer field collections',
    'administer fieldgroups' => 'administer fieldgroups',
    'administer file types' => 'administer file types',
    'administer files' => 'administer files',
    'administer filters' => 'administer filters',
    'administer image styles' => 'administer image styles',
    'administer media browser' => 'administer media browser',
    'administer menu' => 'administer menu',
    'administer meta tags' => 'administer meta tags',
    'administer module filter' => 'administer module filter',
    'administer modules' => 'administer modules',
    'administer mpx account' => 'administer mpx account',
    'administer nodes' => 'administer nodes',
    'administer oauth' => 'administer oauth',
    'administer pathauto' => 'administer pathauto',
    'administer permissions' => 'administer permissions',
    'administer publisher utilities' => 'administer publisher utilities',
    'administer queue' => 'administer queue',
    'administer queue types' => 'administer queue types',
    'administer redirects' => 'administer redirects',
    'administer shortcuts' => 'administer shortcuts',
    'administer site configuration' => 'administer site configuration',
    'administer SiteCatalyst configuration' => 'administer SiteCatalyst configuration',
    'administer software updates' => 'administer software updates',
    'administer taxonomy' => 'administer taxonomy',
    'administer themes' => 'administer themes',
    'administer twitter accounts' => 'administer twitter accounts',
    'administer url aliases' => 'administer url aliases',
    'administer users' => 'administer users',
    'administer views' => 'administer views',
    'administer workbench' => 'administer workbench',
    'administer_workbench_workflows' => 'administer_workbench_workflows',
    'admin_display_suite' => 'admin_display_suite',
    'admin_fields' => 'admin_fields',
    'admin_view_modes' => 'admin_view_modes',
    'block IP addresses' => 'block IP addresses',
    'bypass file access' => 'bypass file access',
    'bypass node access' => 'bypass node access',
    'bypass workbench moderation' => 'bypass workbench moderation',
    'cancel account' => 'cancel account',
    'change own username' => 'change own username',
    'check out documents' => 'check out documents',
    'clone node' => 'clone node',
    'clone own nodes' => 'clone own nodes',
    'create character_profile content' => 'create character_profile content',
    'create collections' => 'create collections',
    'create files' => 'create files',
    'create media_gallery content' => 'create media_gallery content',
    'create url aliases' => 'create url aliases',
    'customize shortcut links' => 'customize shortcut links',
    'delete any audio files' => 'delete any audio files',
    'delete any character_profile content' => 'delete any character_profile content',
    'delete any document files' => 'delete any document files',
    'delete any image files' => 'delete any image files',
    'delete any media_gallery content' => 'delete any media_gallery content',
    'delete any mpx_player files' => 'delete any mpx_player files',
    'delete any video files' => 'delete any video files',
    'delete collections' => 'delete collections',
    'delete own audio files' => 'delete own audio files',
    'delete own character_profile content' => 'delete own character_profile content',
    'delete own document files' => 'delete own document files',
    'delete own image files' => 'delete own image files',
    'delete own media_gallery content' => 'delete own media_gallery content',
    'delete own mpx_player files' => 'delete own mpx_player files',
    'delete own video files' => 'delete own video files',
    'delete revisions' => 'delete revisions',
    'display drupal links' => 'display drupal links',
    'download any audio files' => 'download any audio files',
    'download any document files' => 'download any document files',
    'download any image files' => 'download any image files',
    'download any mpx_player files' => 'download any mpx_player files',
    'download any video files' => 'download any video files',
    'download own audio files' => 'download own audio files',
    'download own document files' => 'download own document files',
    'download own image files' => 'download own image files',
    'download own mpx_player files' => 'download own mpx_player files',
    'download own video files' => 'download own video files',
    'edit any audio files' => 'edit any audio files',
    'edit any character_profile content' => 'edit any character_profile content',
    'edit any document files' => 'edit any document files',
    'edit any image files' => 'edit any image files',
    'edit any media_gallery content' => 'edit any media_gallery content',
    'edit any mpx_player files' => 'edit any mpx_player files',
    'edit any promo_queue queue' => 'edit any promo_queue queue',
    'edit any video files' => 'edit any video files',
    'edit collections' => 'edit collections',
    'edit meta tags' => 'edit meta tags',
    'edit own audio files' => 'edit own audio files',
    'edit own character_profile content' => 'edit own character_profile content',
    'edit own document files' => 'edit own document files',
    'edit own image files' => 'edit own image files',
    'edit own media_gallery content' => 'edit own media_gallery content',
    'edit own mpx_player files' => 'edit own mpx_player files',
    'edit own video files' => 'edit own video files',
    'flush caches' => 'flush caches',
    'generate features' => 'generate features',
    'import media' => 'import media',
    'manage content workflow' => 'manage content workflow',
    'manage features' => 'manage features',
    'notify of path changes' => 'notify of path changes',
    'oauth authorize any consumers' => 'oauth authorize any consumers',
    'oauth register any consumers' => 'oauth register any consumers',
    'override facebook stream details' => 'override facebook stream details',
    'post to site-wide facebook stream' => 'post to site-wide facebook stream',
    'post to twitter' => 'post to twitter',
    'revert revisions' => 'revert revisions',
    'schedule exportables' => 'schedule exportables',
    'schedule revisions' => 'schedule revisions',
    'select account cancellation method' => 'select account cancellation method',
    'stick to Acquia web node' => 'stick to Acquia web node',
    'submit latitude/longitude' => 'submit latitude/longitude',
    'switch shortcut sets' => 'switch shortcut sets',
    'sync mpx_player' => 'sync mpx_player',
    'sync mpx_video' => 'sync mpx_video',
    'use PHP for title patterns' => 'use PHP for title patterns',
    'use publisher utilities' => 'use publisher utilities',
    'use text format ds_code' => 'use text format ds_code',
    'use text format wysiwyg_basic' => 'use text format wysiwyg_basic',
    'use text format wysiwyg_mini' => 'use text format wysiwyg_mini',
    'use workbench_moderation my drafts tab' => 'use workbench_moderation my drafts tab',
    'use workbench_moderation needs review tab' => 'use workbench_moderation needs review tab',
    'view all unpublished content' => 'view all unpublished content',
    'view collections' => 'view collections',
    'view files' => 'view files',
    'view interactive information bar' => 'view interactive information bar',
    'view location directory' => 'view location directory',
    'view node location table' => 'view node location table',
    'view own files' => 'view own files',
    'view own private files' => 'view own private files',
    'view own unpublished content' => 'view own unpublished content',
    'view own unpublished files' => 'view own unpublished files',
    'view private files' => 'view private files',
    'view revisions' => 'view revisions',
    'view the administration theme' => 'view the administration theme',
    'view user location table' => 'view user location table',
  );
  $export['publisher_admin_permissions_set'] = $permission_set;

  $permission_set = new stdClass();
  $permission_set->disabled = FALSE; /* Edit this to true to make a default permission_set disabled initially */
  $permission_set->api_version = 1;
  $permission_set->machinename = 'publisher_anonymous_user_permissions_set';
  $permission_set->name = 'Publisher Anonymous User Permissions Set';
  $permission_set->permissions = array(
    'access comments' => 'access comments',
    'access content' => 'access content',
    'access overlay' => 'access overlay',
    'view files' => 'view files',
  );
  $export['publisher_anonymous_user_permissions_set'] = $permission_set;

  $permission_set = new stdClass();
  $permission_set->disabled = FALSE; /* Edit this to true to make a default permission_set disabled initially */
  $permission_set->api_version = 1;
  $permission_set->machinename = 'publisher_authenticated_user_permissions_set';
  $permission_set->name = 'Publisher Authenticated User Permissions Set';
  $permission_set->permissions = array(
    'access administration pages' => 'access administration pages',
    'access content' => 'access content',
    'access overlay' => 'access overlay',
    'administer shortcuts' => 'administer shortcuts',
    'cancel account' => 'cancel account',
    'change own username' => 'change own username',
    'check out documents' => 'check out documents',
    'customize shortcut links' => 'customize shortcut links',
    'switch shortcut sets' => 'switch shortcut sets',
    'view files' => 'view files',
  );
  $export['publisher_authenticated_user_permissions_set'] = $permission_set;

  $permission_set = new stdClass();
  $permission_set->disabled = FALSE; /* Edit this to true to make a default permission_set disabled initially */
  $permission_set->api_version = 1;
  $permission_set->machinename = 'publisher_editor_permissions_set';
  $permission_set->name = 'Publisher Editor Permissions Set';
  $permission_set->permissions = array(
    'access administration menu' => 'access administration menu',
    'access advanced_link autocomplete' => 'access advanced_link autocomplete',
    'access collection list' => 'access collection list',
    'access comments' => 'access comments',
    'access content overview' => 'access content overview',
    'access contextual links' => 'access contextual links',
    'access user profiles' => 'access user profiles',
    'access workbench' => 'access workbench',
    'add authenticated twitter accounts' => 'add authenticated twitter accounts',
    'add media from remote sources' => 'add media from remote sources',
    'add twitter accounts' => 'add twitter accounts',
    'administer comments' => 'administer comments',
    'administer content revisions' => 'administer content revisions',
    'administer filters' => 'administer filters',
    'administer menu' => 'administer menu',
    'administer meta tags' => 'administer meta tags',
    'administer mpx account' => 'administer mpx account',
    'administer nodes' => 'administer nodes',
    'administer queue' => 'administer queue',
    'administer SiteCatalyst configuration' => 'administer SiteCatalyst configuration',
    'administer taxonomy' => 'administer taxonomy',
    'administer twitter accounts' => 'administer twitter accounts',
    'clone node' => 'clone node',
    'clone own nodes' => 'clone own nodes',
    'create character_profile content' => 'create character_profile content',
    'create collections' => 'create collections',
    'create files' => 'create files',
    'create media_gallery content' => 'create media_gallery content',
    'create movie content' => 'create movie content',
    'create person content' => 'create person content',
    'create post content' => 'create post content',
    'create tv_episode content' => 'create tv_episode content',
    'create tv_season content' => 'create tv_season content',
    'create tv_show content' => 'create tv_show content',
    'create url aliases' => 'create url aliases',
    'delete any audio files' => 'delete any audio files',
    'delete any character_profile content' => 'delete any character_profile content',
    'delete any document files' => 'delete any document files',
    'delete any image files' => 'delete any image files',
    'delete any media_gallery content' => 'delete any media_gallery content',
    'delete any movie content' => 'delete any movie content',
    'delete any mpx_video files' => 'delete any mpx_video files',
    'delete any person content' => 'delete any person content',
    'delete any post content' => 'delete any post content',
    'delete any tv_episode content' => 'delete any tv_episode content',
    'delete any tv_season content' => 'delete any tv_season content',
    'delete any tv_show content' => 'delete any tv_show content',
    'delete any video files' => 'delete any video files',
    'delete collections' => 'delete collections',
    'delete own audio files' => 'delete own audio files',
    'delete own character_profile content' => 'delete own character_profile content',
    'delete own document files' => 'delete own document files',
    'delete own image files' => 'delete own image files',
    'delete own media_gallery content' => 'delete own media_gallery content',
    'delete own movie content' => 'delete own movie content',
    'delete own mpx_video files' => 'delete own mpx_video files',
    'delete own person content' => 'delete own person content',
    'delete own post content' => 'delete own post content',
    'delete own tv_episode content' => 'delete own tv_episode content',
    'delete own tv_season content' => 'delete own tv_season content',
    'delete own tv_show content' => 'delete own tv_show content',
    'delete own video files' => 'delete own video files',
    'delete revisions' => 'delete revisions',
    'delete terms in 1' => 'delete terms in 1',
    'delete terms in 11' => 'delete terms in 11',
    'delete terms in 16' => 'delete terms in 16',
    'delete terms in 21' => 'delete terms in 21',
    'delete terms in 26' => 'delete terms in 26',
    'delete terms in 31' => 'delete terms in 31',
    'delete terms in 36' => 'delete terms in 36',
    'delete terms in 41' => 'delete terms in 41',
    'delete terms in 46' => 'delete terms in 46',
    'delete terms in 51' => 'delete terms in 51',
    'delete terms in 56' => 'delete terms in 56',
    'delete terms in 6' => 'delete terms in 6',
    'delete terms in 61' => 'delete terms in 61',
    'download any audio files' => 'download any audio files',
    'download any document files' => 'download any document files',
    'download any image files' => 'download any image files',
    'download any mpx_player files' => 'download any mpx_player files',
    'download any mpx_video files' => 'download any mpx_video files',
    'download any mpx_video_1 files' => 'download any mpx_video_1 files',
    'download any mpx_video_6 files' => 'download any mpx_video_6 files',
    'download any video files' => 'download any video files',
    'download own audio files' => 'download own audio files',
    'download own document files' => 'download own document files',
    'download own image files' => 'download own image files',
    'download own mpx_player files' => 'download own mpx_player files',
    'download own mpx_video files' => 'download own mpx_video files',
    'download own mpx_video_1 files' => 'download own mpx_video_1 files',
    'download own mpx_video_6 files' => 'download own mpx_video_6 files',
    'download own video files' => 'download own video files',
    'edit any audio files' => 'edit any audio files',
    'edit any character_profile content' => 'edit any character_profile content',
    'edit any document files' => 'edit any document files',
    'edit any image files' => 'edit any image files',
    'edit any media_gallery content' => 'edit any media_gallery content',
    'edit any movie content' => 'edit any movie content',
    'edit any mpx_player files' => 'edit any mpx_player files',
    'edit any mpx_video files' => 'edit any mpx_video files',
    'edit any mpx_video_1 files' => 'edit any mpx_video_1 files',
    'edit any mpx_video_6 files' => 'edit any mpx_video_6 files',
    'edit any person content' => 'edit any person content',
    'edit any post content' => 'edit any post content',
    'edit any promo_queue queue' => 'edit any promo_queue queue',
    'edit any promo_queue_kearns queue' => 'edit any promo_queue_kearns queue',
    'edit any tv_episode content' => 'edit any tv_episode content',
    'edit any tv_season content' => 'edit any tv_season content',
    'edit any tv_show content' => 'edit any tv_show content',
    'edit any video files' => 'edit any video files',
    'edit collections' => 'edit collections',
    'edit meta tags' => 'edit meta tags',
    'edit own audio files' => 'edit own audio files',
    'edit own character_profile content' => 'edit own character_profile content',
    'edit own document files' => 'edit own document files',
    'edit own image files' => 'edit own image files',
    'edit own media_gallery content' => 'edit own media_gallery content',
    'edit own movie content' => 'edit own movie content',
    'edit own mpx_player files' => 'edit own mpx_player files',
    'edit own mpx_video files' => 'edit own mpx_video files',
    'edit own mpx_video_1 files' => 'edit own mpx_video_1 files',
    'edit own mpx_video_6 files' => 'edit own mpx_video_6 files',
    'edit own person content' => 'edit own person content',
    'edit own post content' => 'edit own post content',
    'edit own tv_episode content' => 'edit own tv_episode content',
    'edit own tv_season content' => 'edit own tv_season content',
    'edit own tv_show content' => 'edit own tv_show content',
    'edit own video files' => 'edit own video files',
    'edit terms in 1' => 'edit terms in 1',
    'edit terms in 11' => 'edit terms in 11',
    'edit terms in 16' => 'edit terms in 16',
    'edit terms in 21' => 'edit terms in 21',
    'edit terms in 26' => 'edit terms in 26',
    'edit terms in 31' => 'edit terms in 31',
    'edit terms in 36' => 'edit terms in 36',
    'edit terms in 41' => 'edit terms in 41',
    'edit terms in 46' => 'edit terms in 46',
    'edit terms in 51' => 'edit terms in 51',
    'edit terms in 56' => 'edit terms in 56',
    'edit terms in 6' => 'edit terms in 6',
    'edit terms in 61' => 'edit terms in 61',
    'import media' => 'import media',
    'override facebook stream details' => 'override facebook stream details',
    'post comments' => 'post comments',
    'post to site-wide facebook stream' => 'post to site-wide facebook stream',
    'post to twitter' => 'post to twitter',
    'revert revisions' => 'revert revisions',
    'schedule revisions' => 'schedule revisions',
    'stick to Acquia web node' => 'stick to Acquia web node',
    'sync mpx_player' => 'sync mpx_player',
    'sync mpx_video' => 'sync mpx_video',
    'use text format ds_code' => 'use text format ds_code',
    'use text format markdown' => 'use text format markdown',
    'use text format wysiwyg_basic' => 'use text format wysiwyg_basic',
    'use text format wysiwyg_mini' => 'use text format wysiwyg_mini',
    'view all unpublished content' => 'view all unpublished content',
    'view collections' => 'view collections',
    'view interactive information bar' => 'view interactive information bar',
    'view moderation messages' => 'view moderation messages',
    'view own files' => 'view own files',
    'view own private files' => 'view own private files',
    'view own unpublished content' => 'view own unpublished content',
    'view private files' => 'view private files',
    'view revisions' => 'view revisions',
    'view the administration theme' => 'view the administration theme',
  );
  $export['publisher_editor_permissions_set'] = $permission_set;

  $permission_set = new stdClass();
  $permission_set->disabled = FALSE; /* Edit this to true to make a default permission_set disabled initially */
  $permission_set->api_version = 1;
  $permission_set->machinename = 'publisher_senior_editor_permissions_set';
  $permission_set->name = 'Publisher Senior Editor Permissions Set';
  $permission_set->permissions = array(
    'access administration menu' => 'access administration menu',
    'access administration pages' => 'access administration pages',
    'access advanced_link autocomplete' => 'access advanced_link autocomplete',
    'access collection list' => 'access collection list',
    'access comments' => 'access comments',
    'access content overview' => 'access content overview',
    'access contextual links' => 'access contextual links',
    'access user profiles' => 'access user profiles',
    'access workbench' => 'access workbench',
    'add authenticated twitter accounts' => 'add authenticated twitter accounts',
    'add media from remote sources' => 'add media from remote sources',
    'add twitter accounts' => 'add twitter accounts',
    'administer checked out documents' => 'administer checked out documents',
    'administer comments' => 'administer comments',
    'administer content revisions' => 'administer content revisions',
    'administer filters' => 'administer filters',
    'administer menu' => 'administer menu',
    'administer meta tags' => 'administer meta tags',
    'administer mpx account' => 'administer mpx account',
    'administer nodes' => 'administer nodes',
    'administer queue' => 'administer queue',
    'administer SiteCatalyst configuration' => 'administer SiteCatalyst configuration',
    'administer taxonomy' => 'administer taxonomy',
    'administer twitter accounts' => 'administer twitter accounts',
    'clone node' => 'clone node',
    'clone own nodes' => 'clone own nodes',
    'create character_profile content' => 'create character_profile content',
    'create collections' => 'create collections',
    'create files' => 'create files',
    'create media_gallery content' => 'create media_gallery content',
    'create movie content' => 'create movie content',
    'create person content' => 'create person content',
    'create post content' => 'create post content',
    'create tv_episode content' => 'create tv_episode content',
    'create tv_season content' => 'create tv_season content',
    'create tv_show content' => 'create tv_show content',
    'create url aliases' => 'create url aliases',
    'delete any audio files' => 'delete any audio files',
    'delete any character_profile content' => 'delete any character_profile content',
    'delete any document files' => 'delete any document files',
    'delete any image files' => 'delete any image files',
    'delete any media_gallery content' => 'delete any media_gallery content',
    'delete any movie content' => 'delete any movie content',
    'delete any mpx_video files' => 'delete any mpx_video files',
    'delete any person content' => 'delete any person content',
    'delete any post content' => 'delete any post content',
    'delete any tv_episode content' => 'delete any tv_episode content',
    'delete any tv_season content' => 'delete any tv_season content',
    'delete any tv_show content' => 'delete any tv_show content',
    'delete any video files' => 'delete any video files',
    'delete collections' => 'delete collections',
    'delete own audio files' => 'delete own audio files',
    'delete own character_profile content' => 'delete own character_profile content',
    'delete own document files' => 'delete own document files',
    'delete own image files' => 'delete own image files',
    'delete own media_gallery content' => 'delete own media_gallery content',
    'delete own movie content' => 'delete own movie content',
    'delete own mpx_video files' => 'delete own mpx_video files',
    'delete own person content' => 'delete own person content',
    'delete own post content' => 'delete own post content',
    'delete own tv_episode content' => 'delete own tv_episode content',
    'delete own tv_season content' => 'delete own tv_season content',
    'delete own tv_show content' => 'delete own tv_show content',
    'delete own video files' => 'delete own video files',
    'delete revisions' => 'delete revisions',
    'delete terms in 1' => 'delete terms in 1',
    'delete terms in 11' => 'delete terms in 11',
    'delete terms in 16' => 'delete terms in 16',
    'delete terms in 21' => 'delete terms in 21',
    'delete terms in 26' => 'delete terms in 26',
    'delete terms in 31' => 'delete terms in 31',
    'delete terms in 36' => 'delete terms in 36',
    'delete terms in 41' => 'delete terms in 41',
    'delete terms in 46' => 'delete terms in 46',
    'delete terms in 51' => 'delete terms in 51',
    'delete terms in 56' => 'delete terms in 56',
    'delete terms in 6' => 'delete terms in 6',
    'delete terms in 61' => 'delete terms in 61',
    'download any audio files' => 'download any audio files',
    'download any document files' => 'download any document files',
    'download any image files' => 'download any image files',
    'download any mpx_player files' => 'download any mpx_player files',
    'download any mpx_video files' => 'download any mpx_video files',
    'download any mpx_video_1 files' => 'download any mpx_video_1 files',
    'download any mpx_video_6 files' => 'download any mpx_video_6 files',
    'download any video files' => 'download any video files',
    'download own audio files' => 'download own audio files',
    'download own document files' => 'download own document files',
    'download own image files' => 'download own image files',
    'download own mpx_player files' => 'download own mpx_player files',
    'download own mpx_video files' => 'download own mpx_video files',
    'download own mpx_video_1 files' => 'download own mpx_video_1 files',
    'download own mpx_video_6 files' => 'download own mpx_video_6 files',
    'download own video files' => 'download own video files',
    'edit any audio files' => 'edit any audio files',
    'edit any character_profile content' => 'edit any character_profile content',
    'edit any document files' => 'edit any document files',
    'edit any image files' => 'edit any image files',
    'edit any media_gallery content' => 'edit any media_gallery content',
    'edit any movie content' => 'edit any movie content',
    'edit any mpx_player files' => 'edit any mpx_player files',
    'edit any mpx_video files' => 'edit any mpx_video files',
    'edit any mpx_video_1 files' => 'edit any mpx_video_1 files',
    'edit any mpx_video_6 files' => 'edit any mpx_video_6 files',
    'edit any person content' => 'edit any person content',
    'edit any post content' => 'edit any post content',
    'edit any promo_queue queue' => 'edit any promo_queue queue',
    'edit any promo_queue_kearns queue' => 'edit any promo_queue_kearns queue',
    'edit any tv_episode content' => 'edit any tv_episode content',
    'edit any tv_season content' => 'edit any tv_season content',
    'edit any tv_show content' => 'edit any tv_show content',
    'edit any video files' => 'edit any video files',
    'edit collections' => 'edit collections',
    'edit meta tags' => 'edit meta tags',
    'edit own audio files' => 'edit own audio files',
    'edit own character_profile content' => 'edit own character_profile content',
    'edit own document files' => 'edit own document files',
    'edit own image files' => 'edit own image files',
    'edit own media_gallery content' => 'edit own media_gallery content',
    'edit own movie content' => 'edit own movie content',
    'edit own mpx_player files' => 'edit own mpx_player files',
    'edit own mpx_video files' => 'edit own mpx_video files',
    'edit own mpx_video_1 files' => 'edit own mpx_video_1 files',
    'edit own mpx_video_6 files' => 'edit own mpx_video_6 files',
    'edit own person content' => 'edit own person content',
    'edit own post content' => 'edit own post content',
    'edit own tv_episode content' => 'edit own tv_episode content',
    'edit own tv_season content' => 'edit own tv_season content',
    'edit own tv_show content' => 'edit own tv_show content',
    'edit own video files' => 'edit own video files',
    'edit terms in 1' => 'edit terms in 1',
    'edit terms in 11' => 'edit terms in 11',
    'edit terms in 16' => 'edit terms in 16',
    'edit terms in 21' => 'edit terms in 21',
    'edit terms in 26' => 'edit terms in 26',
    'edit terms in 31' => 'edit terms in 31',
    'edit terms in 36' => 'edit terms in 36',
    'edit terms in 41' => 'edit terms in 41',
    'edit terms in 46' => 'edit terms in 46',
    'edit terms in 51' => 'edit terms in 51',
    'edit terms in 56' => 'edit terms in 56',
    'edit terms in 6' => 'edit terms in 6',
    'edit terms in 61' => 'edit terms in 61',
    'import media' => 'import media',
    'override facebook stream details' => 'override facebook stream details',
    'post comments' => 'post comments',
    'post to site-wide facebook stream' => 'post to site-wide facebook stream',
    'post to twitter' => 'post to twitter',
    'revert revisions' => 'revert revisions',
    'schedule revisions' => 'schedule revisions',
    'stick to Acquia web node' => 'stick to Acquia web node',
    'sync mpx_player' => 'sync mpx_player',
    'sync mpx_video' => 'sync mpx_video',
    'use text format markdown' => 'use text format markdown',
    'use text format wysiwyg_basic' => 'use text format wysiwyg_basic',
    'use text format wysiwyg_mini' => 'use text format wysiwyg_mini',
    'view all unpublished content' => 'view all unpublished content',
    'view collections' => 'view collections',
    'view interactive information bar' => 'view interactive information bar',
    'view moderation messages' => 'view moderation messages',
    'view own files' => 'view own files',
    'view own private files' => 'view own private files',
    'view own unpublished content' => 'view own unpublished content',
    'view private files' => 'view private files',
    'view revisions' => 'view revisions',
    'view the administration theme' => 'view the administration theme',
  );
  $export['publisher_senior_editor_permissions_set'] = $permission_set;

  return $export;
}
