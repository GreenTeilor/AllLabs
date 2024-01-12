package by.bsuir.algorithm;

import java.awt.*;
import java.util.List;
import by.bsuir.Point;

public class Cluster {
    private Centroid centroid;
    private List<Point> points;
    private Color color;

    public Cluster(Centroid centroid, List<Point> points, Color color) {
        this.centroid = centroid;
        this.points = points;
        this.color = color;
    }

    public Centroid getCentroid() {
        return centroid;
    }

    public void setCentroid(Centroid centroid) {
        this.centroid = centroid;
    }

    public List<Point> getPoints() {
        return points;
    }

    public void setPoints(List<Point> points) {
        this.points = points;
    }

    public Color getColor() {
        return color;
    }

    public void setColor(Color color) {
        this.color = color;
    }
}
