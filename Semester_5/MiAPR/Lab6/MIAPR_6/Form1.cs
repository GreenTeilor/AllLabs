using System;
using System.Windows.Forms;

namespace MIAPR_6
{
    public partial class Form1 : Form
    {
        private double[,] distances;

        public Form1()
        {
            InitializeComponent();
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < '0' || e.KeyChar > '9') && e.KeyChar != 8 && e.KeyChar != '-')
                e.KeyChar = '\0';
        }

        private void button1_Click(object sender, EventArgs e)
        {
            distances = SetRandomGrid(int.Parse(textBox1.Text));

            var hierarchical = new HierarchicalGrouping(distances, int.Parse(textBox1.Text));

            hierarchical.FindGroups();
            hierarchical.Draw(chart1, radioBtnMaximum.Checked);
        }

        private double[,] SetRandomGrid(int size)
        {
            dataGridView.ColumnCount = size + 1;
            dataGridView.RowCount = size + 1;

            for (int i = 0; i < size; i++)
            {
                dataGridView[0, i + 1].Value = string.Format("x{0}", i + 1);
                dataGridView[i + 1, 0].Value = string.Format("x{0}", i + 1);
            }

            var result = new double[size, size];
            var rand = new Random();

            for (int i = 0; i < size; i++)
                result[i, i] = 0;
            for (int i = 1; i < size; i++)
                for (int j = 0; j < i; j++)
                {
                    result[i, j] = rand.Next(size + 5) + 1;
                    result[j, i] = result[i, j];
                }
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    dataGridView[i + 1, j + 1].Value = result[i, j];
            if (radioBtnMaximum.Checked)
            {
                for (int i = 1; i < int.Parse(textBox1.Text); i++)
                    for (int j = 0; j < i; j++)
                    {
                        result[i, j] = 1 / result[i,j];
                        result[j, i] = result[i, j];
                    }
            }

            return result;
        }
    }
}