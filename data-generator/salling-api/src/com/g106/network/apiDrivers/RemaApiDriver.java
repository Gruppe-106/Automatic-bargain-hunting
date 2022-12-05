package com.g106.network.apiDrivers;

import com.g106.network.ChromeDriver;
import com.g106.util.ItemData;
import org.openqa.selenium.By;
import org.openqa.selenium.WebElement;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import static com.g106.Main.logger;

public class RemaApiDriver extends ChromeDriver {
    @Override
    public List<ItemData.Item> getProductDataFromPage(String url)  {
        webDriver.get(url);

        logger.info("Connecting to: " + url);
        this.sleep(1000);
        this.executeJavaScript("CookieInformation.declineAllCategories()");
        this.sleep(2000);

        List<ItemData.Item> items = new ArrayList<>();
        List<WebElement> allProductElements = webDriver.findElements(By.className("info"));
        logger.info("Found " + allProductElements.size() + " products");
        for (WebElement product: allProductElements) {
            ItemData.Item item = new ItemData.Item();
            try {
                WebElement name = product.findElement(By.className("title"));
                item.setName(name.getText());

                String[] priceList = product.findElement(By.className("price")).getText().split(" ");
                String price = priceList[0];
                int price_len = price.length() - 2;
                StringBuilder stringBuffer = new StringBuilder(price);
                stringBuffer.insert(price_len, ".");
                price = stringBuffer.toString();
                item.price = Float.parseFloat(price);
                item.setPrice_pr_unit(
                        Float.parseFloat(priceList[1].replace(",", "")),
                        priceList[3].replace(".", ""));

                String[] textList = product.findElement(By.className("extra")).getText().split(" ");
                item.unit_size = Float.parseFloat(textList[0].replace(",", ""));
                item.setUnit_type(textList[1].replace(".", ""));
                try {
                    item.setBrand(product.findElement(By.className("extra")).getText().split("/ ")[1]);
                } catch (Exception e) {
                    logger.warn("No brand for item : " + item.name);
                }

                if (!Objects.equals(item.name, "")) {
                    items.add(item);
                }
            } catch (Exception e) {
                failed.put(item.name, new String[]{url, e.getLocalizedMessage()});
                //logger.error("Error getting product, data collected:\n" + item.toString());
            }
        }

        return items;
    }
}
