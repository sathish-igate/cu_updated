<?php

/**
 * @file
 *   Template for a rendered state_flow_history_entity.
 */
?>
<?php
/**
 * @todo All classes should come fully formed from preprocess
 */
if ($from_state == '') {
 $from_state = 'Draft';
}
?>
<div class="state-flow-history-entity-hid-<?php print $hid ?>">
  <p class="state-flow-history-event">Revision <span>was set from</span> <?php print $from_state ?> to <span><?php print $state ?></span> on <?php print $formatted_timestamp ?> by <?php print $formatted_username ?></p>

  <?php // @todo What html element show wrap the log message? <p> ? Probably
        // not blockquote. ?>
  <blockquote><?php print $log; ?></blockquote>
    <div class="state-flow-history-entity-content">
      <?php print render($content) ?>
    </div>
</div>
