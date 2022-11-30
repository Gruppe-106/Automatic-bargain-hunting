package com.g106;

import com.g106.util.ItemData;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

import static com.g106.Main.logger;

public class MultiThread {
    private static class CallableThreadGetItems implements Callable<List<ItemData.Item>> {
        private int start;
        private int end;
        private int index;

        public CallableThreadGetItems(int start, int end, int index) {
            this.start = start;
            this.end = end;
            this.index = index;
        }

        @Override
        public List<ItemData.Item> call() {
            List<ItemData.Item> list = new ArrayList<>();
            SallingApiDriver driver = new SallingApiDriver();
            int failed = 0;
            int succeeded = 0;
            for (int i = this.start; i < this.end; i++) {
                ItemData.Item item = null;//driver.getProductData(String.valueOf(i));
                if (item != null) {
                    list.add(item);
                    succeeded++;
                    logger.info("Index: " + index + "f: " + failed + ", s: " + succeeded + " p: " + i + "/" + this.end);
                }
                else failed++;
            }
            driver.quit();
            return list;
        }
    }

    public static void createAndRunThreads(int start, int end, int totalThreads) {
        List<Future<List<ItemData.Item>>> threads = new ArrayList<>();
        ExecutorService executorService = Executors.newCachedThreadPool();
        try {
            int perThread = (end - start) / totalThreads;
            int lastEnd = start;
            for (int i = 0; i < totalThreads; i++) {
                threads.add(executorService.submit(new CallableThreadGetItems(lastEnd, (lastEnd + perThread - 1), i)));
                lastEnd = lastEnd + perThread;
            }
            executorService.shutdown();
            boolean finished = executorService.awaitTermination(5, TimeUnit.HOURS);
            if (finished) {
                for (Future<List<ItemData.Item>> listFuture: threads) {
                    List<ItemData.Item> list = listFuture.get();
                    //items.addAll(list);
                }
            }
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
    }
}
