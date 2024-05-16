using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestAssembly.Extension
{
    public static class ExtensionClass
    {
        public static int ExtensionMethod(this Foo myClass, int param)
        {
            return param;
        }
    }
}