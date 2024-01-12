package by.bsuir.lab1.task2;

public class PointsPosition {
    public static boolean isPointInArea(int x, int y) {
        if (y > 0 && y < 6) {
            return x > -5 && x < 5;
        } else if (y > -4 && y <= 0){
            return x > -7 && x < 7;
        }
        return false;
    }
}
