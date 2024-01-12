package by.bsuir;


import by.bsuir.algorithm.Centroid;

import javax.swing.*;
import java.awt.*;
import java.util.List;
import java.util.Optional;

public class Panel extends JPanel {

    private List<Point> points;
    private List<Centroid> centroids;

    public Panel(List<Point> points, List<Centroid> centroids) {
        this.points = points;
        this.centroids = centroids;
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Optional.ofNullable(points).ifPresent(ps -> ps.forEach(p -> p.draw(g)));
        Optional.ofNullable(centroids).ifPresent(cs -> cs.forEach(c -> c.draw(g)));
    }

    public List<Point> getPoints() {
        return points;
    }

    public void setPoints(List<Point> points) {
        this.points = points;
    }

    public List<Centroid> getCentroids() {
        return centroids;
    }

    public void setCentroids(List<Centroid> centroids) {
        this.centroids = centroids;
    }
}
