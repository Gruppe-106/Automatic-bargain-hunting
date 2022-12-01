package com.g106.multithread.threads;

import com.g106.multithread.MultiThread;
import com.g106.network.apiDrivers.CoopApiDriver;
import com.g106.queries.CoopQueries;
import com.g106.util.ItemData;

import java.util.ArrayList;
import java.util.List;

public class MultiThreadCoop extends MultiThread {
    @Override
    public List<ItemData.Item> getItemsThread(int start, int end) {
        List<ItemData.Item> list = new ArrayList<>();
        CoopApiDriver driver = new CoopApiDriver();
        for (int i = start; i <= end; i++) {
            String url = CoopQueries.queries.get(i);
            list.addAll(driver.getProductDataFromPage(url));
        }
        driver.quit();
        return list;
    }
}
