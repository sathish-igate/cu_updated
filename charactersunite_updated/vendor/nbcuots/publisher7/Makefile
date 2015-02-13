# NOTE: Make likes tabs, so the tabs are on purpose.
.PHONY: check-style check-style-ci
.PHONY: check-cpd check-cpd-ci
.PHONY: check-js check-js-ci
.PHONY: check-all-ci

# Both these command exit non-0 when any violations occur
# We want to ignore that so we can get all the results in jenkins
.IGNORE: check-style-ci check-cpd-ci check-pmd-ci check-phpunit-ci

# Variable for --ignore and --exclude patterns
exclude_patterns = *.features.*,*.context.inc,*.*_default.inc,*.default_permission_sets.inc,*.default_mps_tags.inc,*.field_group.inc,*.strongarm.inc,*.quicktabs.inc,*.tpl.php

# A fancy php -l for developers/Jenkins.
check-php:
	./vendor/bin/parallel-lint \
	-e module,php,inc,install,profile \
	docroot

# phpcs for developers.
check-style:
	./vendor/bin/phpcs \
	--standard=./vendor/drupal/coder/coder_sniffer/Drupal \
	--extensions=module,php,inc,install \
	--ignore=$(exclude_patterns) \
	docroot/profiles/publisher/modules/custom

# phpcs as checkstyle for jenkins.
check-style-ci:
	./vendor/bin/phpcs \
	--report=checkstyle \
	--report-file=results/checkstyle.xml \
	--standard=./vendor/drupal/coder/coder_sniffer/Drupal \
	--extensions=module,php,inc,install \
	--ignore=$(exclude_patterns) \
	docroot/profiles/publisher/modules/custom

# phpmd for developers.
check-pmd:
	./vendor/bin/phpmd docroot/profiles/publisher/modules/custom text codesize,unusedcode,design \
	--suffixes module,php,inc \
	--exclude $(exclude_patterns)

# phpmd for jenkins.
check-pmd-ci:
	./vendor/bin/phpmd docroot/profiles/publisher/modules/custom xml codesize,unusedcode,design \
	--reportfile results/phpmd.xml \
	--suffixes module,php,inc \
	--exclude $(exclude_patterns)

# phpcopy-paste-detection for developers
check-cpd:
	./vendor/bin/phpcpd --min-lines 3 --min-tokens 25 \
	--names *.module,*.php,*.inc \
	--names-exclude $(exclude_patterns) \
	docroot/profiles/publisher/modules/custom

# phpcopy-paste-detection for jenkins.
check-cpd-ci:
	./vendor/bin/phpcpd --min-lines 3 --min-tokens 25 \
	--log-pmd results/pmd.xml \
	--names *.module,*.php,*.inc \
	--names-exclude $(exclude_patterns) \
	docroot/profiles/publisher/modules/custom

# pdepend for jenkins.
check-pdepend-ci:
	./vendor/bin/pdepend \
	--jdepend-xml=results/pdepend.xml \
	--overview-pyramid=results/overview-pyramid.svg \
	--jdepend-chart=results/jdepend-chart.svg \
	--suffix=module,php,inc \
	--ignore=$(exclude_patterns) \
	docroot/profiles/publisher/modules/custom

# phpunit for developers.
check-phpunit:
	./vendor/bin/phpunit --exclude-group=webtest

# phpunit for web.
check-phpunit-web:
	./vendor/bin/phpunit

# phpunit for jenkins.
check-phpunit-ci:
	./vendor/bin/phpunit --exclude-group=webtest --log-junit=results/junit.xml --coverage-clover=results/clover.xml --coverage-html=results/clover-html

check-all-ci: check-php check-style-ci check-cpd-ci check-pdepend-ci check-pmd-ci check-phpunit-ci
