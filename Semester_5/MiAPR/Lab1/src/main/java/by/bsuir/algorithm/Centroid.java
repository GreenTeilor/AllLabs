package by.bsuir.algorithm;

import by.bsuir.Point;

import java.awt.*;

public class Centroid extends Point implements Cloneable {

    public Centroid(int x, int y, Color color) {
        super(x, y, color);
    }

    public Centroid(Point point) {
        super(point.getX(), point.getY(), point.getColor());
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Centroid centroid)) return false;
        return this.x == centroid.x && this.y == centroid.y;
    }

    @Override
    public Centroid clone() {
        try {
            return (Centroid) super.clone();
        } catch (CloneNotSupportedException e) {
            throw new AssertionError();
        }
    }
}
