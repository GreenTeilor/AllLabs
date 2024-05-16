namespace Faker.UserGenerators;

public class MarkGenerator : IUserGenerator
{
    public object Generate(Type type, RandomFaker context)
    {
        var mark = context.Random.Next(1, 11);

        return mark;
    }

    public bool CanGenerate(Type type)
    {
        return type == typeof(int);
    }
}