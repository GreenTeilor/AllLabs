using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Tracer.ResultOutput
{
    public class FileResultWriter: IResultWritable
    {
        private string _filePath;

        public FileResultWriter(string filePath)
        {
            _filePath = filePath;
        }

        public void WriteResult(string result)
        {
            File.WriteAllText(_filePath, result);
        }
    }
}
