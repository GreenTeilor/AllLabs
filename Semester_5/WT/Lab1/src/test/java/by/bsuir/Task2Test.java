package by.bsuir;

import by.bsuir.lab1.task2.PointsPosition;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class Task2Test {
    private int x1, y1;
    private int x2, y2;
    private int x3, y3;

    @Before
    public void init() {
        x1 = 2;
        y1 = 3;
        x2 = 6;
        y2 = 0;
        x3 = -3;
        y3 = -7;
    }

    @Test
    public void testIsPoint1InArea() {
        Assert.assertTrue(PointsPosition.isPointInArea(x1, y1));
    }

    @Test
    public void testIsPoint2InArea() {
        Assert.assertTrue(PointsPosition.isPointInArea(x2, y2));
    }

    @Test
    public void testIsPoint3InArea() {
        Assert.assertFalse(PointsPosition.isPointInArea(x3, y3));
    }
}
