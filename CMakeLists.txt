cmake_minimum_required(VERSION 3.16)

project(Cpp20TheCompleteGuide LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER /usr/bin/gcc-11)
set(CMAKE_CXX_COMPILER /usr/bin/g++-11)
#set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

add_executable(Cpp20TheCompleteGuide
    main.cpp
    Enum.h
    MainArgs.h
    Templates.h
    Concepts.h
    Classes.h
    NameSpace.h
    MetaProgramming.h
    SmartPointers.h
    Overloading.h
    LogicalOperators.h
    Polymorphism.hpp
    ExceptionHandling.hpp

    extern/cereal.hpp
    extern/rapidjson.hpp
    extern/fmt.hpp
    extern/named.hpp
    extern/is_optional.hpp
    extern/string_literal.hpp
    extern/spdlog.hpp

    stl/priority_queue.hpp
    stl/Trees.hpp
)

find_package(fmt REQUIRED)

target_compile_features(Cpp20TheCompleteGuide PRIVATE cxx_std_20)
target_link_libraries(Cpp20TheCompleteGuide
  PRIVATE
    fmt::fmt
)
