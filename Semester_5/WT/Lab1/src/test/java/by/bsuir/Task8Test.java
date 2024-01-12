package by.bsuir;

import by.bsuir.lab1.task8.AscendingSequences;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.util.List;

public class Task8Test {
    private List<Double> insertTo1;
    private List<Double> insert1;
    private List<Double> insertTo2;
    private List<Double> insert2;

    @Before
    public void init() {
        insertTo1 = List.of(1.0);
        insert1 = List.of(0.5);
        insertTo2 = List.of(1.0, 2.0, 3.0, 4.0);
        insert2 = List.of(2.0, 3.0, 5.0);
    }

    @Test
    public void testSort1() {
        Assert.assertEquals(List.of(1), AscendingSequences.findInsertPositions(insertTo1, insert1));
    }

    @Test
    public void testSort2() {
        Assert.assertEquals(List.of(2, 4, 6), AscendingSequences.findInsertPositions(insertTo2, insert2));
    }
}
