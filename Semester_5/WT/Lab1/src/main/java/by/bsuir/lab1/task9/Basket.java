package by.bsuir.lab1.task9;

import java.util.List;

public class Basket {
    private final List<Ball> balls;

    public Basket(List<Ball> balls) {
        this.balls = balls;
    }

    public int getBallsWeight() {
        return balls.stream().reduce(0, (prev, b2) -> prev + b2.getWeight(), Integer::sum);
    }

    public int getAmountBallsOfColor(Ball.Color color) {
        return balls.stream().reduce(0, (prev, b2) -> {
            if (b2.getColor() == color) {
                return prev + 1;
            }
            return prev;
        }, Integer::sum);
    }
}
