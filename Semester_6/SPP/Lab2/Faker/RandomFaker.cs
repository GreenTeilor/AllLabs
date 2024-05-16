namespace Faker;

public class RandomFaker
{
    public Random Random { get; }
    public Faker Faker { get; }

    public RandomFaker(Faker faker, Random random)
    {
        Random = random;
        Faker = faker;
    }
}