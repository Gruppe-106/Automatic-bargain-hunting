package com.g106.network.apiDrivers;

import com.g106.network.ChromeDriver;
import com.g106.util.ItemData.PricePrUnit;
import com.g106.util.ItemData.Item;
import org.openqa.selenium.By;
import org.openqa.selenium.WebElement;

import java.util.ArrayList;
import java.util.List;

import static com.g106.Main.logger;

public class FoetexApiDriver extends ChromeDriver {
    @Override
    public List<Item> getProductDataFromPage(String url)  {
        webDriver.get(url);

        logger.info("Connecting to: " + url);
        this.executeJavaScript("CookieInformation.declineAllCategories()");
        try {
            Thread.sleep(500);
        } catch (InterruptedException e) {
            logger.error("Somehow thread.sleep fucked up, idk how....");
        }
        useButton(0, "active:text-primary");

        List<Item> items = new ArrayList<>();
        List<WebElement> allProductElements = webDriver.findElements(By.xpath("//a[@data-testid='e2eProductCards']"));
        logger.info("Found " + allProductElements.size() + " products");
        for (WebElement productElement : allProductElements) {
            Item item = new Item();
            try {
                item.setName(productElement.findElement(By.className("mb-1")).getText().toLowerCase());

                String priceElement = productElement.findElement(By.className("JKUot")).getText();
                item.price = Float.parseFloat(new StringBuffer(priceElement).insert(priceElement.length()-2, ".").toString());

                String weightElement = productElement.findElement(By.className("mb-2")).getText();
                String[] under_list = weightElement.split("/");

                if (under_list.length > 1) {
                    item.setBrand(under_list[1]);
                }

                under_list = weightElement.split(" ");

                if (under_list[1].equalsIgnoreCase("x")) {
                    item.unit_size = Float.parseFloat(under_list[0].replace(".", "").replace(",", ".")) * Float.parseFloat(under_list[2].replace(".", "").replace(",", "."));
                    item.setUnit_type(under_list[3].toLowerCase());
                } else {
                    item.unit_size = Float.parseFloat(under_list[0].replace(".", "").replace(",", "."));
                    item.setUnit_type(under_list[1].toLowerCase());
                }

                List<WebElement> pricePrElement = productElement.findElements(By.className("pr-1"));
                String[] pricePrList = pricePrElement.get(0).getText().split(" ");
                item.setPrice_pr_unit(
                        Float.parseFloat(pricePrList[2].replace(".", "").replace(",", ".")),
                        pricePrList[1]
                );
                items.add(item);
            } catch (Exception e) {
                failed.put(item.name, new String[]{url, e.getLocalizedMessage()});
                //logger.error("Error getting product, data collected:\n" + item.toString());
            }
        }
        return items;
    }
}
