package com.g106.multithread;

import com.g106.util.ItemData.Item;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

public class MultiThread {
    public List<Item> getItemsThread(int start, int end) {
        return null;
    }

    public class CallableThreadGetItems implements Callable<List<Item>> {
        int start;
        int end;

        public CallableThreadGetItems(int start, int end) {
            this.start = start;
            this.end = end;
        }

        @Override
        public List<Item> call() throws Exception {
            return getItemsThread(this.start, this.end);
        }
    }

    public List<Item> createAndRunThreads(List<String> queries, int totalThreads) {
        int amountQueries = queries.size() - 1;
        List<Item> items = new ArrayList<>();
        List<Future<List<Item>>> threads = new ArrayList<>();
        ExecutorService executorService = Executors.newCachedThreadPool();
        try {
            int perThread = amountQueries / totalThreads;
            int lastEnd = 0;
            for (int i = 0; i < totalThreads; i++) {
                threads.add(executorService.submit(new CallableThreadGetItems(lastEnd, (lastEnd + perThread))));
                lastEnd = lastEnd + perThread + 1;
            }
            executorService.shutdown();
            boolean finished = executorService.awaitTermination(30, TimeUnit.MINUTES);
            if (finished) {
                for (Future<List<Item>> listFuture: threads) {
                    List<Item> list = listFuture.get();
                    for (Item item : list) {
                        if (!items.contains(item)) items.add(item);
                    }
                }
            }
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
        return items;
    }
}
