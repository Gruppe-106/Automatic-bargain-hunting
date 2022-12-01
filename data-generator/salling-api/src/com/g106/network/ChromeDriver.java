package com.g106.network;

import com.g106.util.ItemData;
import org.openqa.selenium.*;
import org.openqa.selenium.chrome.ChromeOptions;
import org.openqa.selenium.interactions.Actions;

import java.util.HashMap;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import static com.g106.Main.logger;

public class ChromeDriver {
    public final WebDriver webDriver;
    public HashMap<String, String[]> failed = new HashMap<>();

    public ChromeDriver() {
        //Adding chromedriver to the webdriver
        System.setProperty("webdriver.chrome.driver","C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data-generator\\salling-api\\chromedriver.exe");
        //Turning of logger of selenium, to avoid annoying logs
        System.setProperty("webdriver.chrome.silentOutput", "true");
        Logger.getLogger("org.openqa.selenium").setLevel(Level.OFF);

        ChromeOptions chromeOptions = new ChromeOptions();
        //Make sure page is loaded before pulling data from it
        chromeOptions.setPageLoadStrategy(PageLoadStrategy.NORMAL);
        //Make it headless
        chromeOptions.setHeadless(true);
        webDriver = new org.openqa.selenium.chrome.ChromeDriver(chromeOptions);
    }

    public boolean executeJavaScript(String script) {
        if (webDriver instanceof JavascriptExecutor) {
            ((JavascriptExecutor)webDriver).executeScript(script);
            return true;
        } else {
            logger.error("Driver does not support JavaScript");
            return false;
        }
    }

    public void useButton(int timeWaitIncrement, String className) {
        int increment = 0;
        try {
            while(true) {
                WebElement button = webDriver.findElement(By.className(className));
                button.click();
                Thread.sleep(500 + increment);
                increment += timeWaitIncrement;
            }
        } catch (Exception e) {
            logger.info("No more buttons");
        }
    }

    public void scrollToElement(WebElement element) {
        Actions actions = new Actions(this.webDriver);
        actions.moveToElement(element);
        actions.perform();
    }

    public void scrollToBottomOfPage() {
        this.executeJavaScript("window.scrollBy(0,document.body.scrollHeight)");
    }

    public void quit() {
        webDriver.quit();
    }

    public void sleep(int milliseconds) {
        try {
            Thread.sleep(milliseconds);
        } catch (InterruptedException e) {
            logger.error("Somehow thread.sleep fucked up, idk how....");
        }
    }

    public List<ItemData.Item> getProductDataFromPage(String url) { return null; }
}
