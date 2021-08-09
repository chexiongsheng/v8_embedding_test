# v8_embedding_test

《c++游戏服务器嵌入v8 js引擎胎教级教程》配套代码

测试环境：Ubuntu

## v8下载

下载puerts编译好的配套v8库：https://github.com/Tencent/puerts/releases/tag/V8_8.4.371.19_2021_07_27

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
