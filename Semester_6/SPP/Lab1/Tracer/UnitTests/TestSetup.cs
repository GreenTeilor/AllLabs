using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tracer;

namespace UnitTests
{
    public class TestSetup
    {
        public TraceResultStruct _traceResultStruct { get; }

        public TestSetup()
        {
            ITracer tracer = new Tracer.Tracer(1);
            TestClasses.Class1 First = new TestClasses.Class1(tracer);
            TestClasses.Class2 Second = new TestClasses.Class2(tracer);

            First.Method0();
            Second.Method1();

            _traceResultStruct = tracer.GetTraceResult();
        }
    }
}
