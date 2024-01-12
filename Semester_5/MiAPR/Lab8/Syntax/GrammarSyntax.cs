using System;
using System.Collections.Generic;

namespace Syntax
{
    public class GrammarSyntax
    {
        private int elementNumber;
        private readonly Dictionary<string, ElementType> elementTypes;
        private readonly List<Rule> emptyRules;
        private readonly List<Rule> rules;
        private readonly ElementType startElemenType;

        public GrammarSyntax(List<Element> baseElements)
        {
            var elements = new List<Element>(baseElements);
            emptyRules = new List<Rule>
            {
                new LeftRule(null, null, null),
                new UpRule(null, null, null)
            };
            rules = new List<Rule>();
            elementNumber = 1;
            elementTypes = TerminalElementCreater.GetTerminalElementTypes();
            startElemenType = ConnectElementToSintax(elements);
        }

        public Grammar Grammar
        {
            get { return new Grammar(startElemenType, rules, elementTypes); }
        }

        private ElementType ConnectElementToSintax(List<Element> elements)
        {
            if (elements.Count == 1) return elements[0].ElementType;
            RuleSearchResult searchRuleResult = null;
            foreach (var candidate in elements)
            {
                searchRuleResult = SearchRule(elements, candidate);
                if (searchRuleResult != null) break;
            }
            if (searchRuleResult == null) throw new InvalidElementException();
            elements = searchRuleResult.Elements;
            var result = new ElementType(String.Format("O{0}", elementNumber++));
            elementTypes.Add(result.Name, result);
            rules.Add(searchRuleResult.GetRule(result));
            return result;
        }

        private RuleSearchResult SearchRule(List<Element> elements, Element candidate)
        {
            foreach (var rule in emptyRules)
            {
                if (IsFirstInRule(rule, candidate, elements))
                {
                    elements.Remove(candidate);
                    return new RuleSearchResult
                    {
                        FirstElementType = candidate.ElementType,
                        SecondElementType = ConnectElementToSintax(elements),
                        EmptyRule = rule,
                        Elements = elements
                    };
                }
                if (IsSecondInRule(rule, candidate, elements))
                {
                    elements.Remove(candidate);
                    return new RuleSearchResult
                    {
                        FirstElementType = ConnectElementToSintax(elements),
                        SecondElementType = candidate.ElementType,
                        EmptyRule = rule,
                        Elements = elements
                    };
                }
            }
            return null;
        }

        private bool IsFirstInRule(Rule rule, Element candidate, List<Element> otherElements)
        {
            foreach (var element in otherElements)
            {
                if (IsDifferentElementFirstInRule(rule, candidate, element))
                    return false;
            }
            return true;
        }

        private bool IsSecondInRule(Rule rule, Element candidate, List<Element> otherElements)
        {
            foreach (var element in otherElements)
            {
                if (IsDifferentElementSecondInRule(rule, candidate, element))
                    return false;
            }
            return true;
        }

        private static bool IsDifferentElementFirstInRule(Rule rule, Element candidate,
            Element element)
        {
            return candidate.StartPosition != element.StartPosition &&
                   candidate.EndPosition != element.EndPosition &&
                   !rule.IsRulePositionPare(candidate, element);
        }

        private static bool IsDifferentElementSecondInRule(Rule rule, Element candidate,
            Element element)
        {
            return candidate.StartPosition != element.StartPosition &&
                   candidate.EndPosition != element.EndPosition &&
                   !rule.IsRulePositionPare(element, candidate);
        }
    }
}