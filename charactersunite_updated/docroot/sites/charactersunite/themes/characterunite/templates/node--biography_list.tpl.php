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
<div class="initiativeMain bio-list">
  <div id="colMain">
    <?php if (isset($biography_list) && count($biography_list) > 0):?>
      <?php foreach ($biography_list as $id => $mainlist): ?>
        <?php if ($mainlist['field_bl_category_title'] != '' && $mainlist['field_bl_category_title'] != 'guest'): ?>
          <section>
            <h3>
              <?php print $mainlist['field_bl_category_title']; ?>
            </h3>
          </section>
        <?php endif;?>
        <?php foreach ($mainlist as $subid => $sublist): ?>
          <?php if (is_numeric($subid)): ?>
            <?php $class = (($mainlist['field_bl_category_title'] == 'guest')?' class="guest" ':''); ?>
            <article <?php print $class; ?> >
            <?php if ($sublist['field_bl_section_thumbnail'] != ''): ?>
              <?php $class = (($sublist['field_field_bl_section_info'] == '')?'partners-list':'featured'); ?>
              <img class="<?php print $class; ?>" src="<?php print file_create_url($sublist['field_bl_section_thumbnail']); ?>" alt="<?php print $sublist['field_bl_section_title']; ?>" />
            <?php endif; ?>
              <section>
                  <?php if ($sublist['field_bl_section_link_url'] != ''): ?>
                    <h2>
                      <?php print l($sublist['field_bl_section_title'], $sublist['field_bl_section_link_url'], array('attributes' => array('target' => $sublist['field_bl_section_link_target'], 'class' => 'uppercase')));?>
                    </h2>
                    <?php print $link = l($sublist['field_bl_section_link_title'], $sublist['field_bl_section_link_url'], array('attributes' => array('target' => $sublist['field_bl_section_link_target']))); ?>
                  <?php else: ?>
                    <h2><?php print $sublist['field_bl_section_title']; ?></h2>
                  <?php endif; ?>
                  <?php if ($sublist['field_bl_section_title_2'] != ''): ?>
                    <p>
                      <strong>
                        <?php print $sublist['field_bl_section_title_2']; ?>
                      </strong>
                    </p>
                  <?php endif; ?>
                  <?php if ($sublist['field_field_bl_section_info'] != ''): ?>
                    <p><?php print $sublist['field_field_bl_section_info']; ?></p>
                  <?php endif; ?>
                  <?php if ($sublist['field_bl_section_description'] != ''): ?>
                    <?php if (strlen($sublist['field_bl_section_description']) > 350): ?>
                      <span class="<?php print $subid;?>leftpane_desc" style="height:0px">
                        <?php print $sublist['field_bl_section_description']; ?><br/>
                        <p><?php print $link; ?></p>
                      </span>
                      <a class="<?php print $subid;?>leftpane_desc_more amore<?php print $subid;?>" href="javascript:;" onclick="LeftDesc('<?php print $subid;?>leftpane_desc', 'less', 0, '<?php print $subid;?>');">More</a>
                      <a class="<?php print $subid;?>leftpane_desc_less amore<?php print $subid;?>" href="javascript:;" onclick="LeftDesc('<?php print $subid;?>leftpane_desc', 'more', 0, '<?php print $subid;?>');">Less</a>
                    <?php else: ?>
                      <?php print $sublist['field_bl_section_description']; ?><br/>
                      <p><?php print $link; ?></p>
                    <?php endif; ?>                 
                  <?php endif; ?>
              </section>
            </article>
          <?php endif; ?>
        <?php endforeach; ?>
      <?php endforeach; ?>
    <?php endif; ?>
  </div> <!-- /#colMain -->
  <div id="colSide">
  </div>
</div> <!-- initiativeMain end -->
