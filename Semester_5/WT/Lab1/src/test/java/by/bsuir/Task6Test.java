package by.bsuir;

import by.bsuir.lab1.task6.Matrices;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class Task6Test {
    private double[] arr1;
    private double[] arr2;
    private double[] arr3;

    @Before
    public void init() {
        arr1 = new double[]{1.0};
        arr2 = new double[]{1.0, 2.0};
        arr3 = new double[]{1.0, 2.0, 3.0};
    }

    @Test
    public void testMinPops1() {
        Assert.assertArrayEquals(new double[][]{ {1.0} }, Matrices.convertToMatrix(arr1));
    }

    @Test
    public void testMinPops2() {
        Assert.assertArrayEquals(new double[][]{ {1.0, 2.0}, {2.0, 1.0} }, Matrices.convertToMatrix(arr2));
    }

    @Test
    public void testMinPops3() {
        Assert.assertArrayEquals(new double[][]{ {1.0, 2.0, 3.0}, {2.0, 3.0, 1.0}, {3.0, 1.0, 2.0} }, Matrices.convertToMatrix(arr3));
    }
}
