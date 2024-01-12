package by.bsuir.lab1.task9;

import java.util.List;

public class Run {
    public static void main(String[] args) {
        Basket basket = new Basket(List.of(new Ball(0, Ball.Color.RED), new Ball(5, Ball.Color.GREEN),
                new Ball(3, Ball.Color.RED)));
        System.out.printf("Weight of balls: %d; Amount of red balls: %d", basket.getBallsWeight(), basket.getAmountBallsOfColor(Ball.Color.RED));
    }
}
