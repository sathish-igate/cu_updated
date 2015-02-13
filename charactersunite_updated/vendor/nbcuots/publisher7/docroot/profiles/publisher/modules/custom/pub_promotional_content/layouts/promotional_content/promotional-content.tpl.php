<figure class="<?php print $classes; ?> clearfix">
  <?php if ($type == 'image'): ?>
  <a href="<?php if (isset($promo_link)) print $promo_link; ?>" <?php if (isset($promo_link_window)) print $promo_link_window; ?>>
  <?php endif; ?>
    <div class="media-wrapper clearfix">
      <?php if ($type != 'image'): ?>
      	<div class="click-capture"></div>
      <?php endif; ?>
      <?php if (isset($promo_marquee)): ?>
      	<aside class="promo-marquee <?php print $promo_marquee_position; ?>"><?php print $promo_marquee; ?></aside>
      <?php endif; ?>
      <?php if (!empty($promo_media_render)) { ?>
      	<?php print render($promo_media_render); ?>
      <?php }else{ ?>
      	<?php print $media; ?>
      <?php } ?>
    </div>
    <?php if ($type != 'image'): ?>
      <a href="<?php if (isset($promo_link)) print $promo_link; ?>" <?php if (isset($promo_link_window)) print $promo_link_window?>>
    <?php endif; ?>
    <figcaption class="clearfix">
      <?php if (isset($promo_title)): ?>
        <?php print $promo_title; ?>
      <?php endif; ?>
      <?php if (isset($promo_details)): ?>
      	<span class="details">
      	  <?php print $promo_details; ?>
      	</span>
      <?php endif; ?>
    </figcaption>
  </a>
</figure>