package by.bsuir;

import by.bsuir.lab1.task12.Book;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class Task12Test {
    Book book1;
    Book book2;
    Book book3;

    @Before
    public void init() {
        book1 = new Book("20000 leagues under the water", "Jules Verne", 5);
        book2 = new Book();
        book3 = new Book("20000 leagues under the water", "Jules Verne", 5);
    }

    @Test
    public void testEquals1() {
        Assert.assertEquals(book1, book3);
    }

    @Test
    public void testEquals2() {
        Assert.assertNotEquals(book1, null);
    }

    @Test
    public void testEquals3() {
        Assert.assertNotEquals(book2, book1);
    }

    @Test
    public void testHashCode1() {
        Assert.assertEquals(1906259600, book1.hashCode());
    }

    @Test
    public void testHashCode2() {
        Assert.assertEquals(15699874, book2.hashCode());
    }

    @Test
    public void testToString() {
        Assert.assertEquals("Book(title=20000 leagues under the water, author=Jules Verne, price=5, edition=1)", book1.toString());
    }


}
