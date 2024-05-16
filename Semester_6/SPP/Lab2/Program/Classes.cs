
public class A
{
    public string SetInConstructor { get; }
    public B B { get; set; }

    public int IntProperty { get; set; }
    public int IntField;
    public int FieldWithoutSet { get; }
    public int FieldWithPrivateSet { get; private set; }
    
    public decimal DecimalValue; 
    public short ShortValue;
    public string StringValue;

    public string River { get; }
    public int Mark;

    private A()
    {
        SetInConstructor = "SetInNoParametersConstructor";
    }

    public A(string river)
    {
        SetInConstructor = "SetInOneParameterConstructor";
        River = river;
    }
}

public class B
{
    public C C { get; set; }
}

public class C
{
    public A A { get; set; }
}