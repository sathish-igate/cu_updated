<?php

class PublisherUserLoginTest extends PHPUnit_Framework_TestCase {

  /**
   * @var \RemoteWebDriver
   */
  protected $webDriver;


  public function setUp() {
    $capabilities = array(\WebDriverCapabilityType::BROWSER_NAME => 'firefox');
    $this->webDriver = RemoteWebDriver::create('http://localhost:4444/wd/hub', $capabilities);
  }

  /**
   * @group webtest
   */
  public function testLoginIn() {
    $url = getenv('SITE_URL') . '/user';

    $this->webDriver->get($url);

    // checking that page title contains word 'User account'
    $this->assertContains('User account', $this->webDriver->getTitle());

    // Now lets login and confirm it works.
    // find search field by its id
    $username = $this->webDriver->findElement(WebDriverBy::id('edit-name'));
    $username->click();
    $this->webDriver->getKeyboard()->sendKeys('admin@publisher.nbcuni.com');

    $username = $this->webDriver->findElement(WebDriverBy::id('edit-pass'));
    $username->click();
    $this->webDriver->getKeyboard()->sendKeys('pa55word');

    // pressing "Enter"
    $this->webDriver->getKeyboard()->pressKey(WebDriverKeys::ENTER);

    // checking that page title contains word 'admin' indicating a successful login.
    $this->assertContains('admin', $this->webDriver->getTitle());
  }

  public function tearDown() {
    $this->webDriver->close();
  }
}
