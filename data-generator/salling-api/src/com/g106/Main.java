package com.g106;

import com.g106.util.ItemData.Item;
import com.g106.util.Logger;

import java.util.ArrayList;
import java.util.List;

import static com.g106.util.Json_Handler.*;

public class Main {
    public static Logger logger = new Logger("G-106");
    private static final List<Item> items = new ArrayList<>();

    public static void main(String[] args) {
        logger.info("Starting to fetch product data");

        SallingApiDriver apiDriver = new SallingApiDriver();
        for (int i = 1; i <= 334; i++) {
            items.addAll(apiDriver.getProductDataFromPage("https://www.bilkatogo.dk/s?query=%2a&page=" + i));
            logger.info("Current page: " + i + "/334");
        }
        apiDriver.quit();

        saveJsonToFile(gson.toJson(apiDriver.failed), "C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data-generator\\salling-api\\failed.json");
        saveListToFile(items, "C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data-generator\\salling-api\\test.json");
    }
}