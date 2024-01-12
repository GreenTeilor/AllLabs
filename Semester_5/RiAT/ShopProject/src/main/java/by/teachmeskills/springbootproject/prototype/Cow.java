package by.teachmeskills.springbootproject.prototype;

import java.util.ArrayList;
import java.util.List;

public class Cow implements Prototype{
    private String name;
    private List<String> favoriteFood;

    Cow(String name, List<String> favoriteFood) {
        this.name = name;
        this.favoriteFood = favoriteFood;
    }

    public void changeName(String name) {
        this.name = name;
    }

    public void addFavoriteFood(String food) {
        favoriteFood.add(food);
    }

    @Override
    public Prototype clone() {
        List<String> favoriteFood = new ArrayList<>(this.favoriteFood);
        return new Cow(name, favoriteFood);
    }

    @Override
    public String toString() {
        return "Name: " + name + ", favorite food: " + favoriteFood;
    }

    @Override
    public boolean equals(Object o) {
        if (!(o instanceof Cow))
            return false;
        return ((Cow) o).favoriteFood.equals(this.favoriteFood) && ((Cow) o).name.equals(this.name);
    }
}
