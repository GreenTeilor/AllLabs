namespace Faker.Generators;

public class StringGenerator : IGenerator
{
    private const int MinLength = 1;
    private const int MaxLength = 20;
    
    private const string EnableChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    public object Generate(Type type, RandomFaker context)
    {
        var length = context.Random.Next(MinLength, MaxLength + 1);

        Span<char> buffer = stackalloc char[length];

        for (var i = 0; i < length; i++)
        {
            buffer[i] = EnableChars[context.Random.Next(0, EnableChars.Length)];
        }
        
        return buffer.ToString();
    }

    public bool CanGenerate(Type type)
    {
        return type == typeof(string);
    }
}