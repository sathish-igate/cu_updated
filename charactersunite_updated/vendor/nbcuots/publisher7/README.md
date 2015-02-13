This is Publisher 7. Prepare to be awed.

# Installation

## Core Development

To install publisher locally please follow these steps:

1. Clone this repository in your local sites folder.
1. Follow [pubstack installation instructions](https://github.com/NBCUOTS/pubstack/blob/master/README.md). In step 7 of the install list, use this as the nbcupublisher7 definition for your pubstack `config.yml` file:

    ```yaml
    - subscription: nbcupublisher7
      shortname: nbcupublisher7
      vhost:
        servername: local.publisher7.com
        documentroot: Publisher7/docroot
    ```
1. For the initial installation, run ```drush psi```.

### Publisher Testing/Standards

Publisher composer.json file has all the dependencies that get run when a new PR is open. If contributing please make sure all these test still pass. See below to get started:

```bash
# Install all dependecies
composer install

make check-php # Run php parallel-lint against all our code for syntax checking
make check-style # Run phpcs coding standard against all our code for standard checking
make check-cpd # Run phpcpd against all our code for copy & paste detection
make check-phpunit # Runs phpunit against all our unitTest
```

##testing

```sh
# Run phpunit without any Selenium WebTestCase.
./vendor/bin/phpunit --exclude-group=webtest

# optional if you want to run all Test including WebTestCase.
./vendor/bin/phpunit

# optional if you want to change the default site url
# default url is http://local.publisher7.com/
SITE_URL="http://qa5.publisher7.com" ./vendor/bin/phpunit

# If you want to see inline converage report
./vendor/bin/phpunit --coverage-text
```

Note: To run the selemium Test you must have a running selenium web server.
 Mac:
 1. ```brew install selenium-server-standalone```
 1. ```selenium-server -p 4444```
 1. ```./vendor/bin/phpunit```

 Linux/Mac/Windows:
 1. Download [selenium-server-standalone-2.44.0.jar](http://selenium-release.storage.googleapis.com/2.44/selenium-server-standalone-2.44.0.jar)
 1. ```java -jar selenium-server-standalone-2.44.0.jar```
 1. ```./vendor/bin/phpunit```


## Implementation Development
1. For a new Implementation you just need to create a new composer.json at the top of your new git repo

composer.json:
```json
{
    "name": "nbcuots/GITHUB_REPO_NAME",
    "description": "MySuperCool.com Publisher7 project",
    "repositories": [
        {
            "type": "composer",
            "url": "http://nbcuots.github.io/satis/"
        }
    ],
    "require": {
        "composer/installers": "@dev",
        "drush/drush": "6.4.0",
        "squizlabs/php_codesniffer": "dev-master",
        "drupal/coder": "7.2.2",
        "phpunit/phpunit": "4.1.6",
        "phpunit/php-code-coverage": "2.0.*",
        "sebastian/phpcpd": "*",
        "phpmd/phpmd": "dev-master",
        "jakub-onderka/php-parallel-lint": "0.*"
    },
    "require-dev": {
        "nbcuots/publisher7": "7.47.0"
    },
    "scripts": {
        "post-install-cmd": "vendor/nbcuots/publisher7/scripts/publisher-install",
        "post-update-cmd": "vendor/nbcuots/publisher7/scripts/publisher-install"
    },
    "extra": {
        "webroot-package": "nbcuots/publisher7",
        "webroot-dir": "docroot"
    }
}
```
**Note**: The require-dev key in the composer.json file contains Publisher7, The reason for this is we oftend time want to run ```composer install``` but without updating your Publisher7 version and the best way we've found around this is by running ```composer install --no-dev --no-scripts``` Which will skip the dev dependecies & won't run the post-install-cmd & post-update-cmd command. This allows our CI servers to still bring in all the other dev dependecies without overwriting any patches you might have applied to publisher. Technically all of these requirements belong in "require-dev" since your website will work perfectly fine without any of them, after the initial set up.



1. run ```composer install```
 This will create a docroot folder for you and everything you need.
 - Make sure to add a .gitignore to ignore the vendor directory. (*You should not add this to git*)
 - You will have no sites/default or sites/SITENAME folder you will only get a sites/all. Feel free to make your sites folder "default" if you don't want to deal with multi-sites (That's what we do now on publisher core). We will never touch any folder in sites/* except for sites/all on your repository.

1. Updating publisher verions:
 - Change the ```nbcuots/publisher7``` version on composer.json and run ```composer update```
 - Publisher will get updated, your sites folder will be ok.
