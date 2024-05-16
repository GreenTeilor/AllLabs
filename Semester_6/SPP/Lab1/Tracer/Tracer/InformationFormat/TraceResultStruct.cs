using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace Tracer
{
    [XmlRoot(ElementName = "root")]
    public struct TraceResultStruct
    {
        [XmlAttribute("id")]
        public int Id;
        [XmlAttribute("time")]
        public double Time;
        public List<MethodNode> Methods;
    }
}
