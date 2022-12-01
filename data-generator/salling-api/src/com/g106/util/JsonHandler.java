package com.g106.util;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import org.json.simple.JSONArray;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

import static com.g106.Main.logger;

public class JsonHandler {
    public static final String output_file_path = "C:\\Users\\Mikkel\\CLionProjects\\Automatic-bargain-hunting\\data-generator\\salling-api\\data-bilka.json";
    public static JSONArray output_json = new JSONArray();
    public static final Gson gson = new GsonBuilder().setPrettyPrinting().create();

    public static boolean saveJsonToFile(String string, String pathString) {
        Path path = Paths.get(pathString);
        try {
            Files.writeString(path, string, StandardCharsets.UTF_8);
            return true;
        } catch (IOException ex) {
            logger.error("Invalid path: " + pathString);
            return false;
        }
    }

    public static String listToJson(List<?> list) {
        return gson.toJson(list);
    }

    public static boolean saveListToFile(List<?> list, String pathString) {
        return saveJsonToFile(listToJson(list), pathString);
    }

    public static void saveOutputJsonToFile() {
        String string = gson.toJson(output_json);
        saveJsonToFile(string, output_file_path);
    }

    public static JSONArray fileToJson(String file_path) {
        Path path = Paths.get(file_path);
        BufferedReader reader;
        try {
            reader = Files.newBufferedReader(path);
            String line;
            StringBuilder responseContent = new StringBuilder();
            while ((line = reader.readLine()) != null) {
                responseContent.append(line);
            }
            reader.close();

            String jsonString = responseContent.toString();

            JSONParser jsonParser = new JSONParser();
            return (JSONArray) jsonParser.parse(jsonString);
        } catch (IOException | ParseException e) {
            throw new RuntimeException(e);
        }
    }

    public static void appendToOutputJson(JSONArray json) {
        if(json == null) return;
        for (Object item : json) {
            if (!output_json.contains(item)) {
                output_json.add(item);
            }
        }
    }
}