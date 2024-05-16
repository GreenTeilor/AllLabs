using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tracer.ResultOutput;
using Xunit;

namespace UnitTests
{
    public class FileWriterTest
    {
        [Fact]
        public void WriteResultShouldWriteResultToFile()
        {
            // Arrange
            string filePath = "testFile.txt";
            string result = "Test result";

            var fileResultWriter = new FileResultWriter(filePath);

            // Act
            fileResultWriter.WriteResult(result);

            // Assert
            Assert.True(File.Exists(filePath));
            string fileContent = File.ReadAllText(filePath);
            Assert.Equal(result, fileContent);

            // Clean up
            File.Delete(filePath);
        }
    }
}
