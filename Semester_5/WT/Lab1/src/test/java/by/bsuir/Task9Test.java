package by.bsuir;

import by.bsuir.lab1.task9.Ball;
import by.bsuir.lab1.task9.Ball.Color;
import by.bsuir.lab1.task9.Basket;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.util.List;

public class Task9Test {
    private Basket basket1;
    private Basket basket2;
    private Basket basket3;

    @Before
    public void init() {
        basket1 = new Basket(List.of(new Ball(4, Color.RED), new Ball(5, Color.GREEN)));
        basket2 = new Basket(List.of(new Ball(0, Color.RED), new Ball(5, Color.GREEN),
                new Ball(3, Color.RED)));
        basket3 = new Basket(List.of());
    }

    @Test
    public void testBallsWeight1() {
        Assert.assertEquals(9, basket1.getBallsWeight());
    }

    @Test
    public void testAmountBallsOfColor1() {
        Assert.assertEquals(1, basket1.getAmountBallsOfColor(Color.GREEN));
    }

    @Test
    public void testBallsWeight2() {
        Assert.assertEquals(8, basket2.getBallsWeight());
    }

    @Test
    public void testAmountBallsOfColor2() {
        Assert.assertEquals(2, basket2.getAmountBallsOfColor(Color.RED));
    }

    @Test
    public void testBallsWeight3() {
        Assert.assertEquals(0, basket3.getBallsWeight());
    }

    @Test
    public void testAmountBallsOfColor3() {
        Assert.assertEquals(0, basket3.getAmountBallsOfColor(Color.YELLOW));
    }
}
