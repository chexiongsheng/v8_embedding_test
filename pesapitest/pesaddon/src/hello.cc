#include <pesapi.h>
#include <iostream>
#include <Binding.hpp>

//cpp lib
class TestClass22 {
public:
    static int32_t Inc(int32_t p) {
        std::cout << "Inc" << p << std::endl;
        return p + 1;
    }
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
    static pesapi_property_descriptor properties[] = 
    {
        { "Inc", true, Inc},
    };
    pesapi_define_class("TestClass11", nullptr, "TestClass11", nullptr, nullptr, 1, properties);
}

//cpp template
UsingCppType(TestClass22);

void Init2() {
    puerts::DefineClass<TestClass22>()
        .Function("Inc", MakeFunction(&TestClass22::Inc))
        .Register();
}

void Init() {
    Init1();
    Init2();
}

PESAPI_MODULE(hello, Init)
