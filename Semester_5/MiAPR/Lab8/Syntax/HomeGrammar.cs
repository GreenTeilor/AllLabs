using System.Collections.Generic;
using System.Windows;

namespace Syntax
{
    public class HomeGrammar : Grammar
    {
        public HomeGrammar()
        {
            ElementTypes = GetElementTypes();
            StartElementType = new ElementType("home");
            Rules = new List<Rule>
            {
                new LeftRule(ElementTypes["roof"], ElementTypes["a3"], ElementTypes["a4"]),
                new LeftRule(ElementTypes["parallel"], ElementTypes["a2"], ElementTypes["a2"]),
                new UpRule(ElementTypes["three"], ElementTypes["a1"], ElementTypes["parallel"]),
                new UpRule(ElementTypes["door"], ElementTypes["roof"], ElementTypes["three"]),
                new UpRule(ElementTypes["square"], ElementTypes["three"], ElementTypes["a1"]),
                new InsideRule(ElementTypes["window"], ElementTypes["roof"], ElementTypes["square"]),
                new LeftRule(ElementTypes["windowAndDoor"], ElementTypes["window"],
                    ElementTypes["door"]),
                new InsideRule(ElementTypes["down"], ElementTypes["windowAndDoor"],
                    ElementTypes["square"]),
                new UpRule(StartElementType, ElementTypes["roof"], ElementTypes["down"])
            };
        }

        private static Dictionary<string, ElementType> GetElementTypes()
        {
            return new Dictionary<string, ElementType>
            {
                {"a1", new TerminalElementType("a1", new Line(new Point(0, 0), new Point(10, 0)))},
                {"a2", new TerminalElementType("a2", new Line(new Point(0, 0), new Point(0, 10)))},
                {"a3", new TerminalElementType("a3", new Line(new Point(0, 0), new Point(10, 10)))},
                {"a4", new TerminalElementType("a4", new Line(new Point(10, 0), new Point(0, 10)))},
                {"roof", new ElementType("roof")},
                {"parallel", new ElementType("parallel")},
                {"three", new ElementType("three")},
                {"square", new ElementType("square")},
                {"down", new ElementType("down")},
                {"windowAndDoor", new ElementType("windowAndDoor")},
                {"window", new ElementType("window")},
                {"door", new ElementType("door")}
            };
        }
    }
}