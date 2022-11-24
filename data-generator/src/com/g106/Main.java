package com.g106;

import com.google.gson.GsonBuilder;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import com.google.gson.Gson;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Objects;

import com.g106.queries;

public class Main {
    public static final String apiUrl = "https://api.sallinggroup.com";
    public static final String suggestion_subject = "/v1-beta/product-suggestions/relevant-products?query=";
    public static final String similar_subject = "/v1-beta/product-suggestions/frequently-bought-together?productId=";
    public static final String secret = "9494686b-bce8-4af6-8e57-3f0ff90d37e8";
    public static final Gson gson = new GsonBuilder().setPrettyPrinting().create();
    public static JSONObject output_json = null;

    public static void main(String[] args) throws ParseException, IOException {
        for (String query: queries.queries) {
            JSONObject json = null;
            json = create_request_suggestion(apiUrl + suggestion_subject + URLEncoder.encode(query, StandardCharsets.UTF_8));
            if (json != null) {
                if(output_json == null) {
                    output_json = json;
                } else {
                    append_to_output_json(json);
                }
                JSONArray suggestions = (JSONArray) json.get("suggestions");
                if (!suggestions.isEmpty()) {
                    String id = (String) ((JSONObject) suggestions.get(0)).get("prod_id");
                    append_to_output_json(create_request_similar(apiUrl + similar_subject + URLEncoder.encode(id, StandardCharsets.UTF_8)));
                }
            }
        }
        save_string_to_file(gson.toJson(output_json));
    }

    private static JSONArray create_request_similar(String s) throws ParseException, IOException {
        String json = create_request(s);
        if(json == null) return null;
        JSONParser parser = new JSONParser();
        return (JSONArray) parser.parse(json);
    }

    private static JSONObject create_request_suggestion(String s) throws ParseException, IOException {
        String json = create_request(s);
        if(json == null) return null;
        JSONParser parser = new JSONParser();
        return (JSONObject) parser.parse(json);
    }

    public static String create_request(String queryUrl) throws IOException {
        String retVal = null;
        JSONObject json = null;

        URL url = new URL(queryUrl);
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");

        con.setRequestProperty("accept", "application/json");
        con.setRequestProperty("Authorization", "Bearer " + secret);

        con.setConnectTimeout(5000);
        con.setReadTimeout(5000);

        int status = con.getResponseCode();
        if (status == 200) {
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
        } else {
            log("Status : <" + status + ">");
        }
        con.disconnect();
        return retVal;
    }

    public static void save_string_to_file(String string) {
        Path path = Paths.get("C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data\\data.json");
        try {
            Files.writeString(path, string, StandardCharsets.UTF_8);
        } catch (IOException ex) {
            System.out.print("Invalid Path");
        }
    }

    public static void append_to_output_json(JSONObject json) {
        if(json == null) return;
        JSONArray array = (JSONArray) json.get("suggestions");
        ((JSONArray) output_json.get("suggestions")).addAll(array);
    }

    public static void append_to_output_json(JSONArray json) {
        if(json == null) return;
        ((JSONArray) output_json.get("suggestions")).addAll(json);
    }

    public static void log(String message) {
        System.out.print(message);
    }
}
