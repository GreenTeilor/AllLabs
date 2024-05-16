using System.Collections;

namespace Faker.Generators;

public class IEnumerableGenerator : IGenerator
{
    private const int MinLength = 1;
    private const int MaxLength = 5;
    
    public object Generate(Type type, RandomFaker context)
    {
        var length = context.Random.Next(MinLength, MaxLength);

        var generics = type.GenericTypeArguments;
        var returnListType = typeof(List<>).MakeGenericType(generics);
        var returnList = (IList)Activator.CreateInstance(returnListType);
        
        for (var i = 0; i < length; i++)
        {
            returnList.Add(context.Faker.Create(generics[0]));
        }
        
        return returnList;
    }

    public bool CanGenerate(Type type)
    {
        return type.IsGenericType && type.GetGenericTypeDefinition() == typeof(IEnumerable<>);
    }
    
}