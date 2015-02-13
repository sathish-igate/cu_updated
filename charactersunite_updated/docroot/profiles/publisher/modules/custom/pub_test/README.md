# Publisher Testing

## Writing a Publisher Test
Publisher ships with 1 base class: PublisherWebTestCase (the default Publisher
profile).

*Note: When writing your test it is strongly recommended that you extend from
PublisherWebTestCase.  The reason for this is that we want to be sure the tests
are executed within a publisher installation profile.*

## Running a Test:

Since we have a custom base class to simplify the testing, you must first enable
pub_test.
```sh
 drush en simpletest pub_test --yes
```

A couple of notes:
1) You must enable both simpletest and pub_test if you plan on running any
test from any module, simpletest will fail if you do not enable pub_test.
You do not need to enable simpletest inside your testing environment.
2) The Publisher Testing module is deliberately hidden from the web UI.  Given
that, you'll need to enable pub_test with drush.

```sh
# You can run a single test such as:
drush test-run PublisherProfileTestCase

# Or you can run all the tests in the Publisher group:
drush test-run Publisher

# If you just want to test the new method you just added you can also do:
drush test-run PublisherProfileTestCase --methods="testPublisherSmokeUserLogin"
```

## Tips
 - If running via the UI, odds are that PHP will timeout. Either run it via
 drush or increase your PHP ```max_execution_time``` settings.
 - If you add a new test and you do not see it available make sure you also
 added it to the ```files[]``` array on the pub_test.info file.
 - When running a test you will be messing with the Drupal Registry System a lot.
 It's a good idea to install [Registry Rebuild](https://drupal.org/project/registry_rebuild)

##External resources
