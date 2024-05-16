namespace Faker.Generators;

public class DoubleGenerator : IGenerator
{
    public object Generate(Type type, RandomFaker context)
    {
        return (context.Random.NextDouble() - 0.5) * double.MaxValue;
    }

    public bool CanGenerate(Type type)
    {
        return type == typeof(double);
    }
}