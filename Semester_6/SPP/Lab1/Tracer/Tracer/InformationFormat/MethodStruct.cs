using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace Tracer
{
    public struct MethodStruct
    {
        [XmlAttribute("name")]
        public string Name;
        [XmlAttribute("class")]
        public string ClassName;
        [XmlAttribute("time")]
        public double Time;

        [XmlElement("methods")]
        [JsonProperty(PropertyName = "methods")]
        public List<MethodNode> internalMethodStructs;
        [JsonIgnore]
        [XmlIgnore]
        public int MethodDepth;
    }
}
