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
    Cpp20/Enum.h
    Cpp20/MainArgs.h
    Cpp20/Templates.h
    Cpp20/Concepts.h
    Cpp20/Classes.h
    Cpp20/NameSpace.h
    Cpp20/MetaProgramming.h
    Cpp20/SmartPointers.h
    Cpp20/Overloading.h
    Cpp20/LogicalOperators.h
    Cpp20/Polymorphism.hpp
    Cpp20/ExceptionHandling.hpp
    Cpp20/ClassTemplate.hpp
    Cpp20/MoveSemantic.hpp
    Cpp20/BoxContainer.hpp
    Cpp20/FunctionEntity.hpp

    extern/cereal.hpp
    extern/rapidjson.hpp
    extern/fmt.hpp
    extern/named.hpp
    extern/is_optional.hpp
    extern/string_literal.hpp
    extern/spdlog.hpp

    stl/priority_queue.hpp
    stl/Trees.hpp

    effective_cpp/deducing_types.hpp
    effective_cpp/enable_if.hpp
    effective_cpp/futures.hpp

    TheModernCppChallenge/math_problem.hpp
    TheModernCppChallenge/language_features.hpp
    TheModernCppChallenge/StringAndRegularExperissions.hpp

    apple_interview/algorithms.hpp
    apple_interview/DataStructures.hpp

    replicated_codes/smart_pointers_packagedTask_Async.h

    multithreading/promise_future_packaged.hpp
    multithreading/concurrency.hpp
)

find_package(fmt REQUIRED)

target_compile_features(Cpp20TheCompleteGuide PRIVATE cxx_std_20)
target_link_libraries(Cpp20TheCompleteGuide
  PRIVATE
    fmt::fmt
)
