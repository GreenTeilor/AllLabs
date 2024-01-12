package by.bsuir.algorithm;

import by.bsuir.Constants;
import by.bsuir.Point;
import by.bsuir.PointRandomizerUtils;

import java.awt.*;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

public class K_means {
    private static Double calcDistance(Point point1, Point point2) {
        return Math.sqrt(Math.pow(point1.getX() - point2.getX(), 2.0) + Math.pow(point1.getY() - point2.getY(), 2.0));
    }

    private static void assignPointToCluster(List<Cluster> clusters, Point point) {
        clusters.stream().min(Comparator.comparing(c -> calcDistance(c.getCentroid(), point))).ifPresent(c -> {
            point.setColor(c.getColor());
            c.getPoints().add(point);
        });
    }

    private static void moveClusterCentroids(List<Cluster> clusters) {
        for (Cluster c : clusters) {
            double sumX = 0.0;
            double sumY = 0.0;
            for (Point p : c.getPoints()) {
                sumX += p.getX();
                sumY += p.getY();
                c.getCentroid().setX((int) sumX / c.getPoints().size());
                c.getCentroid().setY((int) sumY / c.getPoints().size());
            }
        }
    }

    //For lab2
    /*
    public static List<Cluster> k_means(int clustersAmount, List<Point> points) {
        List<Centroid> prev = new ArrayList<>();
        List<Cluster> clusters = new ArrayList<>();
        Set<Color> colors = new HashSet<>(Set.of(Color.GREEN, Color.YELLOW, Color.ORANGE, Color.BLUE, Color.CYAN));
        Iterator<Color> iterator = colors.iterator();
        List<Centroid> centroids = new ArrayList<>();
        PointRandomizerUtils.randomizedPoints(Constants.PANEL_WIDTH, Constants.PANEL_HEIGHT, Constants.POINTS_DIAMETER, clustersAmount).
                forEach(p -> centroids.add(new Centroid(p)));
        centroids.forEach(c -> clusters.add(new Cluster(c, new ArrayList<>(), iterator.next())));
        while (!clusters.stream().map(Cluster::getCentroid).toList().equals(prev)) {
            prev.clear();
            clusters.stream().map(Cluster::getCentroid).forEach(c -> prev.add(c.clone()));
            points.forEach(p -> assignPointToCluster(clusters, p));
            moveClusterCentroids(clusters);
        }
        return clusters;
    }
    */

    public static List<Cluster> k_means(List<Centroid> centroids, List<Point> points) {
        List<Centroid> prev = new ArrayList<>();
        List<Cluster> clusters = new ArrayList<>();
        Set<Color> colors = new HashSet<>(Set.of(Color.GREEN, Color.YELLOW, Color.ORANGE, Color.BLUE, Color.CYAN, Color.MAGENTA, Color.PINK, Color.GRAY));
        Iterator<Color> iterator = colors.iterator();
        centroids.forEach(c -> clusters.add(new Cluster(c, new ArrayList<>(), iterator.next())));
        while (!clusters.stream().map(Cluster::getCentroid).toList().equals(prev)) {
            prev.clear();
            clusters.stream().map(Cluster::getCentroid).forEach(c -> prev.add(c.clone()));
            clusters.forEach(c -> c.getPoints().clear());
            points.forEach(p -> assignPointToCluster(clusters, p));
            moveClusterCentroids(clusters);
        }
        return clusters;
    }

}
