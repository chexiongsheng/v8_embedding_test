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

static void Print1(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::Isolate* isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    int *p = (int*)v8::Local<v8::External>::Cast(info.Data())->Value();
    if (p) {
        std::cout << "p=[" << p[0] << ", " << p[1] << ", " << p[2] <<  "]" << std::endl;
    } else {
        std::cout << "p=null" << std::endl;
    }
    
    std::string msg = *(v8::String::Utf8Value(isolate, info[0]->ToString(context).ToLocalChecked()));
    std::cout << "Print1:" << msg << std::endl;
}

static void Print2(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::Isolate* isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    int *p = (int*)v8::Local<v8::External>::Cast(info.Data())->Value();
    if (p) {
        std::cout << "p=[" << p[0] << ", " << p[1] << ", " << p[2] <<  "]" << std::endl;
    } else {
        std::cout << "p=null" << std::endl;
    }
    
    std::string msg = *(v8::String::Utf8Value(isolate, info[0]->ToString(context).ToLocalChecked()));
    std::cout << "Print2:" << msg << std::endl;
}

v8::StartupData SerializeInternalFields(v8::Local<v8::Object> holder,
                                    int index,
                                    void* data) {
  std::vector<int>* s = static_cast<std::vector<int>*>(holder->GetAlignedPointerFromInternalField(index));
  if (s) {
      std::cout << "SerializeInternalFields index: " << index
                << ", ver[0]: " << (*s)[0]  << std::endl;


      int* payload = new int[s->size() + 1];
      int arr_size = s->size() * sizeof(int);
      int size = (s->size() + 1) * sizeof(int);
      payload[0] = (int)s->size();
      memcpy(payload + 1, s->data(), arr_size);
      std::cout << "SerializeInternalFields payload size: " << size << std::endl;
      std::cout << "ptr of InternalField:" << s << std::endl;
      return {(char*)payload, size};
      //return {nullptr, 0}; // 不会调用DeserializeInternalFields，但GetAlignedPointerFromInternalField会返回非空值，返回的是之前指针“值”
  } else {
      void* p = (*((void**)*holder));
      
      if (!holder->IsArrayBufferView() && !holder->IsArrayBuffer()) {
          std::cout << "no data, SerializeInternalFields index: " << index << ",ptr=" << p << std::endl;
      }
      
      //一个Int8Array会有两个对象，一个是ArrayBufferView，一个是ArrayBuffer，每个都有两个InternalFields
      //如果是js中new的，不用管，会自动序列化过去
      if (holder->IsArrayBufferView()) {
          std::cout << "ArrayBufferView index: " << index << ",ptr=" << p << std::endl;
      }
      if (holder->IsArrayBuffer()) {
          std::cout << "ArrayBuffer index: " << index << ",ptr=" << p << std::endl;
      }
      return {nullptr, 0};
  }
}

void DeserializeInternalFields(v8::Local<v8::Object> holder,
                               int index,
                               v8::StartupData payload,
                               void* data) {
  std::cout << "DeserializeInternalFields payload size: " << payload.raw_size << '\n';
  std::vector<int>* s = new std::vector<int>();
  int* buffer = (int*)payload.data;
  int size = buffer[1];
  s->insert(s->end(), buffer + 1, buffer + 1 + buffer[1]);
  
  std::cout << "DeserializeInternalFields vec.size: " << s->size() << ", ver[0]: " << (*s)[0] << '\n';
  holder->SetAlignedPointerInInternalField(index, s);
}

int main(int argc, char* argv[]) {

    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.get());
    v8::V8::Initialize();
    size_t context_index;
    v8::StartupData cross_data;
    
    v8::SerializeInternalFieldsCallback si_cb = v8::SerializeInternalFieldsCallback(
      SerializeInternalFields, nullptr);

    {
        v8::Isolate* isolate = v8::Isolate::Allocate();
        
        {
            std::vector<intptr_t> external_refs;
            external_refs.reserve(100); //make external_refs.data do not change
            external_refs.push_back(reinterpret_cast<intptr_t>(Print2));
            external_refs.push_back(reinterpret_cast<intptr_t>(Print1));
            //看v8的处理，external_refs以nullptr作为结尾
            
            v8::StartupData SnapshotBlob;
            SnapshotBlob.data = (const char *)SnapshotBlobCode;
            SnapshotBlob.raw_size = sizeof(SnapshotBlobCode);
            
            v8::SnapshotCreator snapshot_creator(isolate, external_refs.data(), &SnapshotBlob);
            std::cout << "external_refs.data()=" << external_refs.data() << std::endl;
            std::vector<int> s;
            s.push_back(1);
            {

                v8::Isolate::Scope isolate_scope(isolate);
                
                // Create a stack-allocated handle scope.
                v8::HandleScope handle_scope(isolate);

                // Create a new context.
                v8::Local<v8::Context> context = v8::Context::New(isolate);
                

                // Enter the context for compiling and running the hello world script.
                v8::Context::Scope context_scope(context);
                
                int * p = new int[] {1, 2, 3};
                external_refs.push_back(reinterpret_cast<intptr_t>(p));
                std::cout << "external_refs.data()=" << external_refs.data() << std::endl;
                
                context->Global()->Set(context, v8::String::NewFromUtf8Literal(isolate, "Print"),
                    v8::FunctionTemplate::New(isolate, Print1, v8::External::New(isolate, p))->GetFunction(context).ToLocalChecked())
                    .Check();
                    
                uint8_t * buff = new uint8_t[3] {6, 7, 8};
                
                auto backing = v8::ArrayBuffer::NewBackingStore(
                    buff, 3,
                    [](void* Data, size_t Length, void* DeleterData)
                    {
                        uint8_t * b = (uint8_t *)Data;
                        std::cout << "delete " << (void*)b << std::endl;
                        delete b;
                    }, nullptr);
                
                auto ab = v8::ArrayBuffer::New(isolate, std::move(backing));
                
                void* abp = (*((void**)*ab));
                std::cout << "abp:" << abp << std::endl;
                
                context->Global()->Set(context, v8::String::NewFromUtf8Literal(isolate, "ab"), ab)
                    .Check();
                    
                //int * p2 = new int[] {1, 2, 3};
                //如果External p2, 会报Unknown external reference，也就是同一个外部指针可以用多次
                context->Global()->Set(context, v8::String::NewFromUtf8Literal(isolate, "Print2"),
                    v8::FunctionTemplate::New(isolate, Print2, v8::External::New(isolate, p))->GetFunction(context).ToLocalChecked())
                    .Check();

                {
                    const char* csource = R"(
                        Print('hello world');
                        int8arr = new Int8Array(2);
                        int8arr[0] = 10;
                        int8arr[1] = 42;
                        
                        (function(){
                            const aba = new Int8Array(ab);
                            Print(`aba.length=${aba.length}, aba[0,1]=[${aba[0]}, ${aba[1]}]`);
                        })();
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
                
                auto objTemplate = v8::ObjectTemplate::New(isolate);
                objTemplate->SetInternalFieldCount(1);
                auto obj = objTemplate->NewInstance(context).ToLocalChecked();
                //std::vector<int> s; //放这里局部变量析构了，序列化时就是无效内存了，说明序列化操作是在CreateBlob时操作的，而不是AddContext
                //s.push_back(1);
                obj->SetAlignedPointerInInternalField(0, static_cast<void*>(&s));
                context->Global()->Set(context, v8::String::NewFromUtf8Literal(isolate, "something"), obj).Check();
                
                // SetDefaultContext mush be call
                //snapshot_creator.SetDefaultContext(v8::Context::New(isolate)); //cross_data.raw_size=58486
                //context_index = snapshot_creator.AddContext(context, si_cb); //对应v8::Context::FromSnapshot
                
                snapshot_creator.SetDefaultContext(context, si_cb);// 对应v8::Context::New
            }
            
            std::cout << "create blob...." << std::endl;
            // Must be out of HandleScope
            cross_data = snapshot_creator.CreateBlob(v8::SnapshotCreator::FunctionCodeHandling::kKeep);
            std::cout << "cross_data.raw_size=" << cross_data.raw_size << ", context_index=" << context_index << std::endl;
        }

        // Dispose will crash, managed by SnapshotCreator
        //isolate->Dispose();
        
    }
    
    v8::DeserializeInternalFieldsCallback di_cb = v8::DeserializeInternalFieldsCallback(
      DeserializeInternalFields, nullptr);
    
    {
        std::vector<intptr_t> external_refs;
        external_refs.push_back(reinterpret_cast<intptr_t>(Print1));
        external_refs.push_back(reinterpret_cast<intptr_t>(Print2));
        int * p = new int[] {1, 2, 3};
        external_refs.push_back(reinterpret_cast<intptr_t>(p)); // 假如不给值，Data获取到的是空，个人推测是直接获取external_refs.data()[1]，因为本来就没给长度，这样会越界读，毕竟危险
        
        v8::Isolate* isolate = v8::Isolate::Allocate();
        
        v8::SnapshotCreator snapshot_creator(isolate, external_refs.data(), &cross_data);

        v8::Isolate::Scope isolate_scope(isolate);
        
        // Create a stack-allocated handle scope.
        v8::HandleScope handle_scope(isolate);

        // Create a new context.
        //v8::Local<v8::Context> context = v8::Context::FromSnapshot(isolate, context_index, di_cb).ToLocalChecked();
        v8::Local<v8::Context> context = v8::Context::New(isolate, nullptr, v8::MaybeLocal<v8::ObjectTemplate>(), v8::MaybeLocal<v8::Value>(), di_cb);
        

        // Enter the context for compiling and running the hello world script.
        v8::Context::Scope context_scope(context);


        {
            v8::TryCatch try_catch(isolate);
            const char* csource = R"(
                Print('hello world');
                Print(`int8arr.length=${int8arr.length}, int8arr[0,1]=[${int8arr[0]}, ${int8arr[1]}]`);
                
                (function() {
                    const aba = new Int8Array(ab);
                    Print(`aba.length=${aba.length}, aba[0,1]=[${aba[0]}, ${aba[1]}]`);
                })();
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
            std::cout << "try_catch.HasCaught():" << try_catch.HasCaught() << std::endl;
        }
        
        auto val = context->Global()->Get(context, v8::String::NewFromUtf8Literal(isolate, "something")).ToLocalChecked();

        auto obj = v8::Local<v8::Object>::Cast(val);
        
        std::cout << "obj->InternalFieldCount(): " << obj->InternalFieldCount() << std::endl;
        
        std::vector<int>* ptr = static_cast<std::vector<int>*>(obj->GetAlignedPointerFromInternalField(0));
        if (ptr) {
            std::cout << "ptr of InternalField:" << ptr << std::endl;
            std::cout << "InternalField vec.size: " << ptr->size() << ", ver[0]: " << (*ptr)[0] << '\n';
        } else { 
            std::cout << "InternalField is null" << std::endl;
        }
        
    }
    
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
    return 0;
}
