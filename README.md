# v8_embedding_test

《c++游戏服务器嵌入v8 js引擎胎教级教程》配套代码

# !!! 注意：本示例库较老旧，正式生产使用，应到puerts官网取最新库代码： https://github.com/Tencent/puerts

测试环境：Ubuntu

## v8下载

下载puerts编译好的配套[v8库](https://github.com/puerts/backend-v8/releases/tag/V8_8.4.371.19_0323)

解压到v8_embedding_test目录

## helloworld项目编译运行

~~~bash
cd helloworld
mkdir build
cd build
cmake ..
make

./helloworld
~~~

## puertstest项目编译运行

~~~bash
cd puertstest
mkdir build
cd build
cmake ..
make

./helloworld
~~~


## nodeaddon项目运行

~~~bash
cd nodeaddon
npm install .
node hello.js
~~~

## nodejstest项目运行

先编译libnode.so

~~~bash
git clone git@github.com:nodejs/node.git
cd node
./configure --shared
make -j4
~~~

拷贝nodejstest到node目录，拷贝puertstest/puerts目录到node/nodejstest目录

~~~bash
cd nodejstest
mkdir build
cd build
cmake ..
make

./embedtest
~~~

## pesapitest

由于动态库加载仅实现了window版本（见([PesapiAddonLoad.cpp]pesapitest/pesapiv8impl/src/PesapiAddonLoad.cpp)），所以只能在window下运行

编译
~~~bash
cd pesapitest\pesv8app
make_win64.bat
~~~

~~~bash
cd pesapitest\pesaddon
make_win64.bat
~~~

运行
~~~bash
cd pesapitest\pesv8app
build64_v8\Release\helloworld.exe
~~~

输出
~~~bash
wrap by hand begin
Inc1024
wrap by hand end
Inc2048
~~~

### 说明

* pesapitest\pesaddon是一个pesapi的扩展（动态库），理论上可以在任意实现了pesapi的环境运行，可以仅依赖于纯c的头文件pesapi.h以根据该头文件生成的pesapi_adpt.c文件。如果需要用c++模板绑定，则依赖puerts相关头文件。

* pesv8app是个可执行程序，其嵌入了v8，并基于v8实现了pesapi（见[PesapiV8Impl.cpp]pesapitest/pesapiv8impl/src/PesapiV8Impl.cpp)）

* pesv8app通过pesapi_load_addon加载了dll，然后就可以通过loadCppType加载注册的类


