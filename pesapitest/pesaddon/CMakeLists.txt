cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 11)

project (hello)

set(PUERTS_LIB_ROOT ../../puertstest/puerts)
set(PUERTS_INCLUDE ${PUERTS_LIB_ROOT}/include)
set(PESAPI_ROOT ../pesapiv8impl)
set(PESAPI_INCLUDE ${PESAPI_ROOT}/include)

file(GLOB SOURCE_FILES "src/hello.cc", "src/TestClass.cc")


include_directories(
    ${PESAPI_INCLUDE}
    ${PUERTS_INCLUDE} # for template support
    "src"
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} pesapi_adpt.c)

target_compile_definitions (${PROJECT_NAME} PRIVATE BUILDING_PES_EXTENSION) 
