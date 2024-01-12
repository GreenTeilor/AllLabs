package by.bsuir.lab1.task9;

public class Ball {
    private int weight;
    private Color color;

    public Ball(int weight, Color color) {
        this.weight = weight;
        this.color = color;
    }

    public enum Color {
        YELLOW("yellow"), GREEN("green"), RED("red");
        private final String name;
        Color (String name) {
            this.name = name;
        }

        @Override
        public String toString() {
            return name;
        }
    }

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public Color getColor() {
        return color;
    }

    public void setColor(Color color) {
        this.color = color;
    }
}
