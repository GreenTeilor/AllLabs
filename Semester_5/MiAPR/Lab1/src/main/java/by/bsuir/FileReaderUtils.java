package by.bsuir;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class FileReaderUtils {
    public static List<Point> getPoints() throws FileNotFoundException {
        List<Point> result = new ArrayList<>();
        Scanner scanner = new Scanner(new File("src/main/resources/points.txt"));
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] c = line.split(" ");
            Point coordinates = new Point(Integer.parseInt(c[0]), Integer.parseInt(c[1]), Constants.DEFAULT_COLOR);
            result.add(coordinates);
        }
        return result;
    }

}
