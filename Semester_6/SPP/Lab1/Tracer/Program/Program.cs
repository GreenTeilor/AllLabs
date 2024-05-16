using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using LibDemonstration.SomeClasses;
using Tracer;


namespace LibDemonstration
{
    class Program
    {
        static private Tracer.Tracer _tracer0; // Tracer0 для потока, работающего в Main
        static private Tracer.Tracer _tracer1; // Tracer1/2 для двух вложенных потоков
        static private Tracer.Tracer _tracer2;

        static void Main()
        {
            _tracer0 = new Tracer.Tracer(Thread.CurrentThread.ManagedThreadId);

            Thread thread1 = new Thread(Thread1); // Tracer's для вложенных потоков инициализируются в Thread1/Thread2
            Thread thread2 = new Thread(Thread2);

            thread1.Start();
            thread2.Start();

            Foo foo = new Foo(_tracer0);
            foo.MyMethod();

            thread1.Join(); // Главный поток ожидает два других
            thread2.Join();

            _tracer2.GetTraceResult(); // Результаты Tracer: TraceResultStruct всех потоков объединяются в общую map 
            _tracer1.GetTraceResult();
            _tracer0.GetTraceResult();
            // Результаты из общей Map записываются в файлы json и XML
            _tracer1.GetMultiThreadResult("..//..//..//Result.json", "..//..//..//Result.xml");
        }

        static public void Thread1()
        {
            _tracer1 = new Tracer.Tracer(Thread.CurrentThread.ManagedThreadId);
            Foo foo = new Foo(_tracer1);

            foo.MyMethod();
            foo.MySecondMethod();
        }
        static public void Thread2()
        {
            _tracer2 = new Tracer.Tracer(Thread.CurrentThread.ManagedThreadId);
            Foo foo = new Foo(_tracer2);
            Bar bar = new Bar(_tracer2);

            foo.MyMethod();
            bar.InnerMethod();
        }

    }
}
