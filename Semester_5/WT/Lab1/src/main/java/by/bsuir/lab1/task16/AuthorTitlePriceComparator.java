package by.bsuir.lab1.task16;

import by.bsuir.lab1.task12.Book;

import java.util.Comparator;

public class AuthorTitlePriceComparator implements Comparator<Book> {
    @Override
    public int compare(Book b1, Book b2) {
        Comparator<Book> authorTitleComparator = new AuthorTitleComparator();
        Comparator<Book> priceComparator = Comparator.comparing(Book::getPrice);
        return authorTitleComparator.thenComparing(priceComparator).compare(b1, b2);
    }
}
