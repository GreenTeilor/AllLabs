using System.Linq.Expressions;
using Faker;
using Faker.UserGenerators;

var fakerConfig = new CustomGenerators();
fakerConfig.Add<A, string, RiverGenerator>(a => a.River);
fakerConfig.Add<A, int, MarkGenerator>(a => a.Mark);

var faker = new Faker.Faker(fakerConfig);


var a = faker.Create<A>();

Console.WriteLine($"SetInConstructor: {a.SetInConstructor};\n" +
                  $"DecimalValue: {a.DecimalValue};\n" +
                  $"FieldWithoutSet: {a.FieldWithoutSet};\n" +
                  $"FieldWithPrivateSet: {a.FieldWithPrivateSet};\n" +
                  $"IntProperty: {a.IntProperty};\n" +
                  $"IntField: {a.IntField};\n" +
                  $"ShortValue: {a.ShortValue};\n" +
                  $"StringValue: {a.StringValue};\n" +
                  $"River: {a.River};\n" +
                  $"Mark: {a.Mark};\n");

