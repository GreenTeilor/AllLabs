package by.bsuir;

import by.bsuir.algorithm.Cluster;
import by.bsuir.algorithm.MaxMin;

import javax.swing.*;
import java.util.ArrayList;
import java.util.List;

public class MainWindow extends JFrame {

    private List<Cluster> clusters;

    private final JButton btCalculate = new JButton("Calculate");
    private final JButton btGenerate = new JButton("Generate");
    private final JButton btIterate = new JButton("Iterate");
    private final JButton btK_means = new JButton("k_means");
    private final JTextField tfPointsAmount = new JTextField();
    private final JLabel lbPoints = new JLabel("Points");
    private Panel panel = new Panel(new ArrayList<>(), new ArrayList<>());

    private void init() {
        btCalculate.setBounds(660, 690, 100, 50);
        btGenerate.setBounds(130, 690, 100, 50);
        btIterate.setBounds(240, 690, 100, 50);
        btIterate.setVisible(false);
        btK_means.setBounds(350, 690, 100, 50);
        btK_means.setVisible(false);
        tfPointsAmount.setBounds(20, 690, 100, 50);
        lbPoints.setBounds(20, 670, 100, 20);
        panel.setBounds(10, 10, Constants.PANEL_WIDTH, Constants.PANEL_HEIGHT);
        panel.setBorder(BorderFactory.createLineBorder(Constants.DEFAULT_COLOR));

        btGenerate.addActionListener(e -> {
            panel.setPoints(PointRandomizerUtils.randomizedPoints(panel.getWidth(), panel.getHeight(),
                    Constants.POINTS_DIAMETER, Integer.parseInt(tfPointsAmount.getText())));
            panel.setCentroids(new ArrayList<>());
            panel.repaint();
        });

        btCalculate.addActionListener(e -> {
            btIterate.setVisible(true);
            btK_means.setVisible(false);
            clusters = MaxMin.generate(panel.getPoints());
            panel.setCentroids(clusters.stream().map(Cluster::getCentroid).toList());
            panel.repaint();
        });

        btIterate.addActionListener(e -> {
            panel.setCentroids(MaxMin.maxMin(panel.getPoints(), clusters, btIterate, btK_means).stream().map(Cluster::getCentroid).toList());
            panel.repaint();
        });

        btK_means.addActionListener(e -> {
            MaxMin.k_means(panel.getCentroids(), panel.getPoints());
            panel.repaint();
        });
    }

    MainWindow() {
        super("k middle");
        setBounds(0, 0, 800, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(null);

        init();

        add(btCalculate);
        add(btGenerate);
        add(btIterate);
        add(btK_means);
        add(tfPointsAmount);
        add(lbPoints);
        add(panel);
    }

    public Panel getPanel() {
        return panel;
    }

    public void setPanel(Panel panel) {
        this.panel = panel;
    }
}
