#include <pesapi.h>
#include <iostream>
#include <Binding.hpp>
#include "TestClass.h"

//cpp lib
class TestClass22 {
public:
    TestClass22(){
        std::cout << "TestClass22 " << this << std::endl;
        c = 0;
    }
    
    static int32_t Inc(int32_t p) {
        std::cout << "Inc " << p << std::endl;
        return p + 1;
    }
    
    int32_t Cpp() {
        std::cout << "Cpp " << c << std::endl;
        return c++;
    }
    
    ~TestClass22(){
        std::cout << "~TestClass22 " << this << std::endl;
    }
    
    int c;
};

//only depend on pesapi.h 
void Inc(pesapi_callback_info info) {
    std::cout << "wrap by hand begin" << std::endl;
    pesapi_env env = pesapi_get_env(info);
    int32_t i = pesapi_get_value_int32(env, pesapi_get_arg(info, 0));
    pesapi_add_return(info, pesapi_create_int32(env, TestClass22::Inc(i)));
    std::cout << "wrap by hand end" << std::endl;
}

void Init1() {
    pesapi_property_descriptor properties = pesapi_alloc_property_descriptors(1);
    pesapi_set_method_info(properties, 0, "Inc", true, Inc, nullptr, nullptr);
    pesapi_define_class("TestClass11", nullptr, "TestClass11", nullptr, nullptr, 1, properties, nullptr);
}

//cpp template
UsingCppType(TestClass22);
UsingCppType(BaseClass);
UsingCppType(TestClass);
UsingCppType(AdvanceTestClass);

void Init2() {
    puerts::DefineClass<TestClass22>()
        .Constructor()
        .Function("Inc", MakeFunction(&TestClass22::Inc))
        .Method("Cpp", MakeFunction(&TestClass22::Cpp))
        .Register();
        
    puerts::DefineClass<BaseClass>()
        .Method("Foo", MakeFunction(&BaseClass::Foo))
        .Register();

    puerts::DefineClass<TestClass>()
        .Extends<BaseClass>()
        //.Constructor<int32_t, int32_t>() //if only one Constructor
        .Constructor(CombineConstructors(
            MakeConstructor(TestClass, int32_t, int32_t),
            MakeConstructor(TestClass)
            ))
        .Property("X", MakeProperty(&TestClass::X))
        .Property("Y", MakeProperty(&TestClass::Y))
        .Variable("StaticInt", MakeVariable(&TestClass::StaticInt))
        .Variable("Ten", MakeReadonlyVariable(&TestClass::Ten))
        .Variable("IntArray", MakeReadonlyVariable(&TestClass::IntArray))
        .Function("Add", MakeFunction(&TestClass::Add))
        .Function("PrintInfo", MakeFunction(&TestClass::PrintInfo))
        .Method("GetSelf", MakeFunction(&TestClass::GetSelf))
        .Method("Ref", MakeFunction(&TestClass::Ref))
        .Method("StrRef", MakeFunction(&TestClass::StrRef))
        .Method("Ptr", MakeFunction(&TestClass::Ptr))
        .Method("CStr", MakeFunction(&TestClass::CStr))
        .Method("StrPtr", MakeFunction(&TestClass::StrPtr))
        .Method("ConstRef", MakeFunction(&TestClass::ConstRef))
        .Method("VoidPtr", MakeFunction(&TestClass::VoidPtr))
        .Function("Overload", CombineOverloads(
            MakeOverload(void(*)(), &TestClass::Overload),
            MakeOverload(void(*)(int32_t), &TestClass::Overload),
            MakeOverload(void(*)(int32_t, int32_t), &TestClass::Overload),
            MakeOverload(void(*)(std::string, int32_t), &TestClass::Overload)
            ))
        .Method("OverloadMethod", CombineOverloads(
            MakeOverload(int32_t(TestClass::*)(), &TestClass::OverloadMethod),
            MakeOverload(int32_t(TestClass::*)(int32_t), &TestClass::OverloadMethod),
            MakeOverload(uint32_t(TestClass::*)(uint32_t), &TestClass::OverloadMethod),
            MakeOverload(int64_t(TestClass::*)(int64_t), &TestClass::OverloadMethod)
            ))
        .Register();
        
    puerts::DefineClass<AdvanceTestClass>()
        .Constructor<int>() //if only one Constructor
        .Method("JsObjectTest", MakeFunction(&AdvanceTestClass::JsObjectTest))
        .Method("CallJsObjectTest", MakeFunction(&AdvanceTestClass::CallJsObjectTest))
        .Method("StdFunctionTest", MakeFunction(&AdvanceTestClass::StdFunctionTest))
        .Register();
}

void Init() {
    Init1();
    Init2();
}

PESAPI_MODULE(hello, Init)
