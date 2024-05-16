namespace Faker.Generators;

public class ULongGenerator : IGenerator
{
    public object Generate(Type type, RandomFaker context)
    {
        return (ulong)context.Random.NextInt64();
    }

    public bool CanGenerate(Type type)
    {
        return type == typeof(ulong);
    }
}