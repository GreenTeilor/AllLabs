package by.bsuir;

import by.bsuir.lab1.task12.Book;
import by.bsuir.lab1.task16.AuthorTitleComparator;
import by.bsuir.lab1.task16.AuthorTitlePriceComparator;
import by.bsuir.lab1.task16.TitleAuthorComparator;
import by.bsuir.lab1.task16.TitleComparator;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

public class Task16Test {
    private List<Book> books1;
    private List<Book> books2;

    @Before
    public void init() {
        books1 = new ArrayList<>(List.of(
                new Book("name1", "author2", 10),
                new Book("name1", "author1", 5),
                new Book("name4", "author4", 20),
                new Book("name1", "author3", 15))
        );

        books2 = new ArrayList<>(List.of(
                new Book("name4", "author4", 20),
                new Book("name1", "author1", 10),
                new Book("name3", "author1", 15),
                new Book("name3", "author1", 5))
        );
    }

    @Test
    public void testTitleComparator() {
        books1.sort(new TitleComparator());
        Assert.assertEquals(List.of(
                new Book("name1", "author2", 10),
                new Book("name1", "author1", 5),
                new Book("name1", "author3", 15),
                new Book("name4", "author4", 20)), books1);
    }

    @Test
    public void testTitleAuthorComparator() {
        books1.sort(new TitleAuthorComparator());
        Assert.assertEquals(List.of(
                new Book("name1", "author1", 5),
                new Book("name1", "author2", 10),
                new Book("name1", "author3", 15),
                new Book("name4", "author4", 20)), books1);
    }

    @Test
    public void testAuthorTitleComparator() {
        books2.sort(new AuthorTitleComparator());
        Assert.assertEquals(List.of(
                new Book("name1", "author1", 10),
                new Book("name3", "author1", 15),
                new Book("name3", "author1", 5),
                new Book("name4", "author4", 20)), books2);
    }

    @Test
    public void testAuthorTitlePriceComparator() {
        books2.sort(new AuthorTitlePriceComparator());
        Assert.assertEquals(List.of(
                new Book("name1", "author1", 10),
                new Book("name3", "author1", 5),
                new Book("name3", "author1", 15),
                new Book("name4", "author4", 20)), books2);
    }
}
