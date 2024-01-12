package by.bsuir.lab1.task4;

import java.util.List;

import java.util.stream.IntStream;

public class PrimeNumbers {
    private static boolean isPrime(int number) {
        return number > 1 && IntStream.range(2, (int)Math.sqrt(number) + 1).filter(divider -> number % divider == 0).findAny().isEmpty();
    }

    public static List<Integer> findIndexes(int[] numbers) {
        return IntStream.range(0, numbers.length).filter(index -> isPrime(numbers[index])).boxed().toList();
    }
}
