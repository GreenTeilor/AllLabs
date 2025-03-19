import org.apache.poi.ss.usermodel.*;
import org.apache.poi.util.IOUtils;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;
import org.jfree.chart.ChartColor;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.statistics.HistogramDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.*;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

// 1 1003 9991 31381059609
// 2 2493 10465 1073741824
// 3 8982 17 96889010407

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long x0, a, c, m;
        int k, n;

        while (true) {
            System.out.print("Input x0: ");
            x0 = getValidInput(1, Long.MAX_VALUE, scanner);

            System.out.print("Input a: ");
            a = getValidInput(1, Long.MAX_VALUE, scanner);

            System.out.print("Input c: ");
            c = getValidInput(0, Long.MAX_VALUE, scanner);

            System.out.print("Input m: ");
            m = getValidInput(Math.max(Math.max(a, c), x0) + 1, Long.MAX_VALUE, scanner);

            if (isValidLemerParameters(a, c, m)) {

                System.out.print("Input k: ");
                k = (int) getValidInput(10, 40, scanner);

                System.out.print("Input n: ");
                n = (int) getValidInput(100, 100_000, scanner);

                break;
            }

            System.out.println("Error: invalid generator parameters");
        }

        List<Double> randomNumbers = generateLemerNumbers(x0, a, c, m, n);

        String histogramPath = "./result/histogram.png";
        String chartPath = "./result/distributionFunction.png";
        String excelFilePath = "./result/output.xlsx";

        try {
            generateHistogram(randomNumbers, histogramPath, k);
            double chiSquare = calculateChiSquare(randomNumbers, k);
            System.out.println("X^2-criteria: " + chiSquare);
            double kcCriteria = calculateCriteriaKS(randomNumbers, chartPath);
            System.out.println("KS-criteria: " + kcCriteria);
            createExcelFileWithCharts(randomNumbers, histogramPath, chartPath, excelFilePath);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static long getValidInput(long minValue, long maxValue, Scanner scanner) {
        while (true) {
            try {
                long value = Long.parseLong(scanner.nextLine());
                if (value >= minValue && value <= maxValue) {
                    return value;
                }
            } catch (NumberFormatException ignored) {
                System.out.print("Input value from " + minValue + " to " + maxValue + ": ");
            }
        }
    }

    private static boolean isValidLemerParameters(long a, long c, long m) {
        if (greatestCommonDivisor(c, m) != 1) {
            System.out.println("с and m have to be coprime");
            return false;
        }

        long b = a - 1;
        List<Long> primeFactors = getPrimeFactors(m);
        for (long prime : primeFactors) {
            if (b % prime != 0) {
                System.out.println("b = a - 1 must be a multiple of " + prime + ", prime factor of m");
                return false;
            }
        }

        if (m % 4 == 0 && b % 4 != 0) {
            System.out.println("If m is a multiple of 4, then b = a - 1 has to be multiple of 4");
            return false;
        }

        return true;
    }

    private static long greatestCommonDivisor(long a, long b) {
        return BigInteger.valueOf(a).gcd(BigInteger.valueOf(b)).longValue();
    }

    private static List<Long> getPrimeFactors(long n) {
        List<Long> factors = new ArrayList<>();
        for (long i = 2; i <= Math.sqrt(n); i++) {
            while (n % i == 0) {
                factors.add(i);
                n /= i;
            }
        }
        if (n > 1) {
            factors.add(n);
        }
        return factors;
    }

    private static List<Double> generateLemerNumbers(long x0, long a, long c, long m, int n) {
        List<Double> numbers = new ArrayList<>();
        long xn = x0;

        for (int i = 0; i < n; i++) {
            xn = (a * xn + c) % m;
            double un = (double) xn / m;
            numbers.add(un);
        }

        return numbers;
    }
    private static List<Double> transformRandomNumbersToRange(List<Double> numbers, Long b1, Long b2) {
        return numbers.stream().map(number -> b1 + number * (b2 - b1)).collect(Collectors.toList());
    }

    private static void generateHistogram(List<Double> randomNumbers, String filePath, int k) throws IOException {
        HistogramDataset dataset = new HistogramDataset();
        double[] values = randomNumbers.stream().mapToDouble(Double::doubleValue).toArray();
        dataset.addSeries("Histogram", values, k);
        createHistogramChartImage(dataset, filePath);
    }

    private static void createHistogramChartImage(HistogramDataset dataset, String filePath) throws IOException {
        JFreeChart histogram = ChartFactory.createHistogram("Histogram", "Random value", "Frequency",
                dataset, PlotOrientation.VERTICAL, false, false, false);
        histogram.setBackgroundPaint(new ChartColor(0, 255, 255));
        histogram.setBorderVisible(true);
        histogram.setBorderPaint(new ChartColor(0, 139, 139));

        BufferedImage image = histogram.createBufferedImage(800, 600);
        ImageIO.write(image, "png", new File(filePath));
    }

    private static double calculateCriteriaKS(List<Double> randomNumbers, String filePath) throws IOException {
        Collections.sort(randomNumbers);

        int n = randomNumbers.size();
        double kPlus = 0;
        double kMinus = 0;

        XYSeries empiricalSeries = new XYSeries("Empirical distribution function");
        XYSeries theoreticalSeries = new XYSeries("Theoretical distribution function");

        for (int i = 0; i < n; i++) {
            double y = (double) i / n;
            double x = randomNumbers.get(i);
            empiricalSeries.add(x, y);
            theoreticalSeries.add(y, y);

            double kPlusCandidate = (double) (i + 1) / n - randomNumbers.get(i);
            double kMinusCandidate = randomNumbers.get(i) - y;

            kPlus = Math.max(kPlus, kPlusCandidate);
            kMinus = Math.max(kMinus, kMinusCandidate);
        }

        kPlus = Math.sqrt(n) * kPlus;
        kMinus = Math.sqrt(n) * kMinus;
        System.out.println("k-plus: " + kPlus + ", k-minus: " + kMinus);

        createFunctionalChartImage(empiricalSeries, theoreticalSeries, filePath);

        return Math.max(kPlus, kMinus);
    }

    private static void createFunctionalChartImage(XYSeries empiricalSeries, XYSeries theoreticalSeries, String filePath) throws IOException {
        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(empiricalSeries);
        dataset.addSeries(theoreticalSeries);

        JFreeChart chart = ChartFactory.createXYLineChart(
                "Distribution functions",
                "Random value",
                "F(x)",
                dataset,
                PlotOrientation.VERTICAL,
                true,
                true,
                false
        );
        chart.setBackgroundPaint(new ChartColor(0, 255, 255));
        chart.setBorderVisible(true);
        chart.setBorderPaint(new ChartColor(0, 139, 139));

        BufferedImage image = chart.createBufferedImage(800, 600);
        ImageIO.write(image, "png", new File(filePath));
    }

    private static void createExcelFileWithCharts(List<Double> randomNumbers, String histogramPath, String chartPath, String excelFilePath) throws IOException {
        Workbook workbook = new XSSFWorkbook();
        Sheet sheet = workbook.createSheet("Random numbers");

        for (int i = 0; i < randomNumbers.size(); i++) {
            Row row = sheet.createRow(i);
            Cell cell = row.createCell(0);
            cell.setCellValue(randomNumbers.get(i));
        }

        insertImageIntoSheet(workbook, sheet, histogramPath, 1, 3);
        insertImageIntoSheet(workbook, sheet, chartPath, 32, 3);

        try (FileOutputStream fileOut = new FileOutputStream(excelFilePath)) {
            workbook.write(fileOut);
        }
        workbook.close();
    }

    private static void insertImageIntoSheet(Workbook workbook, Sheet sheet, String imagePath, int row, int col) throws IOException {
        InputStream is = new FileInputStream(imagePath);
        byte[] bytes = IOUtils.toByteArray(is);
        int pictureIdx = workbook.addPicture(bytes, Workbook.PICTURE_TYPE_PNG);
        is.close();

        Drawing<?> drawing = sheet.createDrawingPatriarch();
        ClientAnchor anchor = workbook.getCreationHelper().createClientAnchor();
        anchor.setCol1(col);
        anchor.setRow1(row);

        Picture pict = drawing.createPicture(anchor, pictureIdx);
        pict.resize();
    }

    private static double calculateChiSquare(List<Double> numbers, int k) {
        int n = numbers.size();
        double expectedFrequency = n / (double) k;

        int[] observedFrequencies = new int[k];

        for (double number : numbers) {
            int intervalIndex = (int) (number * k);
            if (intervalIndex == k) intervalIndex--;
            observedFrequencies[intervalIndex]++;
        }

        double chiSquare = 0;
        for (int i = 0; i < k; i++) {
            double observed = observedFrequencies[i];
            chiSquare += Math.pow(observed - expectedFrequency, 2) / expectedFrequency;
        }

        return chiSquare;
    }
}
