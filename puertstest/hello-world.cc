// Copyright 2015 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <map>
#include <string>
#include <limits>

#include "Binding.hpp"
#include "CppObjectMapper.h"

#include "libplatform/libplatform.h"
#include "v8.h"

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


int main(int argc, char* argv[]) {
    // Initialize V8.
    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.get());
    v8::V8::Initialize();

    // Create a new Isolate and make it the current one.
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator =
        v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    v8::Isolate* isolate = v8::Isolate::New(create_params);
    
    puerts::FCppObjectMapper cppObjectMapper;
    {
        v8::Isolate::Scope isolate_scope(isolate);

        // Create a stack-allocated handle scope.
        v8::HandleScope handle_scope(isolate);

        // Create a new context.
        v8::Local<v8::Context> context = v8::Context::New(isolate);

        // Enter the context for compiling and running the hello world script.
        v8::Context::Scope context_scope(context);
        
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

    }

    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;
    return 0;
}
