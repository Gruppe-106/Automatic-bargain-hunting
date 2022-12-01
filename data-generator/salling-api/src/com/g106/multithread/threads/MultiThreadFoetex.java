package com.g106.multithread.threads;

import com.g106.network.apiDrivers.FoetexApiDriver;
import com.g106.queries.FoetexQueries;
import com.g106.util.ItemData.Item;
import com.g106.multithread.MultiThread;

import java.util.ArrayList;
import java.util.List;

public class MultiThreadFoetex extends MultiThread {
    @Override
    public List<Item> getItemsThread(int start, int end) {
        List<Item> list = new ArrayList<>();
        FoetexApiDriver driver = new FoetexApiDriver();
        for (int i = start; i <= end; i++) {
            String url = FoetexQueries.queries.get(i);
            list.addAll(driver.getProductDataFromPage(url));
        }
        driver.quit();
        return list;
    }
}
