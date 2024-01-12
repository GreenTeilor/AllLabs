package by.teachmeskills.springbootproject.composite;

import java.util.List;

public class Run {
    public static void main(String[] args) {
        Component phone1 = new Phone(5);
        Component phone2= new Phone(4);
        Component phone3 = new Phone(3);
        Component box1 = new Box(List.of(phone1, phone2, phone3));
        Component box2 = new Box(List.of(box1, phone2, phone3));
        Component box3 = new Box(List.of(box1, box2, phone1, phone2));
        System.out.println(box1 + "Box 1 price: " + box1.getPrice());
        System.out.println(box2 + "Box 2 price: " + box2.getPrice());
        System.out.println(box3 + "Box 3 price: " + box3.getPrice());
        System.out.println(phone1 + " Phone 1 price: " + phone1.getPrice());
    }
}
