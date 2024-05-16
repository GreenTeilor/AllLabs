using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Text;

namespace AssemblyBrowserLib
{
    public class AssemblyBrowser : IAssemblyBrowser
    {
        // List of all methods of extension
        private readonly List<MethodInfo> _extensionMethods = new List<MethodInfo>();

        // Add all methods of extension
        private void AddExtensionMethods(ContainerInfo[] containers)
        {
            foreach (var method in _extensionMethods)
            {
                var parameters = method.GetParameters();
                if (parameters.Length < 0) continue;
                var param = parameters[0];
                var extentedType = param.ParameterType;
                foreach (var container in containers)
                {
                    if (container.DeclarationName != extentedType.Namespace) continue;
                    var types = container.Members;
                    foreach (var type in types)
                    {
                        if (type.DeclarationName == GetTypeDeclaration(extentedType.GetTypeInfo()))
                        {
                            ((TypeInfo)type).AddMember(new MemberInfo() { DeclarationName = "ext. method: " + CreateExtensionMethodDeclarationString(method), Name = method.Name });
                        }
                    }
                }
            }
        }

        public ContainerInfo[] GetNamespaces(string assemblyPath)
        {
            // Load assembly to parse
            var assembly = Assembly.LoadFile(assemblyPath);
            // Get all types in assembly
            var types = assembly.GetTypes();
            // Map of all namespaces in assembly
            var namespaces = new Dictionary<string, ContainerInfo>();
            // All types in loaded assembly
            foreach (var type in types)
            {
                // Namespace of current type
                var typeNamespace = type.Namespace;

                // Null, if there is no namespace for type
                if (typeNamespace == null) continue;

                // Container fir namespace of current type
                ContainerInfo namespaceInfo;

                // If there is no namespace in map
                if (!namespaces.ContainsKey(typeNamespace))
                {
                    // Initialize container with name of current namespace
                    namespaceInfo = new NamespaceInfo { DeclarationName = typeNamespace };
                    // Add namespace to map
                    namespaces.Add(typeNamespace, namespaceInfo);
                }
                // Otherwise just retrieve namespace info
                else
                {
                    namespaces.TryGetValue(typeNamespace, out namespaceInfo);
                }
                // Get info about current type(including inner types)
                var typeInfo = GetTypeInfo(type);
                // Add type info to namespace info
                namespaceInfo?.AddMember(typeInfo);
            }
            // Get all namespaces info from map
            ContainerInfo[] result = namespaces.Values.ToArray();
            AddExtensionMethods(result);

            return result;
        }

        // Get type name
        private string GetTypeName(Type type)
        {
            // Name of namespace + type name
            var result = $"{type.Namespace}.{type.Name}";
            // Add info if type is generic
            if (type.IsGenericType)
            {
                result += GetGenericArgumentsString(type.GetGenericArguments());
            }
            return result;
        }

        // Get method name
        private string GetMethodName(MethodBase method)
        {
            // If method is generified
            if (method.IsGenericMethod)
            {
                // Get all generic arguments of method
                return method.Name + GetGenericArgumentsString(method.GetGenericArguments());
            }
            return method.Name;
        }
        
        // Get generic parameters of type
        private string GetGenericArgumentsString(Type[] arguments)
        {
            var genericArgumentsString = new StringBuilder("<");
            for (int i = 0; i < arguments.Length; i++)
            {
                // Concat
                genericArgumentsString.Append(GetTypeName(arguments[i]));
                if (i != arguments.Length - 1)
                {
                    genericArgumentsString.Append(", ");
                }
            }
            genericArgumentsString.Append(">");

            return genericArgumentsString.ToString();
        }

        // Return declaration name of method
        private string CreateMethodDeclarationString(MethodInfo methodInfo)
        {
            // Get name of return type
            var returnType = GetTypeName(methodInfo.ReturnType);
            // Method parameters
            var parameters = methodInfo.GetParameters();
            // Concat access modifier + method name + parameters types
            var declaration =
                $"{GetMethodDeclaration(methodInfo)} {returnType} {GetMethodName(methodInfo)} {GetMethodParametersString(parameters)}";

            return declaration;
        }

        //Same as above, but for extension method
        private string CreateExtensionMethodDeclarationString(MethodInfo methodInfo)
        {
            var returnType = GetTypeName(methodInfo.ReturnType);
            var parameters = new List<ParameterInfo>(methodInfo.GetParameters());
            parameters.RemoveAt(0);
            var declaration =
                $"{GetMethodDeclaration(methodInfo)} {returnType} {GetMethodName(methodInfo)} {GetMethodParametersString(parameters.ToArray())}";

            return declaration;
        }

        // Get method parameters types names
        private string GetMethodParametersString(ParameterInfo[] parameters)
        {
            var parametersString = new StringBuilder("(");
            for (int i = 0; i < parameters.Length; i++)
            {
                parametersString.Append(GetTypeName(parameters[i].ParameterType));
                if (i != parameters.Length - 1)
                {
                    parametersString.Append(", ");
                }
            }
            parametersString.Append(")");

            return parametersString.ToString();
        }

        // Get signature of type(access modifier + additional info, if it's class or delegate)
        private string GetTypeDeclaration(System.Reflection.TypeInfo typeInfo)
        {
            var result = new StringBuilder();
            // Access 
            if (typeInfo.IsNestedPublic || typeInfo.IsPublic)
                result.Append("public ");
            else if (typeInfo.IsNestedPrivate)
                result.Append("private ");
            else if (typeInfo.IsNestedFamily)
                result.Append("protected ");
            else if (typeInfo.IsNestedAssembly)
                result.Append("internal ");
            else if (typeInfo.IsNestedFamORAssem)
                result.Append("protected internal ");
            else if (typeInfo.IsNestedFamANDAssem)
                result.Append("private protected ");
            else if (typeInfo.IsNotPublic)
                result.Append("private ");
            // Abstract
            if (typeInfo.IsAbstract && typeInfo.IsSealed)
                result.Append("static ");
            else if (typeInfo.IsAbstract)
                result.Append("abstract ");
            else if (typeInfo.IsSealed)
                result.Append("sealed ");
            //If it's class or delegate(neither interface nor primitive type)
            if (typeInfo.IsClass)
                result.Append("class ");
            else if (typeInfo.IsEnum)
                result.Append("enum ");
            else if (typeInfo.IsInterface)
                result.Append("interface ");
            else if (typeInfo.IsGenericType)
                result.Append("generic ");
            else if (typeInfo.IsValueType && !typeInfo.IsPrimitive)
                result.Append("struct ");

            result.Append($"{GetTypeName(typeInfo.AsType())} ");

            return result.ToString();
        }

        // Get access modifier of method
        private string GetMethodDeclaration(MethodBase methodBase)
        {
            var result = new StringBuilder();
            if (methodBase.IsAssembly)
                result.Append("internal ");
            else if (methodBase.IsFamily)
                result.Append("protected ");
            else if (methodBase.IsFamilyOrAssembly)
                result.Append("protected internal ");
            else if (methodBase.IsFamilyAndAssembly)
                result.Append("private protected ");
            else if (methodBase.IsPrivate)
                result.Append("private ");
            else if (methodBase.IsPublic)
                result.Append("public ");

            if (methodBase.IsStatic)
                result.Append("static ");
            else if (methodBase.IsAbstract)
                result.Append("abstract ");
            else if (methodBase.IsVirtual)
                result.Append("virtual ");

            return result.ToString();
        }

        // Get property declaration
        private string GetPropertyDeclaration(PropertyInfo propertyInfo)
        {
            var result = new StringBuilder(GetTypeName(propertyInfo.PropertyType));
            result.Append(" ");
            // Property name
            result.Append(propertyInfo.Name);
            // Getters and setters
            var accessors = propertyInfo.GetAccessors(true);
            foreach (var accessor in accessors)
            {
                // If getter or setter have special name, then add this name to result
                if (accessor.IsSpecialName)
                {
                    result.Append(" { ");
                    result.Append(accessor.Name);
                    result.Append(" } ");
                }
            }

            return result.ToString();
        }

        // Get event declaration
        private string GetEventDeclaration(EventInfo eventInfo)
        {
            var result = new StringBuilder();
            // Event type + name
            result.Append($"{GetTypeName(eventInfo.EventHandlerType)} {eventInfo.Name}");
            result.Append($" [{eventInfo.AddMethod.Name}] ");
            result.Append($" [{eventInfo.RemoveMethod.Name}] ");

            return result.ToString();
        }

        // Get field declaration
        private string GetFieldDeclaration(FieldInfo fieldInfo)
        {
            var result = new StringBuilder();
            // Access modifier
            if (fieldInfo.IsAssembly)
                result.Append("internal ");
            else if (fieldInfo.IsFamily)
                result.Append("protected ");
            else if (fieldInfo.IsFamilyOrAssembly)
                result.Append("protected internal ");
            else if (fieldInfo.IsFamilyAndAssembly)
                result.Append("private protected ");
            else if (fieldInfo.IsPrivate)
                result.Append("private ");
            else if (fieldInfo.IsPublic)
                result.Append("public ");

            if (fieldInfo.IsInitOnly)
                result.Append("readonly ");
            if (fieldInfo.IsStatic)
                result.Append("static ");
            // Add type name of field
            result.Append(GetTypeName(fieldInfo.FieldType));
            result.Append(" ");
            // Add field name
            result.Append(fieldInfo.Name);

            return result.ToString();
        }

        // Get constructor declaration
        private string GetConstructorDeclaration(ConstructorInfo constructorInfo)
        {
            // Access modifier + name + parameters
            return
                $"{GetMethodDeclaration(constructorInfo)} {GetMethodName(constructorInfo)} {GetMethodParametersString(constructorInfo.GetParameters())}";
        }

        //Get full type info
        private TypeInfo GetTypeInfo(Type type)
        {
            var typeInfo = new TypeInfo() 
            {
                // Get declaration of this type
                DeclarationName = GetTypeDeclaration(type.GetTypeInfo()),
                // Type name
                Name = type.Name
            };
            // Inner members of type
            var members = type.GetMembers(BindingFlags.NonPublic
                                          | BindingFlags.Instance
                                          | BindingFlags.Public
                                          | BindingFlags.Static);
            
            foreach (var member in members)
            {
                // Variable to contain info about inner member of type
                var memberInfo = new MemberInfo();
                // If inner member is method
                if (member.MemberType == MemberTypes.Method)
                {
                    // Cast to MethodInfo
                    var method = (MethodInfo)member;
                    // If method is extension method
                    if (method.IsDefined(typeof(ExtensionAttribute), false))
                    {
                        // Add to extension methods
                        _extensionMethods.Add(method);
                    }
                    // Get method signature
                    memberInfo.DeclarationName = CreateMethodDeclarationString(method);
                }
                // If inner member is property
                else if (member.MemberType == MemberTypes.Property)
                {
                    // Get property declaration
                    memberInfo.DeclarationName = GetPropertyDeclaration((PropertyInfo)member);
                }
                // If inner member is field
                else if (member.MemberType == MemberTypes.Field)
                {
                    // Get field declaration
                    memberInfo.DeclarationName = GetFieldDeclaration(((FieldInfo)member));
                }
                // If inner member is event
                else if (member.MemberType == MemberTypes.Event)
                {
                    // Get event declaration
                    memberInfo.DeclarationName = GetEventDeclaration((EventInfo)member);
                }
                // If inner member is constructor
                else if (member.MemberType == MemberTypes.Constructor)
                {
                    // Get constructor declaration
                    memberInfo.DeclarationName = GetConstructorDeclaration((ConstructorInfo)member);
                }
                else
                {
                    //If none of above
                    memberInfo.DeclarationName = GetTypeDeclaration((System.Reflection.TypeInfo)member);
                }
                // If declaration name of inner member is not null
                if (memberInfo.DeclarationName != null)
                {
                    // Add to member array of type
                    memberInfo.Name = member.Name;
                    typeInfo.AddMember(memberInfo);
                }
            }

            return typeInfo;
        }
    }
}
