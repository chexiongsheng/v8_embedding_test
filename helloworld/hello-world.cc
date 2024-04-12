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

#include "libplatform/libplatform.h"
#include "v8.h"

static void Print(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::Isolate* isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    std::string msg = *(v8::String::Utf8Value(isolate, info[0]->ToString(context).ToLocalChecked()));
    std::cout << msg << std::endl;
}

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
    {
        v8::Isolate::Scope isolate_scope(isolate);

        // Create a stack-allocated handle scope.
        v8::HandleScope handle_scope(isolate);

        // Create a new context.
        v8::Local<v8::Context> context = v8::Context::New(isolate);

        // Enter the context for compiling and running the hello world script.
        v8::Context::Scope context_scope(context);
        
        context->Global()->Set(context, v8::String::NewFromUtf8(isolate, "Print").ToLocalChecked(),
            v8::FunctionTemplate::New(isolate, Print)->GetFunction(context).ToLocalChecked())
            .Check();
            

        {
            const char* csource = R"(
                Print('hello world');
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

    }

    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;
    return 0;
}
