var addon = require('bindings')('hello');

const TestClass = addon.loadCppType('TestClass');
TestClass.Print('hello world');
let obj = new TestClass(123);

TestClass.Print(obj.X);
obj.X = 99;
TestClass.Print(obj.X);

TestClass.Print('ret = ' + obj.Add(1, 3));