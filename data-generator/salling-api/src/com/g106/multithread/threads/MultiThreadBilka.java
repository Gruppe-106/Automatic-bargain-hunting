package com.g106.multithread.threads;

import com.g106.multithread.MultiThread;
import com.g106.network.apiDrivers.BilkaApiDriver;
import com.g106.network.apiDrivers.CoopApiDriver;
import com.g106.queries.CoopQueries;
import com.g106.util.ItemData;

import java.util.ArrayList;
import java.util.List;

import static com.g106.Main.logger;

public class MultiThreadBilka extends MultiThread {
    final String baseUrl = "https://www.bilkatogo.dk/s?query=%2a&page=";
    @Override
    public List<ItemData.Item> getItemsThread(int start, int end) {
        BilkaApiDriver driver = new BilkaApiDriver();
        List<ItemData.Item> list = new ArrayList<>();
        for (int i = start; i <= end; i++) {
            try {
                list.addAll(driver.getProductDataFromPage(baseUrl + i));
            } catch (Exception e) {
                logger.error(e.getLocalizedMessage());
            }
        }
        driver.quit();
        return list;
    }
}
