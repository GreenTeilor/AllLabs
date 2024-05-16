namespace Faker.Generators;

public class ByteGenerator : IGenerator
{
    public object Generate(Type type, RandomFaker context)
    {
        return (byte)context.Random.Next(byte.MinValue, byte.MaxValue);
    }

    public bool CanGenerate(Type type)
    {
        return type == typeof(byte);
    }
}
