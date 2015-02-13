<?php

/**
 * @file
 * Functions called by pub_commerce_example_post_features_revert().
 */

function pub_commerce_example_get_categories_array() {
  return array(
    'accessories'    => (object) array('name' => 'Accessories', 'weight' => 0),
    'bags'           => (object) array('name' => 'Bags', 'weight' => 0, 'parent' => 'accessories'),
    'tech'           => (object) array('name' => 'Tech', 'weight' => 1, 'parent' => 'accessories'),
    'apparel'        => (object) array('name' => 'Apparel', 'weight' => 0),
    'youth_t_shirts' => (object) array('name' => 'Youth T-Shirts', 'weight' => 0, 'parent' => 'apparel'),
    'headwear'       => (object) array('name' => 'Headwear', 'weight' => 0),
  );
}

function pub_commerce_example_get_color_array() {
  return array(
    'blue' => (object) array('name' => 'BLUE', 'weight' => 0),
    'grey' => (object) array('name' => 'GREY', 'weight' => 1),
  );
}

function pub_commerce_example_get_size_array() {
  return array(
    'sm'  => (object) array('name' => 'SM', 'weight' => 0),
    'md'  => (object) array('name' => 'MD', 'weight' => 1),
    'lg'  => (object) array('name' => 'LG', 'weight' => 2),
    'xlg' => (object) array('name' => 'XLG', 'weight' => 3),
  );
}

function pub_commerce_example_get_skus_array() {
  return array(
    'bags1' => 'example-bag-1',
    'bags2' => 'example-bag-2',
    'headwear1' => 'example-headwear-1',
    'tech1' => 'example-tech-1',
    'youth_t_shirts' => 'example-youthtshirt',
  );
}

function pub_commerce_example_insert_example_product_bags1($sku_key, $sku, $categories, $color, $size) {
  $amount = 999;
  $filename = 'Accessories_Bags_UniversalStudiosDrawstringBackpack.jpg';
  $language = LANGUAGE_NONE;
  $terms = array();
  $terms[] = substr($sku_key, 0, -1);
  $terms[] = ('accessories');
  $title = 'Universal Studios Drawstring Backpack';
  $body = "Convenient and portable, this easy-cinch drawstring back pack is light weight and durable. The Universal Studios logo is screen printed in full color against basic black to stand out. This pack works perfectly as an extra day bag.\n\nTM & © Universal Studios";

  pub_commerce_example_save_example_product($sku, $title, $language, $amount, $filename, $body, $terms, $categories);
}

function pub_commerce_example_insert_example_product_bags2($sku_key, $sku, $categories, $color, $size) {
  $amount = 2495;
  $filename = 'Accessories_Bags_UniversalStudiosBlackToteBag.jpg';
  $language = LANGUAGE_NONE;
  $terms = array();
  $terms[] = substr($sku_key, 0, -1);
  $terms[] = ('accessories');
  $title = 'Universal Studios Black Tote Bag';
  $body = "This go-anywhere tote is durable and spacious. The exterior zippered front pocket features a Universal Studios globe. Dual outside mesh pockets easily hold bottled beverages. This sharp nylon bag has black handle straps and a reinforced bottom.\n\nTM & © Universal Studios";

  pub_commerce_example_save_example_product($sku, $title, $language, $amount, $filename, $body, $terms, $categories);
}

function pub_commerce_example_insert_example_product_headwear1($sku_key, $sku, $categories, $color, $size) {
  $amount = 2195;
  $filename = 'Headwear_UniversalStudiosFloridaBlackEmbroideredAdultCap.jpg';
  $language = LANGUAGE_NONE;
  $terms = array();
  $terms[] = substr($sku_key, 0, -1);
  $title = 'Universal Studios Florida Black Embroidered Adult Cap';
  $body = "This classic Universal Studios logo hat is our most popular. The sandwich bill and velcro back strap are constructed for comfort and a life time of wear. A six panel structured crown features an embroidered, full color Universal Studios Florida logo.\n\nTM & © Universal Studios";

  pub_commerce_example_save_example_product($sku, $title, $language, $amount, $filename, $body, $terms, $categories);
}

function pub_commerce_example_insert_example_product_tech1($sku_key, $sku, $categories, $color, $size) {
  $amount = 3995;
  $filename = 'Despicable-Me-Grey-Case-For-iPad.jpg';
  $language = LANGUAGE_NONE;
  $terms = array();
  $terms[] = substr($sku_key, 0, -1);
  $terms[] = ('accessories');
  $title = 'Despicable Me™ Grey Case For iPad®';
  $body = "A tech accessory that even Gru would approve of! Light grey case features repeating minions for a must-have look! Fits second, third and fourth-generation iPads. A practical stand with multiple display angles is included.

• Plastic case
• Fits second, third and fourth-generation iPads
• Includes stand
• Imported

iPad is a registered trademark of Apple Inc.

Despicable Me is a TM and © of Universal Studios. Licensed by Universal Studios Licensing LLC. All rights reserved.";

  pub_commerce_example_save_example_product($sku, $title, $language, $amount, $filename, $body, $terms, $categories);
}

function pub_commerce_example_insert_example_product_youth_t_shirts($sku_key, $sku, $categories, $color, $size) {
  $amount = 1499;
  $language = LANGUAGE_NONE;
  $terms = array();
  $terms[] = $sku_key;
  $terms[] = ('apparel');
  $title = 'Universal Studios Florida™ Star Logo Youth T-Shirt';
  $body = "This variation on a classic is a must-have for Universal fans. An overlay of stars provides a colorful perspective to a monochromatic logo on the center front of this youth t-shirt.

• 60% Cotton/40% Polyester
• Screen-printed features
• Machine wash
• Imported

TM & © Universal Studios";

  $i = 1;
  // Create and save the product variations.
  foreach ($color as $ckey => $cvalue) {
    if (empty($cvalue->tid)) continue;

    if ($ckey== 'blue') {
      $filename = 'Youth-T-Shirt-US-STARGLB-TEE-BLUE.jpg';
    } else {
      $filename = 'Youth-T-Shirt-US-STARGLB-TEE-GREY.jpg';
    }

    foreach ($size as $skey => $svalue) {
      if (empty($svalue->tid)) continue;

      $product = pub_commerce_example_get_product_entity_object("$sku-$skey-$ckey-$i", $title, $language, $amount, $filename);
      $product->field_color[$language][]['tid'] = $cvalue->tid;
      $product->field_size[$language][]['tid'] = $svalue->tid;
      commerce_product_save($product);

      // Only create the node if commerce_product_save() was successful.
      if (!empty($product->product_id)) {
        if (empty($node)) {
          $node = pub_commerce_example_get_product_node_object($title, $language, $body, $terms, $product, $categories);
        } else {
          $node->field_product[$language][]['product_id'] = $product->product_id;
        }
      }
      $i++;
    }
  }
  // Save the node once and only once.
  $node = node_submit($node);
  node_save($node);
}

function pub_commerce_example_save_example_product($sku, $title, $language, $amount, $filename, $body, $terms, $categories) {
  // Create and save the product entity.
  $product = pub_commerce_example_get_product_entity_object($sku, $title, $language, $amount, $filename);
  commerce_product_save($product);

  // Only create the node if commerce_product_save() was successful.
  if (!empty($product->product_id)) {
    $node = pub_commerce_example_get_product_node_object($title, $language, $body, $terms, $product, $categories);
    $node = node_submit($node);
    node_save($node);
  }
}

function pub_commerce_example_get_product_entity_object($sku, $title, $language, $amount, $filename) {
  $product = commerce_product_new('product');
  $product->sku = $sku;
  $product->title = $title;
  $product->language = $language;
  $product->uid = 1;
  $product->status = 1;

  // Set up field data.
  $commerce_price = array($language => array(array(
    'amount' => $amount,
    'currency_code' => commerce_default_currency(),
    'data' => array('components' => array()),
  )));
  $product->commerce_price = $commerce_price;

  $path = drupal_get_path('module', 'pub_commerce_example');
  $image = file_get_contents($path . '/images/' . $filename);
  $file = file_save_data($image, 'public://' . $filename, FILE_EXISTS_REPLACE);
  $field_images = array($language => array(array(
    'fid' => $file->fid,
    'alt' => $title,
    'title' => $title,
    'width' => $file->metadata['width'],
    'height' => $file->metadata['height'],
  )));
  $product->field_images = $field_images;

  return $product;
}

function pub_commerce_example_get_product_node_object($title, $language, $body, $terms, $product, $categories) {
  $node = new stdClass();
  $node->title = $title;
  $node->type = 'product';
  // Sets some defaults. Invokes hook_prepare() and hook_node_prepare().
  node_object_prepare($node);
  $node->language = $language;
  $node->uid = 1;
  $node->status = 1;
  $node->comment = 0;
  $node->promote = 0;

  // Set up field data.
  $field_body = array($language => array(array(
    'value' => $body,
    'summary' => '',
    'format' => 'plain_text',
  )));
  $node->body = $field_body;
  foreach ($terms as $term) {
    $node->field_categories[$language][]['tid'] = $categories[$term]->tid;
  }
  $node->field_product[$language][]['product_id'] = $product->product_id;

  return $node;
}
