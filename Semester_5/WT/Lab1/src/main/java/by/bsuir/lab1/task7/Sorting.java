package by.bsuir.lab1.task7;

public class Sorting {
    public static void sort(double[] array) {
        int h = 1;
        while (h * 3 < array.length)
            h = h * 3 + 1;

        while (h >= 1) {
            hSort(array, h);
            h = h / 3;
        }
    }

    private static void hSort(double[] array, int h) {
        int length = array.length;
        for (int i = h; i < length; i++) {
            for (int j = i; j >= h; j = j - h) {
                if (array[j] < array[j - h])
                    swap(array, j, j - h);
                else
                    break;
            }
        }
    }

    private static void swap(double[] array, int j, int i) {
        double temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
