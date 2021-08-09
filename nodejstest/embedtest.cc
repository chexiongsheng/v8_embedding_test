#include "node.h"
#include "uv.h"
#include <assert.h>
#include <iostream>
#include <string>

#include "Binding.hpp"
#include "CppObjectMapper.h"

// Note: This file is being referred to from doc/api/embedding.md, and excerpts
// from it are included in the documentation. Try to keep these in sync.

using node::CommonEnvironmentSetup;
using node::Environment;
using node::MultiIsolatePlatform;
using v8::Context;
using v8::HandleScope;
using v8::Isolate;
using v8::Locker;
using v8::MaybeLocal;
using v8::V8;
using v8::Value;


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

static int RunNodeInstance(MultiIsolatePlatform* platform,
                           const std::vector<std::string>& args,
                           const std::vector<std::string>& exec_args);

int main(int argc, char** argv) {
  argv = uv_setup_args(argc, argv);
  std::vector<std::string> args(argv, argv + argc);
  std::vector<std::string> exec_args;
  std::vector<std::string> errors;
  int exit_code = node::InitializeNodeWithArgs(&args, &exec_args, &errors);
  for (const std::string& error : errors)
    fprintf(stderr, "%s: %s\n", args[0].c_str(), error.c_str());
  if (exit_code != 0) {
    return exit_code;
  }

  std::unique_ptr<MultiIsolatePlatform> platform =
      MultiIsolatePlatform::Create(4);
  V8::InitializePlatform(platform.get());
  V8::Initialize();

  int ret = RunNodeInstance(platform.get(), args, exec_args);

  V8::Dispose();
  V8::ShutdownPlatform();
  return ret;
}

int RunNodeInstance(MultiIsolatePlatform* platform,
                    const std::vector<std::string>& args,
                    const std::vector<std::string>& exec_args) {
  int exit_code = 0;

  std::vector<std::string> errors;
  std::unique_ptr<CommonEnvironmentSetup> setup =
      CommonEnvironmentSetup::Create(platform, &errors, args, exec_args);
  if (!setup) {
    for (const std::string& err : errors)
      fprintf(stderr, "%s: %s\n", args[0].c_str(), err.c_str());
    return 1;
  }

  Isolate* isolate = setup->isolate();
  Environment* env = setup->env();

  {
    Locker locker(isolate);
    Isolate::Scope isolate_scope(isolate);
    HandleScope handle_scope(isolate);
    Context::Scope context_scope(setup->context());

    MaybeLocal<Value> loadenv_ret = node::LoadEnvironment(
        env,
        "const publicRequire ="
        "  require('module').createRequire(process.cwd() + '/');"
        "globalThis.require = publicRequire;"
        "globalThis.embedVars = { nön_ascıı: '🏳️‍🌈' };"
        "require('vm').runInThisContext(process.argv[1]);");

    if (loadenv_ret.IsEmpty())  // There has been a JS exception.
      return 1;

    exit_code = node::SpinEventLoop(env).FromMaybe(1);
    
    auto context = setup->context();
    puerts::FCppObjectMapper cppObjectMapper;
    cppObjectMapper.Initialize(isolate, context);
    isolate->SetData(MAPPER_ISOLATE_DATA_POS, static_cast<puerts::ICppObjectMapper*>(&cppObjectMapper));
    
    context->Global()->Set(context, v8::String::NewFromUtf8(isolate, "loadCppType").ToLocalChecked(), v8::FunctionTemplate::New(isolate, [](const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        auto pom = static_cast<puerts::FCppObjectMapper*>((v8::Local<v8::External>::Cast(info.Data()))->Value());
        pom->LoadCppType(info);
    }, v8::External::New(isolate, &cppObjectMapper))->GetFunction(context).ToLocalChecked()).Check();
    
    //注册
    puerts::DefineClass<TestClass>()
        .Constructor<int>()
        .Function("Print", MakeFunction(&TestClass::Print))
        .Property("X", MakeProperty(&TestClass::X))
        .Method("Add", MakeFunction(&TestClass::Add))
        .Register();
    
    {
        const char* csource = R"(
            const TestClass = loadCppType('TestClass');
            TestClass.Print('hello world');
            let obj = new TestClass(123);
            
            TestClass.Print(obj.X);
            obj.X = 99;
            TestClass.Print(obj.X);
            
            TestClass.Print('ret = ' + obj.Add(1, 3));
            
            const fs = require('fs');
            let info = fs.readdirSync('.');
            console.log(info);
          )";

        // Create a string containing the JavaScript source code.
        v8::Local<v8::String> source =
            v8::String::NewFromUtf8(isolate, csource)
            .ToLocalChecked();

        // Compile the source code.
        v8::Local<v8::Script> script =
            v8::Script::Compile(context, source).ToLocalChecked();

        // Run the script
        auto _unused = script->Run(context);
    }
    
    cppObjectMapper.UnInitialize(isolate);

    node::Stop(env);
  }

  return exit_code;
}
