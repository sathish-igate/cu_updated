<?php

/**
 * @file
 * TVE Auth Example template.
 *
 * @ingroup tve_auth_example
 */
?>

<?php if (!$mvpd_configured || !$adobe_pass_configured || !$jquery_version_ok): ?>
  <div class="tve-auth-example-notes messages error">
    <ul class="notes">
      <?php if (!$mvpd_configured): ?>
        <li>The MVPD Connection must be <a href="/admin/config/services/mvpd/connection">setup</a>.</li>
      <?php endif; ?>
      <?php if (!$adobe_pass_configured): ?>
        <li>The Adobe Pass configuration must be <a href="/admin/config/services/adobe-pass">setup</a>.</li>
      <?php endif; ?>
      <?php if (!$jquery_version_ok): ?>
        <li><a href="/admin/config/development/jquery_update">Configure jQuery</a> to use version 1.7 or higher.</li>
      <?php endif; ?>
    </ul>
  </div>
<?php endif; ?>

<section id="authExample" class="tve-widget tve-auth-example">
  <button class="authCancelBtn hide"><?php print t('Cancel'); ?></button>

  <div>
    <h2><?php print t('User status'); ?></h2>
    <dl>
      <dt><?php print t('Authentication status checked:'); ?></dt>
      <dd class="authCheckStatus">unknown</dd>

      <dt><?php print t('Authenticated:'); ?></dt>
      <dd class="authN">unknown</dd>

      <dt><?php print t('Selected MVPD:'); ?></dt>
      <dd class="selectedMvpd">unknown</dd>
    </dl>
    <div class="logoutWrap hide"><button class="logoutBtn"><?php print t('Logout'); ?></button></div>
  </div>

  <div class="loginWrap hide">
    <h2><?php print t('MVPD picker'); ?></h2>
    <h3><?php print t('All MVPDs:'); ?></h3>
    <select class="allMvpds"></select>
    <input type="button" value="login" class="loginBtn"/>

    <hr/>

    <h3><?php print t('Featured MVPDs:'); ?></h3>
    <ul class="featuredMvpds clearfix"></ul>
  </div>

</section>
