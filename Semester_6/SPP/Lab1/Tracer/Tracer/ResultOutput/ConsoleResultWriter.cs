using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tracer
{
    public class ConsoleResultWriter : IResultWritable
    {
        public void WriteResult(string result)
        {
            Console.WriteLine(result);
        }
    }
}
