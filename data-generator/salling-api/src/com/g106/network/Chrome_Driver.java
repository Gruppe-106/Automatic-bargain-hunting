package com.g106.network;

import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.PageLoadStrategy;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.chrome.ChromeOptions;

import java.util.logging.Level;
import java.util.logging.Logger;

import static com.g106.Main.logger;

public class Chrome_Driver {
    public final WebDriver webDriver;

    public Chrome_Driver() {
        //Adding chromedriver to the webdriver
        System.setProperty("webdriver.chrome.driver","C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data-generator\\salling-api\\chromedriver.exe");
        //Turning of logger of selenium, to avoid annoying logs
        System.setProperty("webdriver.chrome.silentOutput", "true");
        Logger.getLogger("org.openqa.selenium").setLevel(Level.OFF);

        ChromeOptions chromeOptions = new ChromeOptions();
        //Make sure page is loaded before pulling data from it
        chromeOptions.setPageLoadStrategy(PageLoadStrategy.NORMAL);
        //Make it headless
        chromeOptions.setHeadless(false);
        webDriver = new ChromeDriver(chromeOptions);
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

    public void quit() {
        webDriver.quit();
    }
}
