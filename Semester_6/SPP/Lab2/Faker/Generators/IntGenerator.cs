namespace Faker.Generators;

public class IntGenerator : IGenerator
{
    public object Generate(Type type, RandomFaker context)
    {
        return context.Random.Next(int.MinValue, int.MaxValue);
    }

    public bool CanGenerate(Type type)
    {
        return type == typeof(int);
    }
}