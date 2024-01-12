package by.bsuir.springbootproject.utils;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ErrorPopulatorUtils {

    public static Map<String, String> populateErrors(String message) {
        Map<String, String> errors = new HashMap<>();
        Arrays.stream(message.split(", ")).toList().forEach(errorMessage -> {
            List<String> pair = Arrays.stream(errorMessage.split(": ")).toList();
            errors.put(pair.get(0), pair.get(1));
        });
        return errors;
    }
}