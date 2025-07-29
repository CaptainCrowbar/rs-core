cmake_minimum_required(VERSION 3.30)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# The version number here is the canonical one for the project. Run
# bump-version to increment the patch number and propagate the new version to
# version.hpp.

project(rs-core
    VERSION 0.1.88
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS=1)
    add_compile_options(/EHsc /Gy /MP /O2 /sdl /utf-8 /W4 /WX)
else()
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
    add_compile_options(-fdiagnostics-color=always -finput-charset=UTF-8 -march=native -O2
        -Wall -Wextra -Wpedantic -Werror -Wconversion -Wshadow)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_compile_options(-Wsuggest-override -Wsuggest-destructor-override)
    endif()
endif()

if(WIN32)
    add_compile_definitions(NOMINMAX=1 UNICODE=1 _UNICODE=1 WINVER=0xa00 _WIN32_WINNT=0xa00)
else()
    add_compile_definitions(_REENTRANT=1 _XOPEN_SOURCE=700)
    if(APPLE)
        add_compile_definitions(_DARWIN_C_SOURCE=1)
    endif()
endif()

find_package(Threads REQUIRED)
include_directories(.)
set(library rs-core)
set(unittest test-rs-core)

add_executable(${unittest}

    test/global-test.cpp
    test/alias-test.cpp
    test/arithmetic-parsing-test.cpp
    test/arithmetic-test.cpp
    test/character-test.cpp
    test/constants-test.cpp
    test/enum-test.cpp
    test/format-test.cpp
    test/hash-test.cpp
    test/io-test.cpp
    test/iterator-test.cpp
    test/log-test.cpp
    test/markup-test.cpp
    test/mp-integer-sign-agnostic-test.cpp
    test/mp-integer-signed-arithmetic-test.cpp
    test/mp-integer-signed-conversion-test.cpp
    test/mp-integer-unsigned-arithmetic-test.cpp
    test/mp-integer-unsigned-conversion-test.cpp
    test/random-algorithm-test.cpp
    test/random-engine-test.cpp
    test/random-float-test.cpp
    test/random-integer-test.cpp
    test/rational-int-test.cpp
    test/rational-mp-integer-basics-test.cpp
    test/rational-mp-integer-maths-addition-subtraction-test.cpp
    test/rational-mp-integer-maths-division-test.cpp
    test/rational-mp-integer-maths-multiplication-test.cpp
    test/rational-mp-integer-string-conversion-test.cpp
    test/scope-test.cpp
    test/terminal-test.cpp
    test/typename-test.cpp
    test/uuid-test.cpp
    test/version-test.cpp
    test/unit-test.cpp

)

target_link_libraries(${unittest}
    PRIVATE Threads::Threads
)

install(DIRECTORY ${library} DESTINATION include)
