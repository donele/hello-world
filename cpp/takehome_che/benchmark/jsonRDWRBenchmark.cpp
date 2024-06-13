#include <benchmark/benchmark.h>
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "xjson.h"
#include <iostream>


using namespace rapidjson;
using namespace std;

struct RapidJsonHandler {
    bool Null() { return true; }
    bool Bool(bool b) {  return true; }
    bool Int(int i) { return true; }
    bool Uint(unsigned u) { return true; }
    bool Int64(int64_t i) { return true; }
    bool Uint64(uint64_t u) { return true; }
    bool Double(double d) { return true; }
    bool RawNumber(const char* str, SizeType length, bool copy) { 
        return true;
    }
    bool String(const char* str, SizeType length, bool copy) { 
        return true;
    }
    bool StartObject() {  return true; }
    bool Key(const char* str, SizeType length, bool copy) {
        return true;
    }
    bool EndObject(SizeType memberCount) { return true; }
    bool StartArray() {return true; }
    bool EndArray(SizeType elementCount) {return true; }
};

struct TestJson : public JsonObj
{
    double dvalue_;
    float fvalue_;
    int ivalue_;
    long lvalue_;
    std::string svalue_;
    std::vector<std::string> vsvalue_;
    std::vector<double> vdvalue_;
    std::vector<long> vlvalue_;

    TestJson()
    {
        mem2fromStr_["dvalue"] = [this](const std::string& v){fromStr(v, dvalue_);};
        mem2fromStr_["fvalue"] = [this](const std::string& v){fromStr(v, fvalue_);};
        mem2fromStr_["ivalue"] = [this](const std::string& v){fromStr(v, ivalue_);};
        mem2fromStr_["lvalue"] = [this](const std::string& v){fromStr(v, lvalue_);};
        mem2fromStr_["svalue"] = [this](const std::string& v){fromStr(v, svalue_);};
        mem2fromStr_["vsvalue"] = [this](const std::string& v){fromStr(v, vsvalue_);};
        mem2fromStr_["vdvalue"] = [this](const std::string& v){fromStr(v, vdvalue_);};
        mem2fromStr_["vlvalue"] = [this](const std::string& v){fromStr(v, vlvalue_);};

        mem2toStr_["dvalue"] = [this](){return toStr(dvalue_);};
        mem2toStr_["fvalue"] = [this](){return toStr(fvalue_);};
        mem2toStr_["ivalue"] = [this](){return toStr(ivalue_);};
        mem2toStr_["lvalue"] = [this](){return toStr(lvalue_);};
        mem2toStr_["svalue"] = [this](){return toStr(svalue_);};
        mem2toStr_["vsvalue"] = [this](){return toStr(vsvalue_);};
        mem2toStr_["vdvalue"] = [this](){return toStr(vdvalue_);};
        mem2toStr_["vlvalue"] = [this](){return toStr(vlvalue_);};
    }
};


static void BM_rapidjsonReadTest(benchmark::State& state) 
{
    const char json[] = "{\"dvalue\" : -12.345,  \
                    \"fvalue\" : 1.234, \
                    \"ivalue\" : 42, \
                    \"lvalue\" : -142, \
                    \"svalue\" : \"abc\", \
                    \"vsvalue\" : [\"abc\",\"def\"], \
                    \"vdvalue\": [-23.4, 56.7, 8.9], \
                    \"vlvalue\": [0, -10, 100] \
                    }";

    RapidJsonHandler handler;
    Reader reader;
    for (auto _ : state)
    {
        StringStream ss(json);
        reader.Parse(ss, handler);
    }

}

BENCHMARK(BM_rapidjsonReadTest);

static void BM_xjsonReadTest(benchmark::State& state) 
{
    const char json[] = "{\"dvalue\" : -12.345,  \
                    \"fvalue\" : 1.234, \
                    \"ivalue\" : 42, \
                    \"lvalue\" : -142, \
                    \"svalue\" : \"abc\", \
                    \"vsvalue\" : [\"abc\",\"def\"], \
                    \"vdvalue\": [-23.4, 56.7, 8.9], \
                    \"vlvalue\": [0, -10, 100] \
                    }";
    TestJson obj;
    for (auto _ : state)
        str2obj(json, obj);
}

BENCHMARK(BM_xjsonReadTest);

static void BM_rapidjsonWriteTest(benchmark::State& state) 
{
    for (auto _ : state)
    {
        StringBuffer s;
        Writer<StringBuffer> writer(s);
        
        writer.StartObject();               
        writer.Key("dvalue");                
        writer.Double(-12.345);             
        writer.Key("fvalue");
        writer.Double(1.234);
        writer.Key("ivalue");
        writer.Int(42);
        writer.Key("lvalue");
        writer.Int64(-142);
        writer.Key("svalue");
        writer.String("abc");

        writer.Key("vsvalue");
        writer.StartArray();                
        writer.String("abc");
        writer.String("def");
        writer.EndArray();

        writer.Key("vdvalue");
        writer.StartArray();                
        writer.Double(-23.4);
        writer.Double(56.7);
        writer.Double(8.9);
        writer.EndArray();

        writer.Key("vlvalue");
        writer.StartArray();                
        writer.Int64(0);
        writer.Int64(-10);
        writer.Int64(100);
        writer.EndArray();

        writer.EndObject();
        benchmark::DoNotOptimize(s.GetString());
    }
}

BENCHMARK(BM_rapidjsonWriteTest);


static void BM_xjsonWriteTest(benchmark::State& state) 
{
    const char json[] = "{\"dvalue\" : -12.345,  \
                    \"fvalue\" : 1.234, \
                    \"ivalue\" : 42, \
                    \"lvalue\" : -142, \
                    \"svalue\" : \"abc\", \
                    \"vsvalue\" : [\"abc\",\"def\"], \
                    \"vdvalue\": [-23.4, 56.7, 8.9], \
                    \"vlvalue\": [0, -10, 100] \
                    }";
    TestJson obj;
    str2obj(json, obj);
    for (auto _ : state)
        benchmark::DoNotOptimize(obj2str(obj));
}

BENCHMARK(BM_xjsonWriteTest);


BENCHMARK_MAIN();
