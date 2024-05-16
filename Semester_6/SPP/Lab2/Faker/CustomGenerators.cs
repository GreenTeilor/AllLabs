using System.Linq.Expressions;

namespace Faker;

public class CustomGenerators
{
    //Map for custom generators of different types
    private readonly Dictionary<Type, Dictionary<string, IUserGenerator>> _generators;

    public CustomGenerators()
    {
        _generators = new Dictionary<Type, Dictionary<string, IUserGenerator>>();
    }

    //Add generator for certain field of certain class
    //TTypeName - type of class, TFieldType - field type, TGenerator - generator type
    //getField - lambda expression to return field of class TTypeName
    public void Add<TTypeName, TFieldType, TGenerator>(Expression<Func<TTypeName, TFieldType>> getField)
    {
        //If there is no custom generators for fields of this class yet
        if (!_generators.ContainsKey(typeof(TTypeName)))
        {
            _generators.Add(typeof(TTypeName), new Dictionary<string, IUserGenerator>());
        }
        //Get field and it's name
        var member = getField.Body as MemberExpression ?? throw new ArgumentException("Invalid expression");
        var fieldName = member.Member.Name;
        //Create generator
        var generator = (IUserGenerator)Activator.CreateInstance(typeof(TGenerator));
        //Add generator for field of class TTypeName with and name
        _generators[typeof(TTypeName)].Add(fieldName, generator);
    }
    //Check if exists generator for field with certain name of class
    public bool HasGenerator(Type type, string fieldName)
    {
        return _generators.ContainsKey(type) && _generators[type].ContainsKey(fieldName);
    }

    public IUserGenerator GetGenerator(Type type, string fieldName)
    {
        return HasGenerator(type, fieldName) ? _generators[type][fieldName] : null;
    }
    
}