package com.g106.util;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import org.json.simple.JSONArray;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

import static com.g106.Main.logger;

public class JsonHandler {
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
}