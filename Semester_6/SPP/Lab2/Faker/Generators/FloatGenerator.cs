namespace Faker.Generators;

public class FloatGenerator : IGenerator
{
    public object Generate(Type type, RandomFaker context)
    {
        return (float)((context.Random.NextSingle() - 0.5) * float.MaxValue);
    }

    public bool CanGenerate(Type type)
    {
        return type == typeof(float);
    }
}