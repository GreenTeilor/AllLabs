package by.bsuir.lab1.task16;

import by.bsuir.lab1.task12.Book;

import java.util.Comparator;

public class AuthorTitleComparator implements Comparator<Book> {
    @Override
    public int compare(Book b1, Book b2) {
        Comparator<Book> titleComparator = Comparator.comparing(Book::getTitle);
        Comparator<Book> authorComparator = Comparator.comparing(Book::getAuthor);
        return authorComparator.thenComparing(titleComparator).compare(b1, b2);
    }
}
