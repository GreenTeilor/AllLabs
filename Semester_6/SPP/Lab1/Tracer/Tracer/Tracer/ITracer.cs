using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tracer
{
    public interface ITracer
    {
        // Вызывается в начале замеряемого метода
        void StartTrace();

        // Вызывается в конце замеряемого метода
        void StopTrace();

        // Получить результаты измерений
        TraceResultStruct GetTraceResult();
    }
}
    