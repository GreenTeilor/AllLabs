package by.bsuir.lab1.task3;

import java.util.ArrayList;
import java.util.List;

public class FunctionValues {
    public static List<Double> calculate(double leftBorder, double rightBorder, double step) {
        List<Double> result = new ArrayList<>();
        while (leftBorder <= rightBorder) {
            result.add(Math.tan(leftBorder));
            leftBorder += step;
        }
        return result;
    }
}
