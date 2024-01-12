using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Laba4
{
    public class Perceptron
    {
        public class PerceptronClass
        {
            public readonly List<PerceptronObject> objects = new List<PerceptronObject>();
        }

        public class PerceptronObject
        {
            public readonly List<int> attributes = new List<int>();
        }

        private const int C = 1;
        private const int RANDOM = 10;

        private int classesCount;
        private int objectsInClassCount;
        private int attributesCount;
        private List<PerceptronClass> classes = new List<PerceptronClass>();
        private List<PerceptronObject> weights = new List<PerceptronObject>();
        private List<PerceptronObject> decisionFunctions;

        public Perceptron(int classes, int objectsInclass, int attribute)
        {
            classesCount = classes;
            objectsInClassCount = objectsInclass;
            attributesCount = attribute;
        }

        //Create random classes and calculate decision functions
        public void Calculate()
        {
            CreateRandomClasses();
            CalculateDecisionFunctions();
        }

        //1 of 2 functions called in calculate(*classesCount, objectsInClassCount, attributesCount are already inputted by user)
        //*see button1_Click in Form1.cs
        private void CreateRandomClasses()
        {
            var rand = new Random();

            //We generate classes with objects and objects contain inputted amount of attributes
            for (int i = 0; i < classesCount; i++)
            {
                var currentClass = new PerceptronClass();

                for (int j = 0; j < objectsInClassCount; j++)
                {
                    var currentObject = new PerceptronObject();

                    for (int k = 0; k < attributesCount; k++)
                        currentObject.attributes.Add(rand.Next(RANDOM) - RANDOM / 2);

                    currentClass.objects.Add(currentObject);
                }
                classes.Add(currentClass);
            }

            //Init all weights with 0 and size of attributesCount + 1
            //Also init desions with 0 and size if classesCount
            foreach (PerceptronClass perceptronClass in classes)
            {
                var weigth = new PerceptronObject();

                //IMPORTANT: each weight vector will have size attributesCount + 1
                for (int i = 0; i <= attributesCount; i++)
                    weigth.attributes.Add(0);

                weights.Add(weigth);
               
            }

            //Add in the end of each object attributes list value - 1
            foreach (PerceptronClass perceptronClass in classes)
                foreach (PerceptronObject perceptronObject in perceptronClass.objects)
                    perceptronObject.attributes.Add(1);
        }

        //As result decision functions have all lists with all coefficients
        private void CalculateDecisionFunctions()
        {
            bool areWeightsChanged = true;
            int iteration = 0;
            const int MAX_ITERATIONS_COUNT = 10_000;

            while (areWeightsChanged && iteration < MAX_ITERATIONS_COUNT)
            {
                for (int i = 0; i < classes.Count; i++)
                {
                    PerceptronClass currentClass = classes[i];
                    PerceptronObject currentWeight = weights[i];

                    for (int j = 0; j < currentClass.objects.Count; j++)
                    {
                        PerceptronObject currentObject = currentClass.objects[j];

                        areWeightsChanged = CorrectWeigth(currentObject, currentWeight, i);
                    }
                }
                iteration++;
            }

            if (iteration == MAX_ITERATIONS_COUNT)
                MessageBox.Show("Превышено количество итераций при формировании решающих функций. " +
                    "Функции сформированы неправильно. Повторите процесс формирования обучающей выборки");

            decisionFunctions = weights;
        }

        private bool CorrectWeigth(PerceptronObject currentObject, 
            PerceptronObject currentWeight, int classNumber)
        {
            bool result = false;
            int objectDecision = ObjectMultiplication(currentWeight, currentObject);

            for (int i = 0; i < weights.Count; i++)
            {
                int currentDecision = ObjectMultiplication(weights[i], currentObject);

                if (i != classNumber) //To check if it's not compared to the same weight multiplication(otherwise inner if is always true)
                {
                    if (objectDecision <= currentDecision)
                    {
                        ChangeWeight(weights[i], currentObject, -1);

                        result = true;
                    }
                }
            }
            if (result)
                ChangeWeight(currentWeight, currentObject, 1);

            return result;
        }

        private int ObjectMultiplication(PerceptronObject weight, PerceptronObject obj)
        {
            int result = 0;

            for (int i = 0; i < weight.attributes.Count; i++)
                result += weight.attributes[i]*obj.attributes[i];

            return result;
        }

        private void ChangeWeight(PerceptronObject weight, PerceptronObject perceptronObject, int sign)
        {
            for (int i = 0; i < weight.attributes.Count; i++)
                weight.attributes[i] += C*sign * perceptronObject.attributes[i];
        }

        public void FillListBox(ListBox listBoxClasses, ListBox listBoxFunc)
        {
            int indexCurrentClass = 1;

            listBoxClasses.Items.Clear();
            listBoxFunc.Items.Clear();

            foreach (PerceptronClass currClass in classes)
            {
                int indexCurrentObject = 1;

                listBoxClasses.Items.Add(String.Format("Класс {0}:", indexCurrentClass));
                foreach (PerceptronObject currentObject in currClass.objects)
                {
                    string str = String.Format("    Образ {0}: (", indexCurrentObject);

                    for (int j = 0; j < currentObject.attributes.Count - 1; j++)
                    {
                        int attribute = currentObject.attributes[j];
                        str += attribute + ",";
                    }
                    str = str.Remove(str.Length - 1, 1);
                    str += ")";
                    listBoxClasses.Items.Add(str);
                    indexCurrentObject++;
                }
                listBoxClasses.Items.Add("");
                indexCurrentClass++;
            }

            listBoxFunc.Items.Add("Решающие функции: ");
            for (int i = 0; i < decisionFunctions.Count; i++)
            {
                string str = String.Format("d{0}(x) = ", i + 1);

                for (int j = 0; j < decisionFunctions[i].attributes.Count; j++)
                {
                    int attribute = decisionFunctions[i].attributes[j];

                    if (j < decisionFunctions[i].attributes.Count - 1)
                        if (attribute >= 0 && j != 0)
                            str += "+" + attribute + String.Format("*x{0}", j + 1);
                        else
                            str += attribute + String.Format("*x{0}", j + 1);
                    else
                        if (attribute >= 0 && j != 0)
                            str += "+" + attribute;
                        else
                            str += attribute;
                }
                listBoxFunc.Items.Add(str);
            }
        }

        public int FindClass(PerceptronObject perceptronObject)
        {
            int resultClass = 0;
            int decisionMax;

            perceptronObject.attributes.Add(1);
            decisionMax = ObjectMultiplication(decisionFunctions[0], perceptronObject);

            for (int i = 1; i < decisionFunctions.Count; i++)
            {
                PerceptronObject weight = decisionFunctions[i];

                if (ObjectMultiplication(weight, perceptronObject) > decisionMax)
                {
                    decisionMax = ObjectMultiplication(weight, perceptronObject);
                    resultClass = i;
                }
            }

            return (resultClass + 1);
        }
    }
}