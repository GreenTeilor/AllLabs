using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestAssembly
{
    public class Foo
    {
        int internalPointerVariable;

        public double MyDouble { get; set; }

        public int MyMethod(int param)
        {
            return param;
        }
    }
}
