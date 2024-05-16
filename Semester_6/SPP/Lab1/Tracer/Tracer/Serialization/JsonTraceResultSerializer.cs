using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tracer
{
    public class JsonTraceResultSerializer : ISerializable
    {
        public string Serialize(TraceResultStruct traceResult)
        {
            return JsonConvert.SerializeObject(traceResult, Formatting.Indented);
        }
    }
}
