package by.bsuir;

import by.bsuir.lab1.task4.PrimeNumbers;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.util.List;

public class Task4Test {
    private int[] arr1;
    private int[] arr2;
    private int[] arr3;

    @Before
    public void init() {
        arr1 = new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9, -10};
        arr2 = new int[]{0, 13, 15, 41, 94, 73, 21, 13};
        arr3 = new int[]{49, -26, -51, 12, 29, 5, 97, 98};
    }

    @Test
    public void testPrimesSearch1() {
        Assert.assertEquals(List.of(1, 2, 4, 6), PrimeNumbers.findIndexes(arr1));
    }

    @Test
    public void testPrimesSearch2() {
        Assert.assertEquals(List.of(1, 3, 5, 7), PrimeNumbers.findIndexes(arr2));
    }

    @Test
    public void testPrimesSearch3() {
        Assert.assertEquals(List.of(4, 5, 6), PrimeNumbers.findIndexes(arr3));
    }
}
