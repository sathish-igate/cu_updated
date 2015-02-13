<?php

/**
 * @file
 * Characterunite's theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *   "Blog entry" it would result in "node-blog". Note that the machine
 *   name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *   listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */

?>
<div class="showcaseMain layoutWide">
  <div id="colMain">
    <!-- Video Section -->
    <div class="videoFrame">
      <iframe src="http://player.theplatform.com/p/OyMl-B/oIChOKSBFJ6b/select/<?php print $field_video_id; ?>" width="688" height="387" frameborder="0" scrolling="no"></iframe>
    </div>
    <?php if ($field_transcript_title != '' || $field_transcript_description != ''): ?>
      <div class="mod full caption clearfix">
        <h1>
          <?php print $field_transcript_title; ?>
        </h1>
        <?php if ($field_transcript_more_link != 0 && $field_transcript_description != ''): ?>
          <h2>
            <span class="Tpane_desc" style="height:50px">
              <?php print $field_transcript_description; ?>
            </span>
          </h2>
          <a class="Tpane_desc_more atmore" href="javascript:;" onclick="TDesc('Tpane_desc', 'less', 50, '');">More</a>
          <a class="Tpane_desc_less atmore" href="javascript:;" onclick="TDesc('Tpane_desc', 'more', 50, '');">Less</a>
        <?php elseif ($field_transcript_more_link == 0 && $field_transcript_description != ''): ?>
          <h2>
            <?php print $field_transcript_description; ?>
          </h2>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <!-- Banner -->
    <?php if ($field_issues_banner != '') : ?>
      <div class="svu-nomore-im">
        <?php if ($field_issues_banner_link != ''): ?>
          <a href="<?php print $field_issues_banner_link; ?>" target="<?php print $field_issues_banner_target; ?>">
            <img src="<?php print file_create_url($field_issues_banner); ?>">
          </a>
        <?php else: ?>
          <img src="<?php print file_create_url($field_issues_banner); ?>">
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <!-- Take Action Section -->
    <?php if (isset($take_action) && count($take_action) > 0): ?>
      <?php foreach ($take_action as $id => $take_action_fields): ?>   
        <div class="takeActionFrame">
          <div class="takeActionHeader">
            <h2 class="blackhead">
              <?php print (!empty($take_action_fields['field_take_action_title_1'])?$take_action_fields['field_take_action_title_1']:'');?> 
              <strong>
                <?php print (!empty($take_action_fields['field_take_action_title_2'])?$take_action_fields['field_take_action_title_2']:'');?> 
              </strong>
            </h2>
          </div>
          <div class="takeActionSection">
            <?php if (isset($take_action_fields['field_take_action_list']) && count($take_action_fields['field_take_action_list']) > 0): ?>
              <ul>
                <?php $field_take_action_list_count = count($take_action_fields['field_take_action_list']); ?>
                <?php for($action_list = 0; $action_list < $field_take_action_list_count; $action_list++): ?>
                  <li class="takeAction clearfix">
                      <header>
                        <?php print $take_action_fields['field_take_action_list'][$action_list]['value']; ?>
                      </header>
                  </li>
                <?php endfor; ?>
              </ul>
            <?php endif; ?>
          </div>
        </div>
      <?php endforeach; ?>
    <?php endif; ?>

    <!-- Facts Section -->
    <?php if (isset($facts) && count($facts) > 0): ?>
      <?php foreach ($facts as $id => $facts_fields): ?>
        <div class="resourcesAndFactsFrame">
          <div class="resourcesAndFactsHeader">
            <h2 class="blackhead">
              <?php print (!empty($facts_fields['field_facts_title_1'])?$facts_fields['field_facts_title_1']:'');?> 
              <strong>
                <?php print (!empty($facts_fields['field_facts_title_2'])?$facts_fields['field_facts_title_2']:'');?> 
              </strong>
            </h2>
          </div>
          <div class="theFactsSection">
            <?php if (isset($facts_fields['field_facts_list']) && count($facts_fields['field_facts_list']) > 0): ?>
              <ul>
                <?php $field_take_action_list_count = count($facts_fields['field_facts_list']); ?>
                <?php for($facts_list = 0; $facts_list < $field_take_action_list_count; $facts_list++): ?>
                  <li>
                      <header>
                        <?php print $facts_fields['field_facts_list'][$facts_list]['value']; ?>
                      </header>
                  </li>
                <?php endfor; ?>
              </ul>
            <?php endif; ?>
          </div>
        </div>
      <?php endforeach; ?>
    <?php endif; ?>
    
    <!-- Related Videos Left -->
    <?php if (isset($related_videos_left) && count($related_videos_left) > 0):?>
      <?php foreach ($related_videos_left as $id => $related_videos_fields): ?>
        <div class="mod full clearfix mod top-space">
          <div class="mainstageHeader">
            <h2 class="blackhead blackheadsmall">
              <?php print $related_videos_fields['field_related_videos_title_1']; ?> 
              <strong>
                <?php print $related_videos_fields['field_related_videos_title_2']; ?>
              </strong>
            </h2>
          </div>
          <section class="copy clearfix">
              <?php print $related_videos_fields['field_related_videos_description']; ?>
              <?php print $related_videos_fields['related_videos_link_tag']; ?>
                <?php foreach ($related_videos_fields['related_videos_iteration'] as $key => $iteration_fields): ?>
                  <?php $image_size = (getimagesize(file_create_url($iteration_fields['field_rvi_video_thumbnail']))); ?>
                  <?php $image_size_calss = ($image_size[0] < 100) ? 'playButton25' : 'playButton53 middlePlay'; ?>
                  <?php $backlash = (substr($iteration_fields['field_rvi_video_link_url'], 0, 4) != 'http' && substr($iteration_fields['field_rvi_video_link_url'], 0, 1) != '/' && $iteration_fields['field_rvi_video_link_url'] != '') ? '/' : ''; ?>                     
                   <div class="relatedVideos clearfix">
                    <a href="<?php print $backlash.$iteration_fields['field_rvi_video_link_url']; ?>" class="relatedVideosImage" target="<?php print $iteration_fields['field_rvi_video_link_target']; ?>">
                      <img alt="<?php print $iteration_fields['field_rvi_video_title']; ?>" src="<?php print file_create_url($iteration_fields['field_rvi_video_thumbnail']); ?>">
                      <div class="<?php print $image_size_calss; ?>"></div>
                    </a>                     
                    <?php /* $attributes = array('title' => $iteration_fields['field_rvi_video_title'], 'target' => $iteration_fields['field_rvi_video_link_target'], 'class' => 'relatedVideosImage'); ?>
                    <?php $options = array('html' => TRUE, 'attributes' => $attributes); ?>
                    <?php print $rvi_video_thumbnail_output = l(render($iteration_fields['field_rvi_video_thumbnail']) . '<div class="'.$image_size_calss.'"></div>', $iteration_fields['field_rvi_video_link_url'], $options); */ ?>                       
                    <div class="relatedVideosText">
                      <h2>
                        <?php print substr($iteration_fields['field_rvi_video_title'], 0, 45); ?>
                      </h2>
                      <p>
                        <?php print substr($iteration_fields['field_rvi_video_info'], 0, 45); ?>
                      </p>
                      <?php print l($iteration_fields['field_rvi_video_link_label'], $iteration_fields['field_rvi_video_link_url'], array('attributes' => array('target' => $iteration_fields['field_rvi_video_link_target']))); ?>
                    </div>
                  </div>
                <?php endforeach; ?>
          </section>
        </div>
      <?php endforeach; ?>
    <?php endif; ?>

    <!-- Related Images Left -->
    <?php if (isset($related_images_left) && count($related_images_left) > 0):?>
      <?php foreach ($related_images_left as $id => $related_images_fields): ?>
        <div class="mod full clearfix mod">
          <div class="mainstageHeader">
            <h2 class="blackhead blackheadsmall">
              <?php print $related_images_fields['field_related_image_title_1']; ?> 
              <strong>
                <?php print $related_images_fields['field_related_image_title_2']; ?>
              </strong>
            </h2>
          </div>
          <div id="sponsors" class="initiativeRightBody copy">
            <div>
              <?php print $related_images_fields['field_related_image_description']; ?>
            </div>
            <section class="copy clearfix">
              <?php foreach ($related_images_fields['related_images_iteration'] as $key => $iteration_fields): ?>
                <a href="<?php print $iteration_fields['field_rii_image_link_url']; ?>" target="<?php print $iteration_fields['field_rii_image_link_target']; ?>">
                  <img src="<?php print file_create_url($iteration_fields['field_rii_image']); ?>" alt="<?php print $iteration_fields['field_rii_image_link_label']; ?>" />
                </a>
              <?php endforeach; ?>
            </section>
            <?php print $related_images_fields['related_image_link_tag']; ?>
          </div>
        </div>
      <?php endforeach; ?>
    <?php endif; ?>

    <div class="clear"></div>
    <?php if ($region['facebook_discussion']): ?>
      <div class="social">
        <?php print render($region['facebook_discussion']); ?>
      </div>
    <?php endif; ?>
  </div> <!-- /#colMain -->

  <div id="colSide">
    <!-- Blackbox section -->
    <?php if (!(empty($node->field_black_box_section)) && ($field_black_box_title != '' || 
            $field_black_box_title_2 != '' || $field_black_box_description != '')): ?>
      <div class="mod solid">
        <?php if ($field_black_box_title != '' || $field_black_box_title_2 != ''): ?>
          <h2 class="title">
            <?php print $field_black_box_title; ?> 
            <br/>
            <small>
              <?php print $field_black_box_title_2; ?>
            </small>
          </h2>
        <?php endif; ?>
        <?php if ($field_black_box_more_link != 0): ?>
          <span class="blackpane_desc" style="height:250px">
            <?php print $field_black_box_description; ?>
          </span>
          <a class="blackpane_desc_more amore" href="javascript:;" onclick="LeftDesc('blackpane_desc', 'less', 250, '');">More</a>
          <a class="blackpane_desc_less amore" href="javascript:;" onclick="LeftDesc('blackpane_desc', 'more', 250, '');">Less</a>';
        <?php else: ?>
          <?php print $field_black_box_description; ?>
        <?php endif; ?>
        <?php if ($region['spread_the_word']): ?>
          <aside class="share">
          <?php print render($region['spread_the_word']); ?>
          </aside>
        <?php endif; ?>          
      </div>
    <?php endif; ?>

    <!-- Related videos right -->
    <?php if (isset($related_videos_right) && count($related_videos_right) > 0):?>
      <?php foreach ($related_videos_right as $id => $related_videos_fields): ?>
        <div class="mod">
          <div class="mainstageHeader">
            <h2 class="blackhead blackheadsmall">
              <?php print $related_videos_fields['field_related_videos_title_1']; ?> 
              <strong>
                <?php print $related_videos_fields['field_related_videos_title_2']; ?>
              </strong>
            </h2>
          </div>
          <div class="initiativeRightBody copy">
            <?php print $related_videos_fields['field_related_videos_description']; ?>
            <?php print $related_videos_fields['related_videos_link_tag']; ?>
              <div class="mainstageVideos clearfix">
              <?php foreach ($related_videos_fields['related_videos_iteration'] as $key => $iteration_fields): ?>
                <?php $image_size = (getimagesize(file_create_url($iteration_fields['field_rvi_video_thumbnail']))); ?>
                <?php $image_size_calss = ($image_size[0] < 100) ? 'playButton25' : 'playButton53 middlePlay'; ?>
                <?php $backlash = (substr($iteration_fields['field_rvi_video_link_url'], 0, 4) != 'http' && substr($iteration_fields['field_rvi_video_link_url'], 0, 1) != '/' && $iteration_fields['field_rvi_video_link_url'] != '') ? '/' : ''; ?>                  
                 <div class="relatedVideos clearfix">
                  <a href="<?php print $backlash.$iteration_fields['field_rvi_video_link_url']; ?>" class="relatedVideosImage" target="<?php print $iteration_fields['field_rvi_video_link_target']; ?>">
                    <img alt="<?php print $iteration_fields['field_rvi_video_title']; ?>" src="<?php print file_create_url($iteration_fields['field_rvi_video_thumbnail']); ?>">
                    <div class="<?php print $image_size_calss; ?>"></div>
                  </a>                   
                  <?php /* $attributes = array('title' => $iteration_fields['field_rvi_video_title'], 'target' => $iteration_fields['field_rvi_video_link_target'], 'class' => 'relatedVideosImage'); ?>
                  <?php $options = array('html' => TRUE, 'attributes' => $attributes); ?>
                  <?php print $rvi_video_thumbnail_output = l(render($iteration_fields['field_rvi_video_thumbnail']) . '<div class="'.$image_size_calss.'"></div>', $iteration_fields['field_rvi_video_link_url'], $options); */ ?>                    
                  <div class="relatedVideosText">
                    <h2>
                      <?php print substr($iteration_fields['field_rvi_video_title'], 0, 45); ?>
                    </h2>
                    <p>
                      <?php print substr($iteration_fields['field_rvi_video_info'], 0, 45); ?>
                    </p>
                    <?php print l($iteration_fields['field_rvi_video_link_label'], $iteration_fields['field_rvi_video_link_url'], array('attributes' => array('target' => $iteration_fields['field_rvi_video_link_target']))); ?>
                  </div>
                </div>
              <?php endforeach; ?>
              </div>
          </div>
        </div>
      <?php endforeach; ?>
    <?php endif; ?>

    <!-- Related Images right -->
    <?php if (isset($related_images_right) && count($related_images_right) > 0):?>
      <?php foreach ($related_images_right as $id => $related_images_fields): ?>
        <div class="mod">
          <div class="mainstageHeader">
            <h2 class="blackhead blackheadsmall">
              <?php print $related_images_fields['field_related_image_title_1']; ?> 
              <strong>
                <?php print $related_images_fields['field_related_image_title_2']; ?>
              </strong>
            </h2>
          </div>
          <div class="initiativeRightBody copy">
            <div>
              <?php print $related_images_fields['field_related_image_description']; ?>
            </div>
            <section class="copy">
              <?php foreach ($related_images_fields['related_images_iteration'] as $key => $iteration_fields): ?>
                <a href="<?php print $iteration_fields['field_rii_image_link_url']; ?>" target="<?php print $iteration_fields['field_rii_image_link_target']; ?>">
                  <img class="featured" src="<?php print file_create_url($iteration_fields['field_rii_image']); ?>" alt="<?php print $iteration_fields['field_rii_image_link_label']; ?>" border="0" width="180" style="margin-bottom: 30px;">
                </a>
              <?php endforeach; ?>
            </section>
            <?php print $related_images_fields['related_image_link_tag']; ?>
          </div>
        </div>
      <?php endforeach; ?>
    <?php endif; ?> 
  </div> <!-- /#colSide -->
</div> <!-- showcaseMain end -->
