package by.bsuir;

import by.bsuir.lab1.task1.Calculations;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class Task1Test {
    private double x, y, result;

    @Before
    public void init() {
        x = 2.35;
        y = 3.45;
        result = 2.634;
    }

    @Test
    public void testCalculate() {
        Assert.assertEquals(result, Calculations.calculate(x, y), 0.001);
    }
}
