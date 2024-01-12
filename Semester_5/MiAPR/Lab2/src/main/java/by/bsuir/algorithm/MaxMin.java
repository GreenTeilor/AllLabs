package by.bsuir.algorithm;

import by.bsuir.Constants;
import by.bsuir.Point;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class MaxMin {
    private final static Set<Color> colors = generateColors();
    private static Iterator<Color> iterator = colors.iterator();

    public static Double calcDistance(Point point1, Point point2) {
        return Math.sqrt(Math.pow(point1.getX() - point2.getX(), 2.0) + Math.pow(point1.getY() - point2.getY(), 2.0));
    }

    public static void assignPointToCluster(List<Cluster> clusters, Point point) {
        clusters.stream().min(Comparator.comparing(c -> calcDistance(c.getCentroid(), point))).ifPresent(c -> {
            point.setColor(c.getColor());
            c.getPoints().add(point);
        });
    }

    public static Double calcAvgCoreDistance(List<Centroid> centroids) {
        class Pair {
            private final Centroid centroid1;
            private final Centroid centroid2;

            public Pair(Centroid centroid1, Centroid centroid2) {
                this.centroid1 = centroid1;
                this.centroid2 = centroid2;
            }

            public Double calcDistance() {
                return MaxMin.calcDistance(centroid1, centroid2);
            }
        }

        List<Pair> pairs = new ArrayList<>();
        for (int i = 0; i < centroids.size() - 1; ++i) {
            for (int j = i + 1; j < centroids.size(); ++j) {
                pairs.add(new Pair(centroids.get(i), centroids.get(j)));
            }
        }

        Double distancesSum = pairs.stream().reduce(0.0, (p1, p2) -> p1 + p2.calcDistance(), Double::sum);
        return distancesSum / pairs.size();
    }

    public static Set<Color> generateColors() {
        Set<Color> colors = new HashSet<>();
        for (int red = 0; red < 256; red = red + 64) {
            for (int green = 0; green < 256; green = green + 64) {
                for (int blue = 0; blue < 193; blue = blue + 64) {
                    colors.add(new Color(red, green, blue));
                }
            }
        }
        colors.remove(new Color(255,0,0));
        return colors;
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

    public static List<Cluster> k_means(List<Centroid> centroids, List<Point> points) {
        List<Centroid> prev = new ArrayList<>();
        List<Cluster> clusters = new ArrayList<>();
        Set<Color> colors = points.stream().map(Point::getColor).collect(Collectors.toSet());
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

    public static List<Cluster> generate(List<Point> points) {
        iterator = colors.iterator();
        Point initPoint = points.get((int) (Math.random() * points.size()));
        Point maxDistancePoint = points.stream().max(Comparator.comparing(p -> calcDistance(initPoint, p))).
                orElse(null);
        Centroid centroid1 = new Centroid(initPoint, Constants.CENTROID_COLOR);
        Centroid centroid2 = new Centroid(maxDistancePoint, Constants.CENTROID_COLOR);

        Cluster cluster1 = new Cluster(centroid1, new ArrayList<>(), iterator.next());
        Cluster cluster2 = new Cluster(centroid2, new ArrayList<>(), iterator.next());
        List<Cluster> clusters = new ArrayList<>();
        clusters.add(cluster1);
        clusters.add(cluster2);
        points.forEach(p -> assignPointToCluster(clusters, p));
        return clusters;
    }

    public static List<Cluster> maxMin(List<Point> points, List<Cluster> clusters, JButton btIterate, JButton btK_means) {
        //while (true) {
            clusters.forEach(c -> c.getPoints().clear());
            points.forEach(p -> assignPointToCluster(clusters, p));
            List<Point> maxDistancePoints = new ArrayList<>();
            List<Double> maxDistances = new ArrayList<>();
            for (Cluster c : clusters) {
                Point point = new Point(0, 0, Color.BLACK);
                double max = -1;
                for (Point p : c.getPoints()) {
                    double distance = calcDistance(p, c.getCentroid());
                    if (distance > max) {
                        max = distance;
                        point = p;
                    }
                }
                maxDistancePoints.add(point);
                maxDistances.add(max);
            }
            Centroid newCentroid = new Centroid(maxDistancePoints.get(IntStream.range(0, maxDistances.size())
                    .reduce((i, j) -> maxDistances.get(i) > maxDistances.get(j) ? i : j)
                    .getAsInt()), Constants.CENTROID_COLOR);
            if (calcAvgCoreDistance(clusters.stream().map(Cluster::getCentroid).toList()) / 2 >= maxDistances.stream().mapToDouble(d -> d).max().getAsDouble()) {
                btIterate.setVisible(false);
                btK_means.setVisible(true);
                return clusters;
            }
            clusters.add(new Cluster(newCentroid, new ArrayList<>(), iterator.next()));
        //}
        return clusters;
    }

}
