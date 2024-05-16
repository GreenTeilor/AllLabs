namespace Faker.Generators;

public class LongGenerator : IGenerator
{
    public object Generate(Type type, RandomFaker context)
    {
        return context.Random.NextInt64(long.MinValue, long.MaxValue);
    }

    public bool CanGenerate(Type type)
    {
        return type == typeof(long);
    }
}
