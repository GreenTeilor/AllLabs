using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Newtonsoft.Json;


namespace Tracer
{
    public interface ISerializable
    {
        string Serialize(TraceResultStruct traceResult);
    }
}
