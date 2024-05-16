namespace Generators;

public class BoolGenerator
{
    private static object Generate(Type type)
    {
        var random = new Random();
        return random.Next(0, 2) == 0;
    }

    private static bool CanGenerate(Type type)
    {
        return type == typeof(bool);
    }
}

