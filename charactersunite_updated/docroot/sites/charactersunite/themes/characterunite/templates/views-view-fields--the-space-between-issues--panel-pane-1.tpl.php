<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<?php if (isset($row->field_field_sbi_image) || isset($row->field_field_sbi_section_title)): ?>
  <div class="colMain l-spaceTop">
    <img src="<?php echo file_create_url($row->field_field_sbi_image[0]['raw']['uri']);?>" alt="<?php echo $row->field_field_sbi_section_title[0]['raw']['value']; ?>" />
  </div>
<?php endif; ?>
<?php if (isset($row->field_field_sbi_section_title) || isset($row->field_field_sbi_section_description) || isset($row->field_field_sbi_section_link)): ?>
  <div class="colSide l-spaceTop">
    <div class="mod solid headline issueColSideDesc">
      <?php if (isset($row->field_field_sbi_section_title)): ?>
        <h2 class="title"><strong><?php echo $row->field_field_sbi_section_title[0]['raw']['value'];?></strong></h2>
      <?php endif; ?>
      <?php if (isset($row->field_field_sbi_section_description)): ?>
        <?php if (strlen($row->field_field_sbi_section_description[0]['raw']['value']) > 300): ?>
          <span class="issuedesc" style="height:150px;">
            <?php print $row->field_field_sbi_section_description[0]['raw']['value']; ?>
          </span>
          <br/>
          <span class="issuedescspan"></span>
        <?php else: ?>
          <?php print $row->field_field_sbi_section_description[0]['raw']['value']; ?>
        <?php endif; ?>
      <?php endif; ?>
      <?php if (isset($row->field_field_sbi_section_link)): ?>
        <?php print  l($row->field_field_sbi_section_link[0]['raw']['title'], $row->field_field_sbi_section_link[0]['raw']['url'], array('attributes' => array('class' => 'cta uppercase'))); ?>
      <?php endif; ?>
    </div>
  </div>
<?php endif; ?>
