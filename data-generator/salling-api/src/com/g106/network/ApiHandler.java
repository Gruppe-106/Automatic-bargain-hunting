package com.g106.network;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.util.Objects;

import static com.g106.util.JsonHandler.*;
import static com.g106.Main.logger;

public class ApiHandler {
    public static final String rema_json = "C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data\\rema-1000.json";
    public static final String apiUrl = "https://api.sallinggroup.com";
    public static final String suggestion_subject = "/v1-beta/product-suggestions/relevant-products?query=";
    public static final String similar_subject = "/v1-beta/product-suggestions/similar-products?productId=";
    public static final String secret = "9494686b-bce8-4af6-8e57-3f0ff90d37e8";
    public static final int retryTimeout = 2000;
    public static final int timeToRetry = 2;

    public void getDataFromApi(int max_items) {
        int failed = 0;
        int count = 1;
        JSONArray json = fileToJson(rema_json);
        int list_size = json.size();
        try {
            for (Object item : json) {
                JSONObject json_item = (JSONObject) item;
                JSONObject json_items;
                json_items = create_request_suggestion(apiUrl + suggestion_subject + URLEncoder.encode((String) json_item.get("name"), StandardCharsets.UTF_8));
                if (json_items != null) {
                    JSONArray suggestions = (JSONArray) json_items.get("suggestions");
                    appendToOutputJson(suggestions);
                } else {
                    failed++;
                }
                logger.info("Current count: " + count + "/" + list_size + " " + Math.floor(((float) (count / list_size)) * 100f) + "%");
                if ((count - 1) > max_items) break;
                count++;
            }
            logger.warn("Total failed: " + failed);
        } catch (ParseException | IOException e) {
            logger.error(e.toString());
        }
    }
    public JSONArray create_request_similar(String s) throws ParseException, IOException {
        String json = create_request(s);
        if(json == null) return null;
        JSONParser parser = new JSONParser();
        return (JSONArray) parser.parse(json);
    }

    public JSONObject create_request_suggestion(String s) throws ParseException, IOException {
        String json = create_request(s);
        if(json == null) return null;
        JSONParser parser = new JSONParser();
        return (JSONObject) parser.parse(json);
    }

    public String create_request(String queryUrl) throws IOException {
        String retVal = null;

        HttpURLConnection con = createConnection(queryUrl);
        if (con != null) {
            if (Objects.equals(con.getContentType(), "application/json; charset=utf-8")) {
                String line;
                StringBuilder responseContent = new StringBuilder();
                BufferedReader reader = new BufferedReader(new InputStreamReader(con.getInputStream()));
                while ((line = reader.readLine()) != null) {
                    responseContent.append(line);
                }
                reader.close();
                retVal = responseContent.toString();
            }
            con.disconnect();
        }
        return retVal;
    }

    private HttpURLConnection createConnection(String queryUrl) {
        for (int i = 1; i <= timeToRetry; i++) {
            try {
                URL url = new URL(queryUrl);
                HttpURLConnection con = (HttpURLConnection) url.openConnection();
                con.setRequestMethod("GET");

                con.setRequestProperty("accept", "application/json");
                con.setRequestProperty("Authorization", "Bearer " + secret);

                con.setConnectTimeout(5000);
                con.setReadTimeout(5000);

                int status = con.getResponseCode();
                if (status == 200) {
                    return con;
                }
                con.disconnect();
                if (i != timeToRetry) {
                    logger.warn("Got status : <" + status + ">" + "retrying in: " + retryTimeout + "ms, try: " + i + "/" + timeToRetry);
                    Thread.sleep(retryTimeout);
                } else {
                    logger.error("Failed to create connection to: " + queryUrl + " with status: " + status);
                }
            } catch (IOException | InterruptedException e) {
                logger.error(e.toString());
            }
        }
        return null;
    }
}