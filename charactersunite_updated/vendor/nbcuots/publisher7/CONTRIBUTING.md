Contributing
------------

Publisher7 is an "open source" (Within the context of NBCUniversal), "community-driven" (Within the context of NBCUniversal & External contractors) project.

If you'd like to contribute, please read the following:

* Submitting a Pull Request:
  - All pull-request should be from a feature-branch made off the latest master
  - All pull-request should target the nbcuots/Publisher7:master branch

* What happens when a Pull Request is open:
  - When a Pull Request is open we run it through various test such as:
    - php syntax checking
    - Drupal coding standards
    - PHP Copy & Paste Detection
  
  - Based on the results set you will either see a Passing or Failure error on github. In either case you should be able to see
  Jenkins (our CI system) console output by clicking on the "details" link. If you can open a PR you can see the output (We used github
  permissions for authentication)

* What happens after the CI System says my PR is good:
 - If all our test return succesfull another job will spin up a brand new AWS Environment with your changes.
   The url will be something like "p7-PR_NUMBER.ci.publisher7.com"
 
 - Once that environment is up and running our QA Team will test the code and make sure it does what it's supposed to.
   (And didn't break anything)
   

... More to come.
