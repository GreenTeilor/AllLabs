package by.bsuir;

import by.bsuir.lab1.task3.FunctionValues;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.util.List;

public class Task3Test {
    private double leftBorder1, rightBorder1, step1;
    private double leftBorder2, rightBorder2, step2;
    private double leftBorder3, rightBorder3, step3;

    @Before
    public void init() {
        leftBorder1 = 0.1;
        rightBorder1 = 0.4;
        step1 = 0.05;
        leftBorder2 = 0.0;
        rightBorder2 = 0.38;
        step2 = 0.03;
        leftBorder3 = 0.3;
        rightBorder3 = 0.78;
        step3 = 0.1;
    }

    @Test
    public void testFunctionValues1() {
        Assert.assertEquals(List.of(0.10033467208545055, 0.1511352180582951, 0.2027100355086725, 0.25534192122103627,
                        0.30933624960962325, 0.36502849483042454, 0.4227932187381617),
                FunctionValues.calculate(leftBorder1, rightBorder1, step1));
    }

    @Test
    public void testFunctionValues2() {
        Assert.assertEquals(List.of(0.0, 0.030009003241180714, 0.06007210383129728, 0.09024378990978545,
                        0.1205793372113053, 0.15113521805829508, 0.18196952904019847, 0.2131424443826454,
                        0.24471670271446497, 0.27675813587503056, 0.3093362496096233, 0.342524867530039, 0.3764028516420271),
                FunctionValues.calculate(leftBorder2, rightBorder2, step2));
    }

    @Test
    public void testFunctionValues3() {
        Assert.assertEquals(List.of(0.30933624960962325, 0.4227932187381618, 0.5463024898437905, 0.6841368083416923, 0.8422883804630794),
                FunctionValues.calculate(leftBorder3, rightBorder3, step3));
    }
}
