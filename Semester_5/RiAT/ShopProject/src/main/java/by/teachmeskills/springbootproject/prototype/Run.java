package by.teachmeskills.springbootproject.prototype;

import java.util.ArrayList;
import java.util.Arrays;

public class Run {
    public static void main(String[] args) {
        Cow prototype = new Cow("Zvonochek", new ArrayList<>(Arrays.asList("corn", "peas")));
        Cow clone = (Cow)prototype.clone();
        System.out.println(prototype); //Expected: Name: Zvonochek, favorite food: [corn, peas]
        System.out.println(clone); //Expected: Name: Zvonochek, favorite food: [corn, peas]
        System.out.println(prototype.equals(clone)); //Expected: true
        clone.addFavoriteFood("grass");
        clone.changeName("Burenka");
        System.out.println(prototype); //Expected: Name: Zvonochek, favorite food: [corn, peas]
        System.out.println(clone); //Name: Burenka, favorite food: [corn, peas, grass]
        System.out.println(prototype.equals(clone)); //Expected: false
    }
}
