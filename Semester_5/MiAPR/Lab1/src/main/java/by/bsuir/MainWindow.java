package by.bsuir;

import by.bsuir.algorithm.Centroid;
import by.bsuir.algorithm.K_means;

import javax.swing.*;
import java.util.ArrayList;

public class MainWindow extends JFrame {

    private final JButton btCalculate = new JButton("Calculate");
    private final JButton btGenerate = new JButton("Generate");
    private final JTextField tfClustersAmount = new JTextField();
    private final JTextField tfPointsAmount = new JTextField();
    private final JLabel lbPoints = new JLabel("Points");
    private final JLabel lbClusters = new JLabel("Clusters");
    private Panel panel = new Panel(new ArrayList<>(), new ArrayList<>());

    private void init() {
        btCalculate.setBounds(660, 690, 100, 50);
        btGenerate.setBounds(250, 690, 100, 50);
        tfClustersAmount.setBounds(130, 690, 100, 50);
        lbClusters.setBounds(130, 670, 100, 20);
        tfPointsAmount.setBounds(20, 690, 100, 50);
        lbPoints.setBounds(20, 670, 100, 20);
        panel.setBounds(10, 10, Constants.PANEL_WIDTH, Constants.PANEL_HEIGHT);
        panel.setBorder(BorderFactory.createLineBorder(Constants.DEFAULT_COLOR));

        btGenerate.addActionListener(e -> {
            panel.setPoints(PointRandomizerUtils.randomizedPoints(panel.getWidth(), panel.getHeight(),
                    Constants.POINTS_DIAMETER, Integer.parseInt(tfPointsAmount.getText())));
            panel.setCentroids(new ArrayList<>());
            PointRandomizerUtils.randomizedPoints(panel.getWidth(), panel.getHeight(), Constants.POINTS_DIAMETER, Integer.parseInt(tfClustersAmount.getText())).
                    forEach(p -> {
                        p.setColor(Constants.CENTROID_COLOR);
                        panel.getCentroids().add(new Centroid(p));
                    });
            panel.repaint();
        });

        btCalculate.addActionListener(e -> {
            K_means.k_means(panel.getCentroids(), panel.getPoints());
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
        add(tfClustersAmount);
        add(tfPointsAmount);
        add(lbClusters);
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
