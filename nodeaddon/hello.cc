#include <node.h>
#include <iostream>
#include "Binding.hpp"
#include "CppObjectMapper.h"

class TestClass
{
public:
    TestClass(int p) {
        std::cout << "TestClass(" << p << ")" << std::endl;
        X = p;
    }

    static void Print(std::string msg) {
        std::cout << msg << std::endl;
    }
    
    int Add(int a, int b)
    {
        std::cout << "Add(" << a << "," << b << ")" << std::endl;
        return a + b;
    }
    
    int X;
};

UsingCppType(TestClass);


NODE_MODULE_INIT(/* exports, module, context */) {
  auto isolate = context->GetIsolate();
  
  //TODO: 多addon有两个问题要解决，一个是目前注册JSClassRegister注册数据是放在静态变量，多addon每个addon一份并不共享，其次是FCppObjectMapper如何保持不冲突
  puerts::FCppObjectMapper *cppObjectMapper = new puerts::FCppObjectMapper();
  cppObjectMapper->Initialize(isolate, context);
  isolate->SetData(MAPPER_ISOLATE_DATA_POS, static_cast<puerts::ICppObjectMapper*>(cppObjectMapper));
      
  exports->Set(context, v8::String::NewFromUtf8(isolate, "loadCppType").ToLocalChecked(), v8::FunctionTemplate::New(isolate, [](const v8::FunctionCallbackInfo<v8::Value>& info)
  {
    auto pom = static_cast<puerts::FCppObjectMapper*>((v8::Local<v8::External>::Cast(info.Data()))->Value());
    pom->LoadCppType(info);
  }, v8::External::New(isolate, cppObjectMapper))->GetFunction(context).ToLocalChecked()).Check();
  
  //这个初始化函数，前面都是固定的，从这开始和业务有关
  
  puerts::DefineClass<TestClass>()
    .Constructor<int>()
    .Function("Print", MakeFunction(&TestClass::Print))
    .Property("X", MakeProperty(&TestClass::X))
    .Method("Add", MakeFunction(&TestClass::Add))
    .Register();
}

