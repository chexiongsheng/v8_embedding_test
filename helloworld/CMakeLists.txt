cmake_minimum_required(VERSION 2.8)

if ( WIN32 AND NOT CYGWIN AND NOT ( CMAKE_SYSTEM_NAME STREQUAL "WindowsStore" ) AND NOT ANDROID)
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT" CACHE STRING "")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd" CACHE STRING "")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT" CACHE STRING "")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd" CACHE STRING "")
endif ()

project(Helloworld)

set (CMAKE_CXX_STANDARD 14)


set(JS_ENGINE_ROOT ${CMAKE_SOURCE_DIR}/../v8)

include_directories(
    ${JS_ENGINE_ROOT}/Inc
)

set ( SRC hello-world.cc)

add_executable(helloworld ${SRC})

set (LIB_NAME wee8)

if ( ANDROID )
    find_library(log-lib log )

    if( ANDROID_ABI STREQUAL "armeabi-v7a")
        target_link_libraries(helloworld
            ${JS_ENGINE_ROOT}/Lib/Android/armv7/lib${LIB_NAME}.a
            ${log-lib}
        )
        target_compile_definitions (helloworld PRIVATE PLATFORM_ANDROID_ARM)
    else ( )
        target_link_libraries(helloworld
            ${JS_ENGINE_ROOT}/Lib/Android/arm64/lib${LIB_NAME}.a
            ${log-lib}
        )
        target_compile_definitions (helloworld PRIVATE PLATFORM_ANDROID_ARM64)
    endif ( )
elseif ( APPLE )
    if (IOS)
        target_link_libraries(helloworld
            ${JS_ENGINE_ROOT}/Lib/iOS/lib${LIB_NAME}.a
        )
        target_compile_definitions (helloworld PRIVATE PLATFORM_IOS)
    else ()
        target_link_libraries(helloworld
            ${JS_ENGINE_ROOT}/Lib/macOS/lib${LIB_NAME}.a
        )
        target_compile_definitions (helloworld PRIVATE PLATFORM_MAC)
    endif ( )
elseif (UNIX)
    target_link_libraries(helloworld
        ${JS_ENGINE_ROOT}/Lib/Linux/lib${LIB_NAME}.a
	    pthread
    )
    target_compile_definitions (helloworld PRIVATE PLATFORM_LINUX)
    set(CMAKE_CXX_COMPILER "clang++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
else ()
    if ( JS_ENGINE STREQUAL "v8")
        set(LIBS_NEEDED winmm.lib dbghelp.lib shlwapi.lib)
    endif()
    if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
        target_link_libraries(hello-world
            ${JS_ENGINE_ROOT}/Lib/Win32/${LIB_NAME}.lib
            ${LIBS_NEEDED}
        )
    else ()
        target_link_libraries(helloworld
            ${JS_ENGINE_ROOT}/Lib/Win64/${LIB_NAME}.lib
            ${LIBS_NEEDED}
        )
    endif ()
    target_compile_definitions (helloworld PRIVATE PLATFORM_WINDOWS)
endif ( )
