using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tracer;

namespace UnitTests.TestClasses
{
    internal class Class2
    {
        private readonly ITracer _tracer;

        internal Class2(ITracer tracer)
        {
            _tracer = tracer;
        }

        internal void Method1()
        {
            _tracer.StartTrace();
            Thread.Sleep(100);
            _tracer.StopTrace();
        }
    }
}
