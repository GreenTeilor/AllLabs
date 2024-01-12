package by.bsuir;

import java.awt.*;

public class Point {
    protected int x;
    protected int y;
    private Color color;
    private final static int DIAMETER = Constants.POINTS_DIAMETER;

    public Point(int x, int y, Color color) {
        this.x = x;
        this.y = y;
        this.color =  color;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public Color getColor() {
        return color;
    }

    public void setColor(Color color) {
        this.color = color;
    }

    public void draw(Graphics g) {
        g.setColor(color);
        g.fillOval(x, y, DIAMETER, DIAMETER);
    }
}
