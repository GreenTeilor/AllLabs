using System;
using System.Windows.Forms;

namespace Laba4
{
    public partial class Form1 : Form
    {
        private Perceptron perceptron;

        public Form1()
        {
            InitializeComponent();
        }

        private void textBox_Classes_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < '0' || e.KeyChar > '9') && e.KeyChar != 8)
                e.KeyChar = '\0';
        }

        private void button1_Click(object sender, EventArgs e)
        {
            listBox.Items.Clear();
            //Here inputted fields appear in instance of working class
            perceptron = new Perceptron(int.Parse(textBox_Classes.Text),
                int.Parse(textBox_Objects.Text), int.Parse(textBox_Attributes.Text));
            perceptron.Calculate();
            perceptron.FillListBox(listBox, listBoxFunctions);

            dataGridView1.RowCount = 1;
            dataGridView1.ColumnCount = int.Parse(textBox_Attributes.Text);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            var testObject = new Perceptron.PerceptronObject();
            int[] numbers = new int[dataGridView1.ColumnCount];

            try
            {
                for (int i = 0; i < dataGridView1.ColumnCount; i++)
                {
                    numbers[i] = int.Parse(dataGridView1.Rows[0].Cells[i].Value.ToString());
                    testObject.attributes.Add(numbers[i]);
                }
                MessageBox.Show(String.Format("Объект относится к {0} классу", 
                    perceptron.FindClass(testObject)));
            }
            catch (Exception)
            {
                MessageBox.Show("Ошибка ввода тестового образа");
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }
    }
}