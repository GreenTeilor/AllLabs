namespace Program;

using System.Collections.Concurrent;
using System.Data;
using System.Threading.Tasks.Dataflow;
using Generator;

class Program
{
    //Set up paths to classes for which we want to generate tests
    public static void Main()
    {
        var basePath = AppDomain.CurrentDomain.BaseDirectory;
        basePath = Directory.GetParent(basePath)!.FullName;
        basePath = Directory.GetParent(basePath)!.FullName;
        basePath = Directory.GetParent(basePath)!.FullName;
        basePath = Directory.GetParent(basePath)!.FullName;
        var filePath = Path.Combine(basePath, "MyClass.cs");
        var pathes = new string[] { filePath };
        generateTestClasses(pathes, 4, 4, 4);
    }

    static void generateTestClasses(string[] pathes, int parallel1, int parallel2, int parallel3)
    {
        var generator = new Generator();
        var bufferBlock = new BufferBlock<string>();

        //Max parallelism for reader block
        var readerOptions = new ExecutionDataflowBlockOptions
        {
            MaxDegreeOfParallelism = parallel1,
        };
        var readerBlock = new TransformBlock<string, string>(read, readerOptions);

        //Max parallelism for generator block
        var generatorOptions = new ExecutionDataflowBlockOptions
        {
            MaxDegreeOfParallelism = parallel2,
        };
        var generatorBlock = new TransformBlock<string, ConcurrentDictionary<string, string>>(generator.getNamesAndContents, generatorOptions);

        //Max parallelism for write block
        var writerOptions = new ExecutionDataflowBlockOptions
        {
            MaxDegreeOfParallelism = parallel3,
        };
        var writer = new ActionBlock<ConcurrentDictionary<string, string>>(write, writerOptions);

        //Create chain of blocks to transfer data(
        // 1-st - buffer block
        // 2-nd - read block
        // 3-rd - generator block
        // 4-th - write block
        //)
        bufferBlock.LinkTo(readerBlock);
        readerBlock.LinkTo(generatorBlock);
        generatorBlock.LinkTo(writer);

        //Create chain of blocks in order they executed(
        // 1-st - buffer block
        // 2-nd - read block
        // 3-rd - generator block
        // 4-th - write block
        //)
        bufferBlock.Completion.ContinueWith(task => readerBlock.Complete());
        readerBlock.Completion.ContinueWith(task => generatorBlock.Complete());
        generatorBlock.Completion.ContinueWith(task => writer.Complete());

        //Put all paths in data block(buffer block)
        foreach (var path in pathes)
        {
            bufferBlock.Post(path);
        }

        //At this point all data(paths) is in buffer block so we are ready to start blocks chain execution
        bufferBlock.Complete();

        //Writer block is last and we wait till the end of it's execution
        writer.Completion.Wait();
    }

    //To read all text from file
    static async Task<string> read(string path)
    {
        return await File.ReadAllTextAsync(path);
    }

    //Write generated tests in file
    static async Task write(ConcurrentDictionary<string, string> map)
    {
        var basePath = AppDomain.CurrentDomain.BaseDirectory;
        basePath = Directory.GetParent(basePath)!.FullName;
        basePath = Directory.GetParent(basePath)!.FullName;
        basePath = Directory.GetParent(basePath)!.FullName;
        basePath = Directory.GetParent(basePath)!.FullName;
        basePath = Path.Combine(basePath, "result");

        foreach (var entry in map)
        {
            var fileName = entry.Key;
            var fileContent = entry.Value;

            var copyNumber = 1;

            var filePath = Path.Combine(basePath, $"{fileName}.cs");

            while (File.Exists(filePath))
            {
                filePath = Path.Combine(basePath, $"{fileName} [{copyNumber++}].cs");
            }
            var file = File.Create(filePath);
            var stream = new StreamWriter(file);
            await stream.WriteLineAsync(fileContent);
            await stream.FlushAsync();
            stream.Close();
        }
    }
}