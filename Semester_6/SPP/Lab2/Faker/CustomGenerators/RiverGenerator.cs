namespace Faker.UserGenerators;

public class RiverGenerator : IUserGenerator
{
    private readonly string[] _rivers = { "Ob", "Enisey", "Pripyat", "Dnepr", "Berezina" };

    public object Generate(Type type, RandomFaker context)
    {
        var riverId = context.Random.Next(0, _rivers.Length);

        return _rivers[riverId];
    }

    public bool CanGenerate(Type type)
    {
        return type == typeof(string);
    }
}