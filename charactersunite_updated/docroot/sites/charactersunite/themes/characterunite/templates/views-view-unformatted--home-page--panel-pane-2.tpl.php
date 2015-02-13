<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
 //print_r($rows);
?>
<?php foreach ($rows as $id => $row): ?>
    <div class="section">
      <?php preg_match('#(<img.*?>)#', $row, $image); ?>
      <?php $row = preg_replace('#(<img.*?>)#', '', $row); ?>      
      <div class="sectionText">
      <?php print $row; ?>
      </div>
      <?php print $image[0]; ?>
    </div>
<?php endforeach; ?>
