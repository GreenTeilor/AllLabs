package by.bsuir.lab1.task5;

public class AscendingOrder {
    public static int findMinPops(int[] arr) {
        int n = arr.length;
        int maxAscOrderLength = 0;
        int[] maxSequences = new int[n];
        for (int i = 0; i < n; ++i) {
            maxSequences[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (arr[j] < arr[i] && maxSequences[j] + 1 > maxSequences[i])
                    maxSequences[i] = maxSequences[j] + 1;
            }
            if (maxAscOrderLength < maxSequences[i])
                maxAscOrderLength = maxSequences[i];
        }
        return n - maxAscOrderLength;
    }
}
