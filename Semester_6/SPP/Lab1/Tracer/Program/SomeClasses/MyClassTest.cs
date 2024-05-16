using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tracer;

namespace LibDemonstration.SomeClasses
{
    class MyClass
    {
        private ITracer _tracer;

        internal MyClass(ITracer tracer)
        {
            _tracer = tracer;
        }

        public void MethodA()
        {
            _tracer.StartTrace();

            //Код метода A(просто маленькое вычисление)
            int a = 5;
            a -= 2;

            MethodB();
            MethodC();

            _tracer.StopTrace();
        }

        private void MethodB()
        {
            _tracer.StartTrace();

            //Код метода B(пузырек)
            int[] arr = new int[5] { 3, 8, 1, -7, -2 };
            for (int i = 0; i < arr.Length - 1; i++)
            {
                for (int j = 0; j < arr.Length - i; ++j)
                {
                    if (arr[j] > arr[j + 1])
                    {
                        int temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                }
            }

            _tracer.StopTrace();
        }

        private void MethodC()
        {
            _tracer.StartTrace();

            //Код метода C(swap)
            int a = 3;
            int b = 5;
            int temp = a;
            a = b;
            b = temp;

            MethodD();
            _tracer.StopTrace();
        }

        private void MethodD()
        {
            _tracer.StartTrace();

            //Код метода D(формула Зеллера)
            int h = (26 + (13 * (3 + 1) / 5) + 2024 % 100 + (2024 % 100 / 4) + (2024 / 100 / 4) - 2 * (2024 / 100)) % 7;

            _tracer.StopTrace();
        }
    }
}
