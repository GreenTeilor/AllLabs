package by.bsuir;

import by.bsuir.lab1.task13.ProgrammerBook;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class Task13Test {
    ProgrammerBook book1;
    ProgrammerBook book2;
    ProgrammerBook book3;

    @Before
    public void init() {
        book1 = new ProgrammerBook("Java seventh edition", "Herbert Schildt", 5, "Java", 1);
        book2 = new ProgrammerBook();
        book3 = new ProgrammerBook("Java seventh edition", "Herbert Schildt", 5, "Java", 1);
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
        Assert.assertEquals(1356175343, book1.hashCode());
    }

    @Test
    public void testHashCode2() {
        Assert.assertEquals(890686751, book2.hashCode());
    }

    @Test
    public void testToString() {
        Assert.assertEquals("ProgrammerBook(super=Book(title=Java seventh edition, author=Herbert Schildt, price=5, edition=1), language=Java, level=1)", book1.toString());
    }
}
