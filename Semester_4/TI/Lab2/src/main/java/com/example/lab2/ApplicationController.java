package com.example.lab2;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ApplicationController {

    @FXML
    private AnchorPane apScene;

    @FXML
    private Button btEncrypt;

    @FXML
    private Button btOpen;

    @FXML
    private Button btSave;

    @FXML
    private Label lbGeneratedKey;

    @FXML
    private Label lbInput;

    @FXML
    private Label lbKey;

    @FXML
    private Label lbMessage;

    @FXML
    private Label lbOutput;

    @FXML
    private TextArea taGeneratedKey;

    @FXML
    private TextArea taInput;

    @FXML
    private TextArea taOutput;

    @FXML
    private TextField tfKey;

    private static byte[] bytesArrayM = null;
    private static byte[] bytesArrayC = null;

    @FXML
    void initialize() {
        btOpen.setOnAction(event -> {
            File file = FileOperationsUtil.openFile(Application.scene);
            try (FileInputStream binaryFile = new FileInputStream(file)){
                bytesArrayM = binaryFile.readAllBytes();
                taInput.setText(FileOperationsUtil.toStringBinary(bytesArrayM));
            } catch (IOException | NullPointerException e) {

            }
        });

        btSave.setOnAction(event -> {
            File file = FileOperationsUtil.saveFile(Application.scene);
            try (FileOutputStream binaryFile = new FileOutputStream(file)) {
                if (bytesArrayC != null) {
                    binaryFile.write(bytesArrayC);
                }
            } catch (IOException | NullPointerException e) {

            }
        });

        btEncrypt.setOnAction(event -> {
            if (bytesArrayM != null) {
                String stringKey = FileOperationsUtil.validateKey(tfKey.getText().trim());
                if (FileOperationsUtil.isValidKey(stringKey)) {
                    int key = FileOperationsUtil.fetchKey(stringKey);
                    byte[] generatedKey = StreamEncryption.generateKey(key, bytesArrayM.length * 8);
                    bytesArrayC = StreamEncryption.transform(bytesArrayM, generatedKey);
                    taOutput.setText(FileOperationsUtil.toStringBinary(bytesArrayC));
                    taGeneratedKey.setText(FileOperationsUtil.toStringBinary(generatedKey));
                    taOutput.setText(FileOperationsUtil.toStringBinary(bytesArrayC));
                    lbMessage.setVisible(true);
                    lbMessage.setTextFill(Color.color(0, 1 ,0));
                    lbMessage.setText("Успешно!");
                }
                else {
                    lbMessage.setVisible(true);
                    lbMessage.setTextFill(Color.color(1, 0 ,0));
                    lbMessage.setText("Неверный ключ!");
                    taGeneratedKey.clear();
                    taOutput.clear();
                }
            }
        });
    }

}

