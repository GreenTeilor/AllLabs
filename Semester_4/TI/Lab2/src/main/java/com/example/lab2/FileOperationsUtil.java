package com.example.lab2;

import javafx.scene.Scene;
import javafx.stage.FileChooser;

import java.io.File;

public class FileOperationsUtil {
    public static String toStringBinary(byte[] bytes) {
        if (bytes != null) {
            StringBuilder binaryRepresentation = new StringBuilder(1024 * 100);
            if (bytes.length <= 1024 * 100) {
                for (byte currentByte : bytes) {
                    binaryRepresentation.append(String.format("%8s", Integer.toBinaryString(currentByte & 0xFF)).replace(' ', '0'));
                }
            } else {
                binaryRepresentation.append("Начало файла:\r\n");
                for (int i = 0; i < 100; ++i) {
                    binaryRepresentation.append(String.format("%8s", Integer.toBinaryString(bytes[i] & 0xFF)).replace(' ', '0'));
                }
                binaryRepresentation.append("\r\nКонец файла:\r\n");
                for (int i = bytes.length - 100; i < bytes.length; ++i) {
                    binaryRepresentation.append(String.format("%8s", Integer.toBinaryString(bytes[i] & 0xFF)).replace(' ', '0'));
                }
            }
            return binaryRepresentation.toString();
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
