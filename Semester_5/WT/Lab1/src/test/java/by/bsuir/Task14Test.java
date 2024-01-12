package by.bsuir;

import by.bsuir.lab1.task14.Book;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class Task14Test {
    Book book1;
    Book book2;

    @Before
    public void init() {
        book1 = new Book("20000 leagues under the water", "Jules Verne", 5);
        book2 = new Book();
    }

    @Test
    public void testCloneOnAllArgsConstructor() {
        Book clone = book1.clone();
        Assert.assertEquals(book1, clone);
    }

    @Test
    public void testCloneOnNoArgsConstructor() {
        Book clone = book2.clone();
        Assert.assertEquals(book2, clone);
    }
}
