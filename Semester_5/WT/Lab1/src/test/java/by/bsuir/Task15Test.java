package by.bsuir;

import by.bsuir.lab1.task15.Book;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Task15Test {
    private List<Book> books;

    @Before
    public void init() {
        books = new ArrayList<>(List.of(
                new Book("name1", "author1", 5, 5),
                new Book("name2", "author2", 10, 3),
                new Book("name3", "author3", 15, 1),
                new Book("name4", "author4", 20, 8))
        );
    }

    @Test
    public void testComparable() {
        Collections.sort(books);
        Assert.assertEquals(List.of(new Book("name3", "author3", 15, 1),
                new Book("name2", "author2", 10, 3),
                new Book("name1", "author1", 5, 5),
                new Book("name4", "author4", 20, 8)), books);
    }
}
