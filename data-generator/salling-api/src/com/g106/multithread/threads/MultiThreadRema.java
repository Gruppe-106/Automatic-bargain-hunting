package com.g106.multithread.threads;

import com.g106.network.apiDrivers.RemaApiDriver;
import com.g106.queries.RemaQueries;
import com.g106.util.ItemData.Item;
import com.g106.multithread.MultiThread;

import java.util.ArrayList;
import java.util.List;

import static com.g106.Main.logger;

public class MultiThreadRema extends MultiThread {
    @Override
    public List<Item> getItemsThread(int start, int end) {
        List<Item> list = new ArrayList<>();
        RemaApiDriver driver = new RemaApiDriver();
        for (int i = start; i <= end; i++) {
            try {
                String url = RemaQueries.queries.get(i);
                list.addAll(driver.getProductDataFromPage(url));
            } catch (Exception e) {
                logger.error(e.getLocalizedMessage());
            }
        }
        driver.quit();
        return list;
    }
}
