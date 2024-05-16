using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Tracer.ResultOutput;
using Tracer.Serialization;

namespace Tracer
{
    /*Tracer должен собирать следующую информацию об измеряемом методе:
    имя метода;
    имя класса с измеряемым методом;
    время выполнения метода.
    */
    public class Tracer : ITracer
    {

        private TraceResultStruct _traceResultStruct;
        private MethodNode _method;
        private MethodNode _prevMethod;
        private int _currentMethodDepth;

        private static ConcurrentDictionary<int, TraceResultStruct> _tracersDict;

        private void CountTotalTime()
        {
            _traceResultStruct.Time = 0;
            foreach (var method in _traceResultStruct.Methods)
            {
                _traceResultStruct.Time += method.GetMethodStruct.Time;
            }
        }

        private string GetJSON(TraceResultStruct result)
        {
            JsonTraceResultSerializer serializer = new JsonTraceResultSerializer();
            return serializer.Serialize(result);
        }

        private string GetXML(TraceResultStruct result)
        {
            XMLTraceResultSerializer serializer = new XMLTraceResultSerializer();
            return serializer.Serialize(result);
        }

        public void StartTrace()
        {
            _prevMethod = _method;
            _method = new MethodNode();
            _method.parentMethod = _prevMethod;

            int prevMethodDepth = _prevMethod?.GetMethodStruct.MethodDepth ?? -1;
            _currentMethodDepth = _method.GetMethodStruct.MethodDepth;

            switch (prevMethodDepth)
            {
                case var depth when depth == -1: //Если prevMethod null, то добавляем в Methods Tracer текущий метод
                    _traceResultStruct.Methods.Add(_method);
                    break;
                case var depth when depth == (_currentMethodDepth - 1): //Если глубина prevMethod совпадает с текущей глубиной - 1, 
                                                                        //значит текущий метод нужно добавить в внутренние методы prevMethod
                    _prevMethod.GetMethodStruct.internalMethodStructs.Add(_method);
                    break;
                default:
                    _traceResultStruct.Methods.Add(_method);
                    break;
            }

            _method.StartStopwatch();
        }

        public void StopTrace()
        {
            _method.StopStopwatch();



            if (_prevMethod == _method)
            {
                if (_prevMethod.parentMethod != null)
                {
                    _method = _prevMethod.parentMethod;
                }
            }
            else
            {
                if (_method.GetMethodStruct.MethodDepth == 0)
                {
                    _prevMethod = _method;
                }
                else
                {
                    _method = _prevMethod;
                }
            }

        }
        public TraceResultStruct GetTraceResult()
        {
            CountTotalTime();

            _tracersDict.AddOrUpdate(_traceResultStruct.Id, _traceResultStruct, (key, existingValue) => _traceResultStruct);
            return _traceResultStruct;
        }

        public void GetMultiThreadResult(string filePath1, string filePath2)
        {
            string json = string.Empty;
            string xml = string.Empty;
            foreach(var thread in _tracersDict)
            {
                json += GetJSON(thread.Value) + ", ";
                xml += GetXML(thread.Value);
            }
            ConsoleResult("[\n" + json + "\n]", xml);
            FileOutputResult(filePath1, filePath2, "[\n" + json + "\n]", xml);
        }


        public void ConsoleResult(string resJSON,string resXML)
        {
            IResultWritable writer = new ConsoleResultWriter();
            writer.WriteResult(resJSON);
            writer.WriteResult(resXML);
        }

        public void FileOutputResult(string filePath1, string filePath2, string resJSON, string resXML)
        {
            IResultWritable writer = new FileResultWriter(filePath1);
            writer.WriteResult(resJSON);
            writer = new FileResultWriter(filePath2);
            writer.WriteResult(resXML);
        }


        public Tracer(int threadID)
        {
            _traceResultStruct.Id = threadID;
            _traceResultStruct.Methods = new List<MethodNode>();
            //Все потоки имеют один и тот же потокобезопасный словарь(static), соответственно объект нужно инициализировать только один
            //раз при первом создании Tracer
            if (_tracersDict == null)
            {
                _tracersDict = new ConcurrentDictionary<int, TraceResultStruct>();
            }
        }
    }
}
