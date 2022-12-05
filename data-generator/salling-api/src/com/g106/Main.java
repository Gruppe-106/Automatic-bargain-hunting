package com.g106;

import com.g106.multithread.threads.MultiThreadBilka;
import com.g106.multithread.threads.MultiThreadCoop;
import com.g106.multithread.threads.MultiThreadFoetex;
import com.g106.multithread.threads.MultiThreadRema;
import com.g106.network.apiDrivers.RemaApiDriver;
import com.g106.queries.CoopQueries;
import com.g106.queries.FoetexQueries;
import com.g106.queries.RemaQueries;
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
        //getCoopData();
        //getFoetexData();
        //getBilkaData();
        getRemaData();
    }

    private static void getCoopData() {
        items = (new MultiThreadCoop()).createAndRunThreads(CoopQueries.queries.size() - 1, 10);
        saveListToFile(items, "C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data-generator\\salling-api\\coop.json");
    }

    private static void getFoetexData() {
        items = (new MultiThreadFoetex()).createAndRunThreads(FoetexQueries.queries.size() - 1, 10);
        saveListToFile(items, "C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data-generator\\salling-api\\foetex.json");
    }

    private static void getBilkaData() {
        items = (new MultiThreadBilka()).createAndRunThreads(334, 10);
        saveListToFile(items, "C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data-generator\\salling-api\\bilka.json");
    }

    private static void getRemaData() {
        items = (new MultiThreadRema()).createAndRunThreads(RemaQueries.queries.size() - 1, 10);
        saveListToFile(items, "C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data-generator\\salling-api\\rema-1000.json");
    }
}