namespace Faker;

public interface IGenerator
{
    object Generate(Type type, RandomFaker context);
    bool CanGenerate(Type type);
}