namespace Faker;

public interface IUserGenerator
{
    object Generate(Type type, RandomFaker context);
    bool CanGenerate(Type type);
}