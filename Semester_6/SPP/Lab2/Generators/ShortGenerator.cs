namespace Generators;

public class ShortGenerator
{
    private static object Generate(Type type)
    {
        var random = new Random();
        return (short)random.Next(short.MinValue, short.MaxValue);
    }

    private static bool CanGenerate(Type type)
    {
        return type == typeof(short);
    }
}
