package by.bsuir;

import by.bsuir.lab1.task5.AscendingOrder;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;


public class Task5Test {
    private int[] arr1;
    private int[] arr2;
    private int[] arr3;
    private int[] arr4;

    @Before
    public void init() {
        arr1 = new int[]{1, 2, 3, -7, 8};
        arr2 = new int[]{1, 3, 4, 3, 3, 5, 6};
        arr3 = new int[]{-3, 4, -3, 8, 4, -3};
        arr4 = new int[]{1, 2, 3};
    }

    @Test
    public void testMinPops1() {
        Assert.assertEquals(1, AscendingOrder.findMinPops(arr1));
    }

    @Test
    public void testMinPops2() {
        Assert.assertEquals(2, AscendingOrder.findMinPops(arr2));
    }

    @Test
    public void testMinPops3() {
        Assert.assertEquals(3, AscendingOrder.findMinPops(arr3));
    }

    @Test
    public void testMinPops4() {
        Assert.assertEquals(0, AscendingOrder.findMinPops(arr4));
    }
}
