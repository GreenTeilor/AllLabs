package by.teachmeskills.springbootproject.composite;

public class Phone implements Component{
    private final int PRICE;
    public Phone(int price) {
        this.PRICE = price;
    }
    @Override
    public int getPrice() {
        return PRICE;
    }

    @Override
    public String toString() {
        return "Phone: " + PRICE;
    }
}
