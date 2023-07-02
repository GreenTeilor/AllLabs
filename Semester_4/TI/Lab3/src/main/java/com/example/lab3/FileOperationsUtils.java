package com.example.lab3;

import javafx.scene.Scene;
import javafx.stage.FileChooser;

import java.io.File;
import java.nio.ByteBuffer;
import java.util.function.Function;

public class FileOperationsUtils {
    private FileOperationsUtils() {

    }


    public static String toStringDecimal(byte[] bytes, int numberSize) {
        if (bytes != null) {
            ByteBuffer wrapped = ByteBuffer.wrap(bytes); // big-endian by default
            Function<ByteBuffer, ? extends Number> toNumber;
            switch(numberSize) {
                case 2 -> toNumber = ByteBuffer::getShort;
                case 4 -> toNumber = ByteBuffer::getInt;
                default -> toNumber = ByteBuffer::get;
            }
            StringBuilder decimalRepresentation = new StringBuilder(1024 * 100);
            if (bytes.length <= 1024 * 100) {
                for (int i = 0; i < bytes.length; i += numberSize) {
                    decimalRepresentation.append(AlgorithmsUtils.toUnsignedInteger(toNumber.apply(wrapped))).append(" ");
                }
            } else {
                decimalRepresentation.append("Начало файла:\r\n");
                for (int i = 0; i < 128;i += numberSize) {
                    decimalRepresentation.append(AlgorithmsUtils.toUnsignedInteger(toNumber.apply(wrapped))).append(" ");
                }
                decimalRepresentation.append("\r\nКонец файла:\r\n");
                for (int i = bytes.length - 128; i < bytes.length; i += numberSize) {
                    decimalRepresentation.append(AlgorithmsUtils.toUnsignedInteger(toNumber.apply(wrapped))).append(" ");
                }
            }
            return decimalRepresentation.toString();
        }
        return "";
    }

    public static String validateKey(String binaryKey) {
        binaryKey = binaryKey.replaceAll("[^10]", "");
        return binaryKey;
    }

    public static int fetchKey(String binaryKey) {
        return (int) Long.parseLong(binaryKey, 2);
    }

    public static boolean isValidKey(String binaryKey) {
        if (binaryKey.length() != 32) {
            return false;
        }
        for (char bit : binaryKey.toCharArray()) {
            if (bit != '0' && bit != '1') {
                return false;
            }
        }
        return true;
    }

    public static File openFile(Scene scene) {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Open file");
        FileChooser.ExtensionFilter extFilter = new FileChooser.ExtensionFilter("Any files (*.*)", "*.*");
        fileChooser.getExtensionFilters().add(extFilter);
        return fileChooser.showOpenDialog(scene.getWindow());
    }

    public static File saveFile(Scene scene) {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Save file");
        FileChooser.ExtensionFilter extFilter = new FileChooser.ExtensionFilter("Special files (*.se)", "*.se");
        fileChooser.getExtensionFilters().add(extFilter);
        return fileChooser.showSaveDialog(scene.getWindow());
    }
}
