namespace Faker.Generators;

public class DateTimeGenerator : IGenerator
{
    public readonly DateTime MinDate = new DateTime(1917, 2, 25);
    public readonly DateTime MaxDate = new DateTime(2050, 1, 19);
    public object Generate(Type type, RandomFaker context)
    {
        var maxTimeDelta = MaxDate.Subtract(MinDate);
        var timeDelta = maxTimeDelta.Multiply(context.Random.NextDouble());
        
        return MinDate.Add(timeDelta);
    }

    public bool CanGenerate(Type type)
    {
        return type == typeof(DateTime);
    }
}