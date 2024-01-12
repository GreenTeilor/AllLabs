package by.bsuir.lab1.task8;

import java.util.ArrayList;
import java.util.List;

public class AscendingSequences {
    public static List<Integer> findInsertPositions(List<Double> seq1, List<Double> seq2) {
        int indexA = 0;
        int indexB = 0;
        List<Double> seq1Copy = new ArrayList<>(seq1);
        List<Integer> result = new ArrayList<>();
        while (indexB != seq2.size() && indexA != seq1Copy.size() - 1) {
            if (seq1Copy.get(indexA) <= seq2.get(indexB) && seq1Copy.get(indexA + 1) > seq2.get(indexB)) {
                indexA++;
                result.add(indexA);
                seq1Copy.add(indexA, seq2.get(indexB));
                indexB++;
            } else {
                indexA++;
            }
        }
        while (indexB != seq2.size()) {
            result.add(indexA+1);
            indexA++;
            indexB++;
        }
        return result;
    }
}
