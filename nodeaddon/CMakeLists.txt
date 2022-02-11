cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 11)

project (hello)

set(PUERTS_LIB_ROOT ../puertstest/puerts)
set(PUERTS_INCLUDE ${PUERTS_LIB_ROOT}/include)
set(PUERTS_SRC
    ${PUERTS_LIB_ROOT}/src/CppObjectMapper.cpp
    ${PUERTS_LIB_ROOT}/src/DataTransfer.cpp
    ${PUERTS_LIB_ROOT}/src/JSClassRegister.cpp
)

include_directories(${CMAKE_JS_INC} ${PUERTS_INCLUDE})
file(GLOB SOURCE_FILES  "hello.cc" )

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC} ${PUERTS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

# define NPI_VERSION
add_definitions(-DNAPI_VERSION=3)