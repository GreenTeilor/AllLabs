namespace Generator;

using Microsoft.CodeAnalysis.CSharp.Syntax;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp.Formatting;
using Formatter = Microsoft.CodeAnalysis.Formatting.Formatter;
using System.Collections.Concurrent;
using static Microsoft.CodeAnalysis.CSharp.SyntaxFactory;

#pragma warning disable CS1998

public class Generator
{
    //Main method, that accepts whole text of file with classes, which tests we want to get
    public async Task<ConcurrentDictionary<string, string>> getNamesAndContents(string text)
    {
        return await getNamesAndContentsAsync(text);
    }

    private async Task<ConcurrentDictionary<string, string>> getNamesAndContentsAsync(string text)
    {
        //Document tree
        var syntaxTree = CSharpSyntaxTree.ParseText(text);
        //Get root of syntax tree
        var root = syntaxTree.GetRoot();
        //Create new compilation based on classes tree
        var compilation = CSharpCompilation.Create("MyCompilation").AddSyntaxTrees(syntaxTree);
        //Get semantic model of classes tree
        var semanticModel = compilation.GetSemanticModel(syntaxTree);
        //Get all classes
        var classes = root.DescendantNodes().OfType<ClassDeclarationSyntax>();
        //Empty thread-safe map
        var namesAndContents = new ConcurrentDictionary<string, string>();
        //To allow all block threads iterate simultaneously
        Parallel.ForEach(classes, clazz =>
        {
            //Create class unit
            var unit = generateUnit(clazz, semanticModel);
            //Full class representation based on unit
            var unitView = getUnitView(unit);
            //Add class representation to map
            namesAndContents.TryAdd(clazz.Identifier.ValueText, unitView);
        });
        return namesAndContents;
    }

    //Based on obtained declaration tree(unit), build full class representation
    private string getUnitView(CompilationUnitSyntax compilationUnitSyn)
    {
        var workspace = new AdhocWorkspace();
        var options = workspace.Options;
        options = options.WithChangedOption(CSharpFormattingOptions.NewLinesForBracesInMethods, false);
        options = options.WithChangedOption(CSharpFormattingOptions.NewLinesForBracesInTypes, false);
        var formattedNode = Formatter.Format(compilationUnitSyn, workspace, options);
        using
        var stringWriter = new StringWriter();
        formattedNode.WriteTo(stringWriter);
        return stringWriter.ToString();
    }

    public CompilationUnitSyntax generateUnit(ClassDeclarationSyntax Class, SemanticModel semanticModel)
    {
        //Create empty unit of class, which tests we want to generate
        var compilationUnit = CompilationUnit().AddUsings(UsingDirective(IdentifierName("System"))).AddUsings(UsingDirective(IdentifierName("System.Data"))).AddUsings(UsingDirective(IdentifierName("System.Collections.Generic"))).AddUsings(UsingDirective(IdentifierName("System.Linq"))).AddUsings(UsingDirective(IdentifierName("System.Text"))).AddUsings(UsingDirective(IdentifierName("System.Runtime.Serialization"))).AddUsings(UsingDirective(IdentifierName("Moq"))).AddUsings(UsingDirective(IdentifierName("NUnit.Framework")));
        //Get tree nodes(constructors)
        var constructorSyns = Class.DescendantNodes().OfType<ConstructorDeclarationSyntax>();
        ConstructorDeclarationSyntax? savedConstructorSyn = null;
        List<ParameterSyntax>? savedParameterSyns = null;
        var interfaceMembersMaxAmount = -1;
        var interfaceMembersAmount = 0;
        //If class has at least one constructor
        if (constructorSyns.Any())
        {
            //Each declared constructor
            foreach (var constructorSyn in constructorSyns)
            {
                //For constructor interface-parameters
                var tempParameterSyns = new List<ParameterSyntax>();
                interfaceMembersAmount = 0;
                //All constructor parameters
                foreach (var parameterSyn in constructorSyn.ParameterList.Parameters)
                {
                    //Get from tree node parameter symbol
                    var parameterSymbol = semanticModel.GetDeclaredSymbol(parameterSyn);
                    //If parameter is interface
                    if ((parameterSymbol!.Type.TypeKind == TypeKind.Interface) || (parameterSymbol.Type.Name.Length > 2 && parameterSymbol.Type.Name[0] == 'I' && char.IsUpper(parameterSymbol.Type.Name[1])))
                    {
                        //Save parameter to tempParameters to mock then
                        tempParameterSyns.Add(parameterSyn);
                        //Increment counter
                        interfaceMembersAmount++;
                    }
                }
                //If there is at least one public constructor
                if (constructorSyn.Modifiers.Any(modifier => modifier.IsKind(SyntaxKind.PublicKeyword)))
                {
                    //If this constructor has more interface parameters
                    if (interfaceMembersAmount > interfaceMembersMaxAmount)
                    {
                        //Then use constructor, that contains these interface parameters
                        interfaceMembersMaxAmount = interfaceMembersAmount;
                        savedConstructorSyn = constructorSyn;
                        savedParameterSyns = tempParameterSyns;
                    }
                }
            }
        }
        //If there is no constructors, create empty public constructor
        else
        {
            savedConstructorSyn = ConstructorDeclaration(Identifier(Class.Identifier.ValueText)).WithModifiers(TokenList(Token(SyntaxKind.PublicKeyword))).WithBody(Block());
            savedParameterSyns = new List<ParameterSyntax>();
        }
        //Namespace of class tests
        var namespaceSyn = NamespaceDeclaration(IdentifierName("Tests"));
        //Name of test class
        var classSyn = generateTestClass(Class.Identifier.ValueText);
        var parameterSynQuantity = 1;
        //Create mocks for interface parameters
        foreach (var parameterSyn in savedParameterSyns!)
        {
            //Add mocks into created test class
            classSyn = classSyn.AddMembers(generateField($"Mock<{parameterSyn.Type}>", $"_dependency{parameterSynQuantity}"));
            parameterSynQuantity++;
        }
        //Add field, that reference to instance of class, for which we generated tests
        classSyn = classSyn.AddMembers(generateField(Class.Identifier.ValueText, $"_myClassUnderTest"));
        //Generate method to initialize tested class fields
        classSyn = classSyn.AddMembers(generateSetUpMethod(savedConstructorSyn!, semanticModel, Class));
        //Get all methods for which we have to create tests(all public methods of class)
        var publicMethods = Class.Members.OfType<MethodDeclarationSyntax>().Where(method => method.Modifiers.Any(modifier => modifier.IsKind(SyntaxKind.PublicKeyword)));
        foreach (var publicMethod in publicMethods)
        {
            //Add to test class these methods
            classSyn = classSyn.AddMembers(generateTestMethod(publicMethod, semanticModel));
        }
        //Add test class into created namespace
        namespaceSyn = namespaceSyn.AddMembers(classSyn);
        //Add into unit created namespace
        compilationUnit = compilationUnit.AddMembers(namespaceSyn);
        return compilationUnit;
    }

    //Generate syntax tree node(declaration of test class)
    private ClassDeclarationSyntax generateTestClass(string name)
    {
        //Also add [TestFixture] attribute
        var classSyn = ClassDeclaration(name + "Tests").AddModifiers(Token(SyntaxKind.PublicKeyword)).WithAttributeLists(SingletonList(AttributeList(SingletonSeparatedList(Attribute(IdentifierName("TestFixture"))))));
        return classSyn;
    }

    //For field
    private FieldDeclarationSyntax generateField(string type, string name)
    {
        var variableSyn = VariableDeclaration(IdentifierName(type)).AddVariables(VariableDeclarator(Identifier(name)));
        var fieldSyn = FieldDeclaration(variableSyn).AddModifiers(Token(SyntaxKind.PrivateKeyword));
        return fieldSyn;
    }

    //Generates node(text) of method, that mock interfaces and provides other class dependencies
    private MethodDeclarationSyntax generateSetUpMethod(ConstructorDeclarationSyntax constructorSyn, SemanticModel semanticModel, ClassDeclarationSyntax classSyn)
    {
        var statementSyns = new List<StatementSyntax>();
        var argumentSyns = new List<ArgumentSyntax>();
        int ifaceQuantity = 1;
        int paramQuantity = 1;
        //All constructor parameters
        var parameterSyns = constructorSyn.ParameterList.Parameters;
        //Iterate through all parameters
        foreach (var parameterSyn in parameterSyns)
        {
            //Get parameter symbol
            var parameterSymbol = semanticModel.GetDeclaredSymbol(parameterSyn);
            //If parameter is interface
            if ((parameterSymbol!.Type.TypeKind == TypeKind.Interface) || (parameterSymbol.Type.Name.Length > 2 && parameterSymbol.Type.Name[0] == 'I' && char.IsUpper(parameterSymbol.Type.Name[1])))
            {
                //Generate assign expression
                var statementSyn = generateMoqType(parameterSyn.Type!, $"_dependency{ifaceQuantity}");
                //Generate argument we pass in constructor
                var argumentSyn = Argument(MemberAccessExpression(SyntaxKind.SimpleMemberAccessExpression, IdentifierName($"_dependency{ifaceQuantity}"), IdentifierName("Object")));
                //Add generated to arguments lists
                argumentSyns.Add(argumentSyn);
                statementSyns.Add(statementSyn);
                ifaceQuantity++;
            }
            //If parameter is primitive
            else
            {
                //Generate assign expression for primitive
                var variableSyn = generatePrimitiveType(parameterSyn.Type!, $"param{paramQuantity}");
                //Generate argument we pass in constructor
                var argumentSyn = Argument(IdentifierName($"param{paramQuantity}"));
                //Add generated to arguments lists
                argumentSyns.Add(argumentSyn);
                paramQuantity++;
                statementSyns.Add(LocalDeclarationStatement(variableSyn));
            }
        }
        //Get list of syntax nodes
        var argumentList = ArgumentList(SeparatedList(argumentSyns));
        //Generate assign expression signature for dependency
        var expressionStatementSyn = ExpressionStatement(AssignmentExpression(SyntaxKind.SimpleAssignmentExpression, IdentifierName("_myClassUnderTest"), ObjectCreationExpression(IdentifierName(classSyn.Identifier.ValueText)).WithArgumentList(argumentList)));
        //Add generated signature to list
        statementSyns.Add(expressionStatementSyn);
        //Create all set up method declaration and inner
        var methodSynResult = MethodDeclaration(PredefinedType(Token(SyntaxKind.VoidKeyword)), Identifier("SetUp")).AddModifiers(Token(SyntaxKind.PublicKeyword)).AddAttributeLists(AttributeList(SingletonSeparatedList(Attribute(IdentifierName("SetUp"))))).WithBody(Block(statementSyns));
        return methodSynResult;
    }

    //Creates node of test method
    private MethodDeclarationSyntax generateTestMethod(MethodDeclarationSyntax methodSyn, SemanticModel semanticModel)
    {
        var statementSyns = new List<StatementSyntax>();
        var argumentSyns = new List<ArgumentSyntax>();
        //All parameters of method
        var parameterSyns = methodSyn.ParameterList.Parameters;
        //Iterate
        foreach (var parameterSyn in parameterSyns)
        {
            //Get symbol of method parameter
            var parameterSymbol = semanticModel.GetDeclaredSymbol(parameterSyn);
            //Create mock if it's interface
            if ((parameterSymbol!.Type.TypeKind == TypeKind.Interface) || (parameterSymbol.Type.Name.Length > 2 && parameterSymbol.Type.Name[0] == 'I' && char.IsUpper(parameterSymbol.Type.Name[1])))
            {
                //Generate assign expression to initialize parameter
                var statementSyn = generateMoqType(parameterSyn.Type!, parameterSyn.Identifier.ValueText);
                //Generate argument
                var argumentSyn = Argument(MemberAccessExpression(SyntaxKind.SimpleMemberAccessExpression, IdentifierName(parameterSyn.Identifier.ValueText), IdentifierName("Object")));
                //Add to lists
                argumentSyns.Add(argumentSyn);
                statementSyns.Add(statementSyn);
            }
            //If parameter is primitive
            else
            {
                //Generate assign expression for primitive
                var variableSyn = generatePrimitiveType(parameterSyn.Type!, parameterSyn.Identifier.ValueText);
                //Generate argument we pass into method
                var argumentSyn = Argument(IdentifierName(parameterSyn.Identifier.ValueText));
                //Add to lists
                argumentSyns.Add(argumentSyn);
                statementSyns.Add(LocalDeclarationStatement(variableSyn));
            }
        }
        //Get list of separate syntax nodes-parameters of method
        var argumentList = ArgumentList(SeparatedList(argumentSyns));
        //If passed to test method doesn't return anything
        if (methodSyn.ReturnType.ToString() == "void")
        {
            //Create lambda expression we pass into Assert.DoesNotThrow
            var statementSyn = ExpressionStatement(InvocationExpression(MemberAccessExpression(SyntaxKind.SimpleMemberAccessExpression, IdentifierName("Assert"), IdentifierName("DoesNotThrow"))).WithArgumentList(ArgumentList(SingletonSeparatedList(Argument(ParenthesizedLambdaExpression().WithBlock(Block(SingletonList<StatementSyntax>(ExpressionStatement(InvocationExpression(MemberAccessExpression(SyntaxKind.SimpleMemberAccessExpression, IdentifierName("_myClassUnderTest"), IdentifierName(methodSyn.Identifier.ValueText))).WithArgumentList(argumentList))))))))));
            statementSyns.Add(statementSyn);
        }
        //If method returns anything
        else
        {
            //Get return type
            var typeSyntax = methodSyn.ReturnType;
            //Create declaration of variable, that represents method call result
            var variableSyn = VariableDeclaration(typeSyntax, SingletonSeparatedList(VariableDeclarator(Identifier("actual")).WithInitializer(EqualsValueClause(InvocationExpression(MemberAccessExpression(SyntaxKind.SimpleMemberAccessExpression, IdentifierName("_myClassUnderTest"), IdentifierName(methodSyn.Identifier.ValueText))).WithArgumentList(argumentList)))));
            //Add to list
            statementSyns.Add(LocalDeclarationStatement(variableSyn));
            //Same with expected value
            var statementSyn1 = generatePrimitiveType(typeSyntax, "expected");
            statementSyns.Add(LocalDeclarationStatement(statementSyn1));
            //Generate Assert.That statement
            var statementSyn2 = ExpressionStatement(InvocationExpression(MemberAccessExpression(SyntaxKind.SimpleMemberAccessExpression, IdentifierName("Assert"), IdentifierName("That"))).WithArgumentList(ArgumentList(SeparatedList<ArgumentSyntax>(new SyntaxNodeOrToken[]
            {
                Argument(IdentifierName("actual")),
                    Token(SyntaxKind.CommaToken),
                    Argument(InvocationExpression(MemberAccessExpression(SyntaxKind.SimpleMemberAccessExpression, IdentifierName("Is"), IdentifierName("EqualTo"))).WithArgumentList(ArgumentList(SingletonSeparatedList(Argument(IdentifierName("expected"))))))
            }))));
            statementSyns.Add(statementSyn2);
        }
        //Generate Assert.Fail statement(stub with additional logic)
        var expressionStatementSyn = ExpressionStatement(InvocationExpression(MemberAccessExpression(SyntaxKind.SimpleMemberAccessExpression, IdentifierName("Assert"), IdentifierName("Fail"))).WithArgumentList(ArgumentList(SingletonSeparatedList(Argument(LiteralExpression(SyntaxKind.StringLiteralExpression, Literal("autogenerated")))))));
        statementSyns.Add(expressionStatementSyn);
        //Create method declaration and inner
        var methodSynResult = MethodDeclaration(PredefinedType(Token(SyntaxKind.VoidKeyword)), Identifier(methodSyn.Identifier.ValueText + "Test")).AddModifiers(Token(SyntaxKind.PublicKeyword)).AddAttributeLists(AttributeList(SingletonSeparatedList(Attribute(IdentifierName("Test"))))).WithBody(Block(statementSyns));
        return methodSynResult;
    }

    //Generate assign expression signature for primitives
    private VariableDeclarationSyntax generatePrimitiveType(TypeSyntax typeSyn, string name)
    {
        return VariableDeclaration(typeSyn, SingletonSeparatedList(VariableDeclarator(Identifier(name)).WithInitializer(EqualsValueClause(DefaultExpression(typeSyn)))));
    }

    //Generate assign expression signature for interfaces
    private ExpressionStatementSyntax generateMoqType(TypeSyntax typeSyn, string name)
    {
        return ExpressionStatement(AssignmentExpression(SyntaxKind.SimpleAssignmentExpression, IdentifierName(name), ObjectCreationExpression(GenericName(Identifier("Mock")).WithTypeArgumentList(TypeArgumentList(SingletonSeparatedList(typeSyn)))).WithArgumentList(ArgumentList())));
    }
}