namespace Faker.Generators;

public class CharGenerator : IGenerator
{
    public object Generate(Type type, RandomFaker context)
    {
        return (char)context.Random.Next(); ;
    }

    public bool CanGenerate(Type type)
    {
        return type == typeof(char);
    }
}

