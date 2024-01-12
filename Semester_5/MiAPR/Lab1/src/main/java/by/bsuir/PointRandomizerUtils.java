package by.bsuir;

import java.util.ArrayList;
import java.util.List;

public class PointRandomizerUtils {
    public static List<Point> randomizedPoints(int width, int height, int pointDiameter, int amount) {
        width -= pointDiameter;
        height -= pointDiameter;
        List<Point> result = new ArrayList<>();
        for (int i = 0; i < amount; ++i) {
            result.add(randomPointOf(width, height, i, 9));
        }
        return result;
    }

    private static Point randomPointOf(int width, int height, int n, int ofM) {
        double spread = Math.sqrt(ofM);
        double xs = width / spread; // x spacing
        double ys = height / spread; // y spacing
        n = n % ofM;
        double x = (n % spread) * xs;
        double y = (Math.floor(n / spread)) * ys;
        int xx = (int)(Math.random() * xs + x);
        int yy = (int)(Math.random() * ys + y);
        return new Point(xx, yy, Constants.DEFAULT_COLOR);
    }
}
