package com.g106.network.apiDrivers;

import com.g106.network.ChromeDriver;
import com.g106.util.ItemData.PricePrUnit;
import com.g106.util.ItemData.Item;
import org.openqa.selenium.By;
import org.openqa.selenium.WebElement;

import java.util.ArrayList;
import java.util.List;

import static com.g106.Main.logger;

public class SallingApiDriver extends ChromeDriver {
    @Override
    public List<Item> getProductDataFromPage(String url)  {
        webDriver.get(url);
        logger.info("Connecting to: " + url);
        this.executeJavaScript("CookieInformation.declineAllCategories();");
        try {
            Thread.sleep(500);
        } catch (InterruptedException e) {
            logger.error("Somehow thread.sleep fucked up, idk how....");
        }

        List<Item> items = new ArrayList<>();
        List<WebElement> allProductElements = webDriver.findElements(By.className("product-card-container"));
        logger.info("Found " + allProductElements.size() + " products");
        for (WebElement productElement : allProductElements) {
            Item item = new Item();
            try {
                item.name = productElement.findElement(By.className("name")).getText().toLowerCase();

                WebElement priceElement = productElement.findElement(By.className("product-price"));
                List<WebElement> priceElementSpans = priceElement.findElements(By.tagName("span"));
                String price_int = priceElementSpans.get(0).getText();
                String price_dec = priceElementSpans.get(1).getText().replace(".-", "");

                String price;
                if (price_dec.equals("")) price = price_int;
                else price = price_int + "." + price_dec;
                item.price = Float.parseFloat(price);

                String under_text = productElement.findElement(By.className("description")).getText();
                String[] under_list = under_text.split(" ");

                int length = under_list.length;
                item.unit_size = Float.parseFloat(under_list[length - 3]);
                item.unit_type = under_list[length - 2].toLowerCase();

                String[] pricePrUnit = under_list[length - 1].split("/");
                PricePrUnit pPU = new PricePrUnit();
                pPU.price = Float.parseFloat(pricePrUnit[0].replace(".", "").replace(",", "."));
                pPU.unit = pricePrUnit[1].replace(".", "").toLowerCase();
                item.price_pr_unit = pPU;
                items.add(item);
            } catch (Exception e) {
                failed.put(item.name, new String[]{url, e.getLocalizedMessage()});
                //logger.error("Error getting product, data collected:\n" + item.toString());
            }
        }
        return items;
    }
}