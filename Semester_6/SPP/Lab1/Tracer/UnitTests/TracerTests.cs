using Moq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tracer;
using Xunit;

namespace UnitTests
{
    public class TracerTests:IClassFixture<TestSetup>
    {
        private readonly TestSetup _traceResult;

        public TracerTests(TestSetup traceResult)
        {
            _traceResult = traceResult;
        }

        [Fact]
        public void StartTrace_StopTrace_RecordsExecutionTime()
        {
            // Arrange
            Tracer.Tracer methodTracer = new Tracer.Tracer(1);

            // Act
            methodTracer.StartTrace();
            int j = 0;
            for (int i = 0; i < 1000; i++) { j++; }
            methodTracer.StopTrace();

            // Assert
            // Check if the execution time is recorded correctly
            TraceResultStruct traceResult = methodTracer.GetTraceResult();
            Assert.True(traceResult.Methods[0].GetMethodStruct.Time > 0);
        }

        [Fact]
        public void GetTraceResult_ReturnsCorrectTotalTime()
        {
            // Arrange
            Tracer.Tracer tracer = new Tracer.Tracer(1);

            // Act
            tracer.StartTrace();
            int j = 0;
            for (int i = 0; i < 1000; i++) { j++; }
            tracer.StopTrace();
            TraceResultStruct traceResult = tracer.GetTraceResult();

            // Assert
            // Check if the total time is calculated correctly
            Assert.Equal(traceResult.Methods[0].GetMethodStruct.Time, traceResult.Time);
        }

        [Fact]
        public void GetTraceResult_FirstNestingLevel_ReturnsSameName()
        {
            string className1 = _traceResult._traceResultStruct.Methods[0].GetMethodStruct.ClassName;
            string name1 = _traceResult._traceResultStruct.Methods[0].GetMethodStruct.Name;
            string className2 = _traceResult._traceResultStruct.Methods[1].GetMethodStruct.ClassName;
            string name2 = _traceResult._traceResultStruct.Methods[1].GetMethodStruct.Name;

            Assert.Equal("Class1", className1);
            Assert.Equal("Method0", name1);
            Assert.Equal("Class2", className2);
            Assert.Equal("Method1", name2);
        }

        [Fact]
        public void GetTraceResult_SecondNestingLevel_ReturnsSameName()
        {
            string className1 = _traceResult._traceResultStruct.Methods[0].GetMethodStruct.internalMethodStructs[0].GetMethodStruct.ClassName;
            string name1 = _traceResult._traceResultStruct.Methods[0].GetMethodStruct.internalMethodStructs[0].GetMethodStruct.Name;
            string className2 = _traceResult._traceResultStruct.Methods[1].GetMethodStruct.ClassName;
            string name2 = _traceResult._traceResultStruct.Methods[1].GetMethodStruct.Name;

            Assert.Equal("Class1", className1);
            Assert.Equal("Method1", name1);
            Assert.Equal("Class2", className2);
            Assert.Equal("Method1", name2);
        }

        [Fact]
        public void GetTraceResult_ThirdNestingLevel_ReturnsSameName()
        {
            string className = _traceResult._traceResultStruct.Methods[0].GetMethodStruct.internalMethodStructs[0].GetMethodStruct.internalMethodStructs[0].GetMethodStruct.ClassName;
            string name = _traceResult._traceResultStruct.Methods[0].GetMethodStruct.internalMethodStructs[0].GetMethodStruct.internalMethodStructs[0].GetMethodStruct.Name;

            Assert.Equal("Class1", className);
            Assert.Equal("Method2", name);
        }
    }
}
