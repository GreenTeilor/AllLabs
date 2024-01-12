package by.bsuir.lab1.task6;

public class Matrices {
    public static double[][] convertToMatrix(double... numbers) {
        double[][] result = new double[numbers.length][numbers.length];
        for (int i = 0; i < numbers.length; ++i) {
            System.arraycopy(numbers, i, result[i], 0, numbers.length - i);
            System.arraycopy(numbers, 0, result[i], numbers.length - i, i);
        }
        return result;
    }
}
