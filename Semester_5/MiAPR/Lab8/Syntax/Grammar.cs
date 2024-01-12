using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Syntax
{
    public class Grammar
    {
        public Grammar(ElementType startElementType, List<Rule> rules,
            Dictionary<string, ElementType> elementTypes)
        {
            Rules = rules;
            StartElementType = startElementType;
            ElementTypes = elementTypes;
        }

        protected Grammar()
        {
        }

        protected Dictionary<string, ElementType> ElementTypes { get; set; }
        protected List<Rule> Rules { get; set; }
        protected ElementType StartElementType { get; set; }

        public Element GetImage()
        {
            return GetElement(StartElementType);
        }

        private Element GetElement(ElementType elementType)
        {
            var terminalElementType = elementType as TerminalElementType;
            if (terminalElementType != null)
            {
                return terminalElementType.StandartElement;
            }

            var rule = Rules.FirstOrDefault(x => x.StartElementType.Name == elementType.Name);
            Debug.Assert(rule != null, "rule != null");
            return rule.TransformConnect(GetElement(rule.FirstArgumentType),
                GetElement(rule.SecondArgumentType));
        }

        public RecognazingResult IsImage(IEnumerable<Element> baseElements)
        {
            var elements = new ConcurrentBag<Element>(baseElements);

            foreach (var rule in Rules)
            {
                var result = ContainRuleAgruments(elements, rule);
                elements = result.Elements;
                if (!result.IsElementFound)
                    return new RecognazingResult(rule.StartElementType.Name, false);
            }
            return new RecognazingResult("", true);
        }

        private static ContainRuleAgrumentsResult ContainRuleAgruments(
            ConcurrentBag<Element> elements, Rule rule)
        {
            var result = new ContainRuleAgrumentsResult
            {
                Elements = new ConcurrentBag<Element>(elements),
                IsElementFound = false
            };

            foreach (var firstElement in elements)
            {
                if (firstElement.ElementType.Name == rule.FirstArgumentType.Name)
                {
                    result = ContainRuleAgrumentsForFirstElement(elements, rule, firstElement,
                        result);
                }
            }
            return result;
        }

        private static ContainRuleAgrumentsResult ContainRuleAgrumentsForFirstElement(
            IEnumerable<Element> elements, Rule rule,
            Element firstElement, ContainRuleAgrumentsResult result)
        {
            var element = firstElement;
            Parallel.ForEach(elements, (Element secondElement) =>
            {
                if (rule.IsRulePare(element, secondElement))
                {
                    result.Elements.Add(rule.Connect(element, secondElement));
                    result.IsElementFound = true;
                }
            });
            return result;
        }

        public override string ToString()
        {
            var result = new StringBuilder();
            foreach (var rule in Rules)
            {
                result.AppendFormat("{0} -> {1}({2}, {3}); ", rule.StartElementType.Name,
                    rule.Name, rule.FirstArgumentType.Name, rule.SecondArgumentType.Name);
            }
            return result.ToString();
        }

        private class ContainRuleAgrumentsResult
        {
            public ConcurrentBag<Element> Elements { get; set; }
            public bool IsElementFound { get; set; }
        }
    }
}