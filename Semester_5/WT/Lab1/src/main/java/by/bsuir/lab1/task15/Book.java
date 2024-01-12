package by.bsuir.lab1.task15;

import java.util.Objects;

public class Book implements Comparable<Book> {
    private String title;
    private String author;
    private int price;
    private static int edition = 1;
    private int isbn;

    public Book() {

    }

    public Book(String title, String author, int price, int isbn) {
        this.title = title;
        this.author = author;
        this.price = price;
        this.isbn = isbn;
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

    public int getIsbn() {
        return isbn;
    }

    public void setIsbn(int isbn) {
        this.isbn = isbn;
    }

    @Override
    public int hashCode() {
        int prime = 17;
        return prime * Objects.hash(title, author, price, edition, isbn);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Book book)) return false;
        return Objects.equals(title, book.title) &&
                Objects.equals(author, book.author) && Objects.equals(price, book.price) && Objects.equals(isbn, book.isbn);
    }

    @Override
    public String toString() {
        return String.format("Book(title=%s, author=%s, price=%d, edition=%d, isbn=%d)", title, author, price, edition, isbn);
    }

    @Override
    public int compareTo(Book book) {
        return isbn - book.isbn;
    }
}
