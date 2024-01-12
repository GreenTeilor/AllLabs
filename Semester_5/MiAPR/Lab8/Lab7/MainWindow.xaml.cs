using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Syntax;
using Line = Syntax.Line;

namespace Lab7
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private const int widthDelta = 137;
        private const int heightDelta = 92;

        public MainWindow()
        {
            InitializeComponent();    
        }

        private Point startPoint;

        private bool isDrawingModeEnabled = false;

        private GeometryGroup currentGroup;

        private List<Element> drawedElements = new List<Element>();

        private Grammar grammar = null;
        

        private void SynthesisButton_Click(object sender, RoutedEventArgs e)
        {
            Element home = grammar.GetImage();
            Clear();
            foreach (Line line in home.Lines)
            {
                drawedElements.Add(TerminalElementCreater.GetTerminalElement(line));
            }
            home.ScaleTransform((WindowGrid.ActualWidth - widthDelta)/home.Length,
                (WindowGrid.ActualHeight - heightDelta)/home.Height);
            currentGroup =  home.GetGeometryGroup();
            UpdateImage();
        }

        private void Image_MouseUp(object sender, MouseButtonEventArgs e)
        {
            if (isDrawingModeEnabled)
            {
                isDrawingModeEnabled = false;
                drawedElements.Add(TerminalElementCreater.GetTerminalElement(new Line(GetCortanianCoordinates(startPoint), GetCortanianCoordinates(e.GetPosition(Image)))));
                currentGroup.Children.Add(new LineGeometry(startPoint,  e.GetPosition(Image)));
                UpdateImage();
            }
            else
            {
                isDrawingModeEnabled = true;
                startPoint = e.GetPosition(Image);
            }
        }

        private void UpdateImage()
        {
            Image.Source =
                new DrawingImage(new GeometryDrawing(new SolidColorBrush(Colors.Black),
                    new Pen(new SolidColorBrush(Colors.Black), 1.0), currentGroup));
        }

        private Point GetCortanianCoordinates(Point position)
        {
            return new Point(position.X, WindowGrid.ActualHeight - 20 - position.Y);
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            ClearImage();
        }

        private void ClearImage()
        {
            currentGroup = new GeometryGroup();
            currentGroup.Children.Add(new LineGeometry(new Point(0, 0),
                new Point(0, WindowGrid.ActualHeight - heightDelta)));
            currentGroup.Children.Add(new LineGeometry(new Point(0, WindowGrid.ActualHeight - heightDelta),
                new Point(WindowGrid.ActualWidth - widthDelta, WindowGrid.ActualHeight - heightDelta)));
            currentGroup.Children.Add(
                new LineGeometry(new Point(WindowGrid.ActualWidth - widthDelta, WindowGrid.ActualHeight - heightDelta),
                    new Point(WindowGrid.ActualWidth - widthDelta, 0)));
            currentGroup.Children.Add(new LineGeometry(new Point(WindowGrid.ActualWidth - widthDelta, 0),
                new Point(0, 0)));
            UpdateImage();
        }

        private void RecognitionButton_Click(object sender, RoutedEventArgs e)
        {
            RecognazingResult recognazingResult = grammar.IsImage(drawedElements);
            if (recognazingResult.IsHome)
            {
                MessageBox.Show("Рисунок соответствует грамматике");
            }
            else
            {
                MessageBox.Show(string.Format("Рисунок НЕ соответствует грамматике. Не найден элемент: {0}", recognazingResult.ErrorElementName));
            }
        }

        private void ClearButton_Click(object sender, RoutedEventArgs e)
        {
            Clear();
        }

        private void Clear()
        {
            currentGroup = new GeometryGroup();
            ClearImage();
            drawedElements = new List<Element>();
        }

        private void GenerateButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                GrammarSyntax grammarSyntax = new GrammarSyntax(drawedElements);
                grammar = grammarSyntax.Grammar;
                GrammarLabel.Content = string.Format("Грамматика: {0}", grammar);
                SynthesisButton.IsEnabled = true;
                RecognitionButton.IsEnabled = true;
            }
            catch (InvalidElementException ex)
            {
                MessageBox.Show("Отсутствует рисунок.");
            }
        }
    }
}
