package com.example.lab3;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.List;

public class ApplicationController {

    @FXML
    private AnchorPane apScene;

    @FXML
    private Button btDecrypt;

    @FXML
    private Button btEncrypt;

    @FXML
    private Button btOpen;

    @FXML
    private Button btSave;

    @FXML
    private ComboBox<Integer> cbG;

    @FXML
    private Label lbG;

    @FXML
    private Label lbInput;

    @FXML
    private Label lbK;

    @FXML
    private Label lbMessage;

    @FXML
    private Label lbOutput;

    @FXML
    private Label lbP;

    @FXML
    private Label lbX;

    @FXML
    private Label lbResult;

    @FXML
    private TextArea taInput;

    @FXML
    private TextArea taOutput;

    @FXML
    private TextField tfK;

    @FXML
    private TextField tfP;

    @FXML
    private TextField tfX;

    private static byte[] bytesArrayM = null;
    private static byte[] bytesArrayC = null;

    @FXML
    void initialize() {
        btOpen.setOnAction(event -> {
            File file = FileOperationsUtils.openFile(Application.scene);
            try (FileInputStream binaryFile = new FileInputStream(file)){
                bytesArrayM = binaryFile.readAllBytes();
                if (!tfP.getText().isBlank()) {
                    int P = Integer.parseInt(tfP.getText());
                    if (P < 256) {
                        taInput.setText(FileOperationsUtils.toStringDecimal(bytesArrayM, 1));
                    } else if (P < 32768) {
                        taInput.setText(FileOperationsUtils.toStringDecimal(bytesArrayM, 2));
                    } else {
                        taInput.setText(FileOperationsUtils.toStringDecimal(bytesArrayM, 4));
                    }
                } else {
                    taInput.setText(FileOperationsUtils.toStringDecimal(bytesArrayM, 1));
                }
                //taInput.setText(FileOperationsUtils.toStringDecimal(bytesArrayM, 1));
            } catch (IOException | NullPointerException e) {

            }
        });

        btSave.setOnAction(event -> {
            File file = FileOperationsUtils.saveFile(Application.scene);
            try (FileOutputStream binaryFile = new FileOutputStream(file)) {
                if (bytesArrayC != null) {
                    binaryFile.write(bytesArrayC);
                }
            } catch (IOException | NullPointerException e) {

            }
        });

        btEncrypt.setOnAction(event -> {
            lbResult.setVisible(true);
            if (bytesArrayM == null) {
                lbResult.setTextFill(Color.RED);
                lbResult.setText("Ошибка! Файл не открыт!");
                return;
            }
            if (!tfP.getText().isBlank() && !tfK.getText().isBlank() && !tfX.getText().isBlank() && cbG.getValue() != null) {
                int P = Integer.parseInt(tfP.getText());
                int K = Integer.parseInt(tfK.getText());
                int X = Integer.parseInt(tfX.getText());
                int G = cbG.getValue();
                if (ValidatorUtils.isValidP(P) && ValidatorUtils.isValidK(K, P) && ValidatorUtils.isValidX(X, P)) {
                    int Y = ElGamalEncryptionUtils.calculateY(P, G, X);
                    bytesArrayC = ElGamalEncryptionUtils.encrypt(P, G, bytesArrayM, Y, K);
                    if (P < 128) {
                        taOutput.setText(FileOperationsUtils.toStringDecimal(bytesArrayC, 1));
                    } else if (P < 32768) {
                        taOutput.setText(FileOperationsUtils.toStringDecimal(bytesArrayC, 2));
                    } else {
                        taOutput.setText(FileOperationsUtils.toStringDecimal(bytesArrayC, 4));
                    }
                    lbResult.setTextFill(Color.GREEN);
                    lbResult.setText("Успешно!");
                } else {
                    lbResult.setTextFill(Color.RED);
                    lbResult.setText("Ошибка! Какое-либо значение введено неверно!");
                    taOutput.clear();
                }
            } else {
                lbResult.setTextFill(Color.RED);
                lbResult.setText("Ошибка! Какое-либо из полей пустое!");
                taOutput.clear();
            }
        });

        btDecrypt.setOnAction(event -> {
            lbResult.setVisible(true);
            if (bytesArrayM == null) {
                lbResult.setTextFill(Color.RED);
                lbResult.setText("Ошибка! Файл не открыт!");
                return;
            }
            if (!tfP.getText().isBlank() && !tfK.getText().isBlank() && !tfX.getText().isBlank() && cbG.getValue() != null) {
                int P = Integer.parseInt(tfP.getText());
                int K = Integer.parseInt(tfK.getText());
                int X = Integer.parseInt(tfX.getText());
                int G = cbG.getValue();
                int numberSize = 0;
                if (ValidatorUtils.isValidP(P) && ValidatorUtils.isValidK(K, P) && ValidatorUtils.isValidX(X, P)) {
                    if (P < 128) {
                        numberSize = 1;
                    } else if (P < 32768) {
                        numberSize = 2;
                    } else {
                        numberSize = 4;
                    }
                    bytesArrayC = ElGamalEncryptionUtils.decrypt(bytesArrayM, P, X,numberSize);
                    taOutput.setText(FileOperationsUtils.toStringDecimal(bytesArrayC, 1));
                    lbResult.setTextFill(Color.GREEN);
                    lbResult.setText("Успешно!");
                }
                else {
                    lbResult.setTextFill(Color.RED);
                    lbResult.setText("Ошибка! Какое-либо значение введено неверно!");
                    taOutput.clear();
                }
            } else {
                lbResult.setTextFill(Color.RED);
                lbResult.setText("Ошибка! Какое-либо из полей пустое!");
                taOutput.clear();
            }
        });

        tfP.textProperty().addListener((observable, oldValue, newValue) -> {
            cbG.getItems().clear();
            if (!newValue.matches("\\d*")) {
                tfP.setText(newValue.replaceAll("\\D", ""));
            }
        });

        tfK.textProperty().addListener((observable, oldValue, newValue) -> {
            if (!newValue.matches("\\d*")) {
                tfK.setText(newValue.replaceAll("\\D", ""));
            }
        });

        tfX.textProperty().addListener((observable, oldValue, newValue) -> {
            if (!newValue.matches("\\d*")) {
                tfX.setText(newValue.replaceAll("\\D", ""));
            }
        });

        cbG.setOnMouseClicked(event -> {
            cbG.getItems().clear();
            if (!tfP.getText().isBlank() && ValidatorUtils.isValidP(Integer.parseInt(tfP.getText()))) {
                List<Integer> roots = AlgorithmsUtils.findRoots(Integer.parseInt(tfP.getText()));
                cbG.getItems().addAll(roots);
            }
        });
    }

}

