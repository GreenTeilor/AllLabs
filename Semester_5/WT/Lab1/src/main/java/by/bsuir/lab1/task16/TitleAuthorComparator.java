package by.bsuir.lab1.task16;

import by.bsuir.lab1.task12.Book;

import java.util.Comparator;

public class TitleAuthorComparator implements Comparator<Book> {
    @Override
    public int compare(Book b1, Book b2) {
        Comparator<Book> titleComparator = Comparator.comparing(Book::getTitle);
        Comparator<Book> authorComparator = Comparator.comparing(Book::getAuthor);
        return titleComparator.thenComparing(authorComparator).compare(b1, b2);
    }
}
