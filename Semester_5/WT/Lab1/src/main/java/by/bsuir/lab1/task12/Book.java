package by.bsuir.lab1.task12;

import java.util.Objects;

public class Book {
    private String title;
    private String author;
    private int price;
    private static int edition = 1;

    public Book() {

    }

    public Book(String title, String author, int price) {
        this.title = title;
        this.author = author;
        this.price = price;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    public static int getEdition() {
        return edition;
    }

    public static void setEdition(int edition) {
        Book.edition = edition;
    }

    @Override
    public int hashCode() {
        int prime = 17;
        return prime * Objects.hash(title, author, price, edition);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Book book)) return false;
        return Objects.equals(title, book.title) &&
                Objects.equals(author, book.author) && Objects.equals(price, book.price);
    }

    @Override
    public String toString() {
        return String.format("Book(title=%s, author=%s, price=%d, edition=%d)", title, author, price, edition);
    }
}
