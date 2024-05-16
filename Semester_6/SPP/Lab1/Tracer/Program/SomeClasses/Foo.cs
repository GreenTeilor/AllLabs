using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tracer;

namespace LibDemonstration.SomeClasses
{
    public class Foo
    {
        private readonly Bar _bar;
        private readonly ITracer _tracer;

        internal Foo(ITracer tracer)
        {
            _tracer = tracer;
            _bar = new Bar(_tracer);
        }

        public void MyMethod()
        {
            _tracer.StartTrace();
            Thread.Sleep(150);
            _bar.InnerMethod();

            _tracer.StopTrace();
        }

        public void MySecondMethod()
        {
            _tracer.StartTrace();
            Thread.Sleep(200);
            _bar.InnerMethod();

            _tracer.StopTrace();
        }
    }
}
