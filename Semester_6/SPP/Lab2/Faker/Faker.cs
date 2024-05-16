using System.Globalization;
using System.Reflection;

namespace Faker
{
    public class Faker
    {    
        private readonly CustomGenerators _customGenerators;

        //To resolve cyclic dependencies
        private readonly List<Type> _generatedTypes;

        private readonly RandomFaker _randomFaker;

        private const string ModuleName = "Generators";
        private readonly string[] _generatorsFromModuleNames = { "Generators.BoolGenerator", "Generators.ShortGenerator" };

        private IEnumerable<IGenerator> _defaultGenerators;

        public Faker(CustomGenerators customGenerators)
        {
            _customGenerators = customGenerators;

            //Get all default(not custom) generators
            GetGenerators();

            _randomFaker = new RandomFaker(this, new Random());
            _generatedTypes = new List<Type>();
        }
        
        public Faker() : this(new CustomGenerators())
        { }
        
        public T Create<T>()
        {
            return (T) Create(typeof(T));
        }

        //Accept type of object or field to create
        public object Create(Type t)
        {
            object newObject;
            
            try
            {
                newObject = GenerateWithModule(t);
            }
            catch (Exception)
            {
                newObject = null;
            }
            //Get first appropriate default generator for passed type
            newObject ??= _defaultGenerators.Where(g => g.CanGenerate(t)).
                    Select(g => g.Generate(t, _randomFaker)).FirstOrDefault();

            //Check if type is dto and wasn't generated yet(to resolve cyclic dependencies)
            if (newObject is null && IsDto(t) && !IsGenerated(t))
            {
                //Add type to _generatedTypes to avoid creating instance twice and, thus, resolve cyclic dependencies
                _generatedTypes.Add(t);

                //Create object and set it's fields
                newObject = FillClass(t);

                _generatedTypes.Remove(t);
            }

            return newObject ?? GetDefaultValue(t);
        }

        private void GetGenerators()
        {
            //Get all types and select that implement the IGenerator
            _defaultGenerators = Assembly.GetExecutingAssembly().GetTypes()
                .Where(t => t.GetInterfaces().Contains(typeof(IGenerator)))
                .Select(t => (IGenerator)Activator.CreateInstance(t));
        }

        private object GenerateWithModule(Type t)
        {
            object result = null;

            //Load module
            var assembly = Assembly.LoadFrom(ModuleName);

            //All generators in module
            foreach (var generatorName in _generatorsFromModuleNames)
            {
                //Get generator type
                var genType = assembly.GetType(generatorName);

                //Get method CanGenerate of generator
                var methodInfoCanGenerate = genType?.GetMethod("CanGenerate",  BindingFlags.NonPublic | BindingFlags.Static);

                //Cast to object as invoke method accept it
                var param = new object[] { t };

                //Call CanGenerate to check if it's possible for generator to generate value of passed type
                if (methodInfoCanGenerate is not null && (bool?)methodInfoCanGenerate.Invoke(null, param) == true)
                {
                    //Generate value
                    var methodInfoGenerate = genType.GetMethod("Generate",  BindingFlags.NonPublic | BindingFlags.Static);
                    result = methodInfoGenerate?.Invoke(null, param);
                }
            }

            return result;
        }
        
        //Default value for type(null for references)
        private object GetDefaultValue(Type t)
        {
            return t.IsValueType ? Activator.CreateInstance(t) : null;
        }
        
        private object FillClass(Type t)
        {
            //Create object and set fields, which values passed as parameters in constructor
            var newObject = CreateClass(t);

            //Set properties(have public setter) using default and custom generators
            FillProperties(newObject, t);
            FillPropertiesWithCustomGenerators(newObject, t);

            //Set public fields(don't have public setter) using default and custom generators
            FillFields(newObject, t);
            FillFieldsWithCustomGenerators(newObject, t);

            return newObject;
        }

        //Get constructor of type
        private ConstructorInfo GetConstructorForInvoke(Type t)
        {
            //Get all appropriate constructors
            var constructorsInfo = t.GetConstructors(BindingFlags.DeclaredOnly |
                                                     BindingFlags.Instance | BindingFlags.Public |
                                                     BindingFlags.NonPublic);
            
            //Get constructor with the largest number of arguments
            var maxParamsCount = constructorsInfo[0].GetParameters().Length;
            var constructorWithMaxParams = 0;
            for (var i = 1; i < constructorsInfo.Length; i++)
            {
                var currParamsCount = constructorsInfo[i].GetParameters().Length;
                if (currParamsCount > maxParamsCount)
                {
                    constructorWithMaxParams = i;
                    maxParamsCount = currParamsCount;
                }
            }   

            return constructorsInfo[constructorWithMaxParams];
        }
        
        private object[] GenerateArguments(Type t, ParameterInfo[] paramsInfo)
        {
            var args = new object[paramsInfo.Length];
            var textInfo = new CultureInfo("en-US",false).TextInfo;
            //All constructor parameters
            for (var i = 0; i < args.Length; i++)
            {
                if (paramsInfo[i].Name is not null)
                {
                    //Get field name by parameter name
                    var fieldName = textInfo.ToTitleCase(paramsInfo[i].Name);

                    //If custom generator for field type exists
                    if (_customGenerators.HasGenerator(t, fieldName))
                    {
                        //Get object of this field
                        var fieldInfo = t.GetField(fieldName, 
                            BindingFlags.Public | BindingFlags.Instance);
                        var propertyInfo = t.GetProperty(fieldName, 
                            BindingFlags.Public | BindingFlags.Instance);

                        if (fieldInfo is not null && fieldInfo.FieldType == paramsInfo[i].ParameterType ||
                            propertyInfo is not null && propertyInfo.PropertyType == paramsInfo[i].ParameterType)
                        {
                            //Get appropriate generator
                            var generator = _customGenerators.GetGenerator(t, fieldName);
                            //Generate value for argument
                            args[i] = generator.Generate(paramsInfo[i].ParameterType, _randomFaker);
                            continue;
                        }
                    }
                }
                
                args[i] = Create(paramsInfo[i].ParameterType);
            }

            return args;
        }

        private object CreateClass(Type t)
        {
            //Get appropriate constructor
            var constructor = GetConstructorForInvoke(t);
            //Get constructor parameters
            var paramsInfo = constructor.GetParameters();
            //Generate arguments
            var args = GenerateArguments(t, paramsInfo);
            //Call constructor with generated arguments
            return constructor.Invoke(args);
        }

        private void FillProperties(object obj, IReflect t)
        {
            //Get properties of type
            var propertiesInfo = t.GetProperties(BindingFlags.Public | BindingFlags.Instance);
            foreach (var property in propertiesInfo)
            {
                //Check if public setter for property is present
                if (property.SetMethod is not null && property.SetMethod.IsPublic)
                {
                    //Get property
                    var getMethod = property.GetMethod?.Invoke(obj, null);

                    //Call create for property
                    if (getMethod is null || getMethod.Equals(GetDefaultValue(property.PropertyType)))
                        property.SetValue(obj, Create(property.PropertyType));
                }
            }
        }
        
        //Set values for public fields of object
        private void FillFields(object obj, IReflect t)
        {
            //Get public fields
            var fieldsInfo = t.GetFields(BindingFlags.Public | BindingFlags.Instance);

            foreach (var field in fieldsInfo)
            {   
                //Get object of field
                var getMethod = field.GetValue(obj);

                //Call create
                if (getMethod is null || getMethod.Equals(GetDefaultValue(field.FieldType)))
                    field.SetValue(obj, Create(field.FieldType));
            }
        }

        //Same as FillProperties, but for custom generators
        private void FillPropertiesWithCustomGenerators(object obj, Type t)
        {
            var propertiesInfo = t.GetProperties(BindingFlags.Public | BindingFlags.Instance);
            foreach (var property in propertiesInfo)
            {
                var propertyType = property.PropertyType;
                if (_customGenerators.HasGenerator(t, property.Name) && property.CanWrite)
                {
                    var generator = _customGenerators.GetGenerator(t, property.Name);

                    if (generator.CanGenerate(propertyType))
                        property.SetValue(obj, generator.Generate(propertyType, _randomFaker));
                }
            }
        }
        
        //Same as FillFields, but for custom generators
        private void FillFieldsWithCustomGenerators(object obj, Type t)
        {
            var fieldsInfo = t.GetFields(BindingFlags.Public | BindingFlags.Instance);

            foreach (var field in fieldsInfo)
            {
                if (_customGenerators.HasGenerator(t, field.Name))
                {
                    var generator = _customGenerators.GetGenerator(t, field.Name);
                    field.SetValue(obj, generator.Generate(field.FieldType, _randomFaker));
                }
            }
        }

        //Check if object has public getter and setter for each property
        private bool IsDto(IReflect t)
        {
            var methods = t.GetMethods(BindingFlags.DeclaredOnly |
                                       BindingFlags.Instance | BindingFlags.Public);
            var methodsCount = methods.Length;

            var properties = t.GetProperties(BindingFlags.DeclaredOnly |
                                             BindingFlags.Instance | BindingFlags.Public);
            var propertiesCount = 0;
            foreach (var property in properties)
            {
                if (property.GetMethod is not null && property.GetMethod.IsPublic)
                    propertiesCount += 1;
                if (property.SetMethod is not null && property.SetMethod.IsPublic)
                    propertiesCount += 1;
            }

            return methodsCount - propertiesCount == 0;
        }

        private bool IsGenerated(Type t)
        {
            return _generatedTypes.Exists(genT => genT == t);
        }
    }
}