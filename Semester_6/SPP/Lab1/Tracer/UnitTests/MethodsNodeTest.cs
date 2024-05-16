using Moq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using Tracer;
using Xunit;

namespace UnitTests
{
    public class MethodsNodeTest
    {
        [Fact]
        public void GetCallingMethodNameAndClassNameReturnsCorrectValues()
        {
            // Arrange
            MethodNode methodNode = new MethodNode();
            Type methodNodeType = methodNode.GetType();
            MethodInfo getCallingMethodNameAndClassNameMethod = methodNodeType.GetMethod("GetCallingMethodNameAndClassName", BindingFlags.NonPublic | BindingFlags.Instance);

            // Act
            (string methodName, string className) = ((ValueTuple<string, string>)getCallingMethodNameAndClassNameMethod.Invoke(methodNode, null));

            // Assert
            Assert.Equal("InvokeWithNoArgs", methodName);
            Assert.Equal("MethodBaseInvoker", className);
        }

    }
}
