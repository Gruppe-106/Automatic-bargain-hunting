package com.g106.util;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Logger {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String WARN_COLOUR = "\u001B[33m";
    public static final String ERROR_COLOUR = "\u001B[31m";
    public static final String INFO_COLOUR = "\u001B[38;5;255m";
    private String tag;

    public Logger(String tag) {
        this.tag = tag;
    }

    public void info(String string) {
        System.out.println(INFO_COLOUR + getInfo("INFO") + ANSI_RESET + string);
    }

    public void error(String string) {
        System.out.println(ERROR_COLOUR + getInfo("ERROR") + ANSI_RESET + string);
    }

    public void warn(String string) {
        System.out.println(WARN_COLOUR + getInfo("WARN")+ ANSI_RESET + string );
    }

    private String getInfo(String level) {
        return getTime() + "[" + tag + "/" + level + "] ";
    }

    private String getTime() {
        DateTimeFormatter dtf_date = DateTimeFormatter.ofPattern("MM/dd");
        DateTimeFormatter dtf_time = DateTimeFormatter.ofPattern("HH:mm:ss");
        LocalDateTime now = LocalDateTime.now();
        return "[" + now.format(dtf_date) + "][" + now.format(dtf_time) + "]";
    }
}
