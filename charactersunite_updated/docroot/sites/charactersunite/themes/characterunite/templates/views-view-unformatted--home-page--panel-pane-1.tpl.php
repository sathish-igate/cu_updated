<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<div id="homescroll-container">
  <a class="prev browse left"></a>
    <div class="scrollable" id="homescroll">
      <div class="items">
        <?php foreach ($rows as $id => $row): ?>
          <div class="hsitem">
            <div class="hsfadeimg">
              <?php preg_match('#(<img.*?>)#', $row, $image); ?>
              <?php $row = preg_replace('#(<img.*?>)#', '', $row); ?>
              <div class="hscontent">
                <?php print $row; ?>
              </div>
              <?php print $image[0]; ?>
            </div>
          </div>
        <?php endforeach; ?>
      </div>
    </div>
  <a class="next browse right"></a>
</div>
