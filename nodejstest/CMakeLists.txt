# Tencent is pleased to support the open source community by making xLua available.
# Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.
# Licensed under the MIT License (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
# http://opensource.org/licenses/MIT
# Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.

cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)

project(embedtest)


include_directories(
    ${CMAKE_SOURCE_DIR}/../src
    ${CMAKE_SOURCE_DIR}/../deps/v8/include
    ${CMAKE_SOURCE_DIR}/../deps/uv/include
    puerts/include
)

add_executable(embedtest embedtest.cc
          puerts/src/CppObjectMapper.cpp
          puerts/src/DataTransfer.cpp
          puerts/src/JSClassRegister.cpp)
          
#target_compile_definitions(embedtest PRIVATE MAPPER_ISOLATE_DATA_POS=2)

target_link_libraries(embedtest ${CMAKE_SOURCE_DIR}/../out/Release/libnode.so.95)