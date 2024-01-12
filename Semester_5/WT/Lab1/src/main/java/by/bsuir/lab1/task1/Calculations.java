package by.bsuir.lab1.task1;

import static java.lang.Math.pow;

public class Calculations {
    public static double calculate(double x, double y) {
        return (1 + pow(Math.sin(x + y), 2)) / (2 + Math.abs(x - (2 * x) / (1 + pow(x, 2) * pow(y, 2)))) + x;
    }
}
