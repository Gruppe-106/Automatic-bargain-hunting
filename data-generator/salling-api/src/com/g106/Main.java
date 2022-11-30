package com.g106;

import com.g106.multithread.threads.MultiThreadCoop;
import com.g106.multithread.threads.MultiThreadFoetex;
import com.g106.network.apiDrivers.CoopApiDriver;
import com.g106.network.apiDrivers.SallingApiDriver;
import com.g106.queries.CoopQueries;
import com.g106.queries.FoetexQueries;
import com.g106.util.ItemData.Item;
import com.g106.util.Logger;

import java.util.ArrayList;
import java.util.List;

import static com.g106.util.JsonHandler.*;

public class Main {
    public static Logger logger = new Logger("G-106");
    private static List<Item> items = new ArrayList<>();

    public static void main(String[] args) {
        logger.info("Starting to fetch product data");
        getCoopData();
    }

    private static void getCoopData() {
        items = (new MultiThreadCoop()).createAndRunThreads(CoopQueries.queries, 10);
        saveListToFile(items, "C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data-generator\\salling-api\\coop.json");
    }

    private static void getFoetexData() {
        items = (new MultiThreadFoetex()).createAndRunThreads(FoetexQueries.queries, 10);
        saveListToFile(items, "C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data-generator\\salling-api\\foetex.json");
    }

    private static void getBilkaData() {
        SallingApiDriver apiDriver = new SallingApiDriver();
        for (int i = 1; i <= 334; i++) {
            items.addAll(apiDriver.getProductDataFromPage("https://www.bilkatogo.dk/s?query=%2a&page=" + i));
            logger.info("Current page: " + i + "/334");
        }
        apiDriver.quit();

        saveJsonToFile(gson.toJson(apiDriver.failed), "C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data-generator\\salling-api\\bilka-failed.json");
        saveListToFile(items, "C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data-generator\\salling-api\\bilka.json");
    }
}