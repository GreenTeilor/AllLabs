package by.bsuir;

import by.bsuir.lab1.task7.Sorting;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class Task7Test {
    private double[] arr1;
    private double[] arr2;
    private double[] arr3;
    private double[] arr4;

    @Before
    public void init() {
        arr1 = new double[]{1.0};
        arr2 = new double[]{1.0, -2.7, 4.12, 5.41, 6.12, 5.84, -1.0};
        arr3 = new double[]{1.0, 2.0, 3.0, 4.0};
        arr4 = new double[]{4.0, 3.0, 2.0, 1.0};
    }

    @Test
    public void testSort1() {
        Sorting.sort(arr1);
        Assert.assertArrayEquals(new double[]{1.0}, arr1, 0.01);
    }

    @Test
    public void testSort2() {
        Sorting.sort(arr2);
        Assert.assertArrayEquals(new double[]{-2.7, -1.0, 1.0, 4.12, 5.41, 5.84, 6.12}, arr2, 0.01);
    }

    @Test
    public void testSort3() {
        Sorting.sort(arr3);
        Assert.assertArrayEquals(new double[]{1.0, 2.0, 3.0, 4.0}, arr3, 0.01);
    }

    @Test
    public void testSort4() {
        Sorting.sort(arr4);
        Assert.assertArrayEquals(new double[]{1.0, 2.0, 3.0, 4.0}, arr4, 0.01);
    }
}
