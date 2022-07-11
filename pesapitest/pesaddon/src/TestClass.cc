#include "TestClass.h"
#include "Object.hpp"

void BaseClass::Foo(int p)
{
}

TestClass::TestClass()
{
	X = 0;
	Y = 0;
}

TestClass::TestClass(int32_t InX, int32_t InY)
{
	X = InX;
	Y = InY;
}

int32_t TestClass::Add(int32_t a, int32_t b)
{
	return a + b;
}

void TestClass::Overload()
{
}

void TestClass::Overload(int32_t a)
{
}

void TestClass::Overload(int32_t a, int32_t b)
{
}

void TestClass::Overload(std::string a, int32_t b)
{
}


int32_t TestClass::OverloadMethod()
{
	return 0;
}

int32_t TestClass::OverloadMethod(int32_t a)
{
	return 1;
}

uint32_t TestClass::OverloadMethod(uint32_t a)
{
	return a;
}

int64_t TestClass::OverloadMethod(int64_t a)
{
	return a;
}

TestClass * TestClass::GetSelf()
{
	return this;
}

void TestClass::PrintInfo(TestClass * tc)
{
}


int TestClass::Ref(int32_t & a)
{
	++a;
	return a + 1;
}

void TestClass::StrRef(std::string & str)
{
    str += " append by c++";
}

int TestClass::Ptr(int32_t * a)
{
    ++(*a);
    return *a + 1;
}

const char* TestClass::CStr(const char* str)
{
    return "hehe..";
}

void TestClass::StrPtr(std::string * str)
{
    *str += " append by c++";
}

void TestClass::ConstRef(const int32_t & a)
{
}

int TestClass::StaticInt = 0;

const float TestClass::Ten = 10;


AdvanceTestClass::AdvanceTestClass(int A)
{
}

void AdvanceTestClass::JsObjectTest(puerts::Object Obj)
{
    auto P = Obj.Get<int>("p");
    Obj.Set<std::string>("q", "john");
}

void AdvanceTestClass::CallJsObjectTest(puerts::Function Func)
{
    auto Ret = Func.Func<float>(1024, "che");
}

void AdvanceTestClass::StdFunctionTest(std::function<int(int, int)> Func)
{
    int Ret = Func(88, 99);
}
