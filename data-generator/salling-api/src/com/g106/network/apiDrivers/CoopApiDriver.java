package com.g106.network.apiDrivers;

import com.g106.network.ChromeDriver;
import com.g106.util.ItemData.PricePrUnit;
import com.g106.util.ItemData.Item;
import org.openqa.selenium.By;
import org.openqa.selenium.WebElement;

import java.util.ArrayList;
import java.util.List;

import static com.g106.Main.logger;

public class CoopApiDriver extends ChromeDriver {
    @Override
    public List<Item> getProductDataFromPage(String url)  {
        List<Item> items = new ArrayList<>();

        webDriver.get(url);
        this.executeJavaScript("CookieInformation.declineAllCategories()");
        this.sleep(250);
        scrollToBottomOfPage();
        this.sleep(250);

        List<WebElement> allProductElements = webDriver.findElements(By.xpath("//article[@class='o-tile-grid__item o-tile-grid__item--product']"));
        //logger.info("Connecting to: " + url + ", Found " + allProductElements.size() + " products");
        if (allProductElements.size() == 0) {
            logger.warn("Retrying to find products in 10 secs on page: " + url);
            sleep(10000);
            allProductElements = webDriver.findElements(By.xpath("//article[@class='o-tile-grid__item o-tile-grid__item--product']"));
            if (allProductElements.size() == 0) {
                logger.error("Failed to find products on page: " + url);
            }
        }
        for (WebElement productElement : allProductElements) {
            Item item = new Item();
            try {
                scrollToElement(productElement);
                this.sleep(10);

                item.name = productElement.findElement(By.className("c-product-tile__title")).getText();
                List<WebElement> priceElements = productElement.findElement(By.className("price-wrap")).findElements(By.tagName("span"));
                item.price = Float.parseFloat(priceElements.get(0).getText() + "." + priceElements.get(1).getText());

                String[] pricePrUnitStringList = productElement.findElement(By.className("text-11")).getText().replace("kr. pr. ", "").split(" ");
                PricePrUnit pricePrUnit = new PricePrUnit();
                pricePrUnit.price = Float.parseFloat(pricePrUnitStringList[0].replace(",-", "").replace(".", "").replace(",", "."));
                pricePrUnit.unit =  pricePrUnitStringList[1];
                item.price_pr_unit = pricePrUnit;

                String[] unitStringList = productElement.findElement(By.className("product-text-truncate")).getText().split(", ");
                String lastContaining = "";
                int count = 0;
                for (String string: unitStringList) {
                    if (string.contains(item.price_pr_unit.unit)) {
                        lastContaining = string;
                    } else if (count == 0) {
                        item.brand = string;
                    }
                    count++;
                }
                String[] lastContainingList = lastContaining.split(" ");
                item.unit_size = Float.parseFloat(lastContainingList[0].replace(",-", "").replace(".", "").replace(",", "."));
                item.unit_type = lastContainingList[1];

                items.add(item);
            } catch (Exception e) {
                failed.put(item.name, new String[]{url, e.getLocalizedMessage()});
            }
        }
        return items;
    }
}
