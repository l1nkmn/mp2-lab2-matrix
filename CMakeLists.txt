cmake_minimum_required(VERSION 3.14)
project(mp2-lab1-set LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# =====================================================================
# 1) GTest как статическая библиотека (fused-версия: один gtest-all.cc)
# =====================================================================
add_library(gtest STATIC gtest/gtest-all.cc)

# gtest-all.cc делает #include "gtest.h", поэтому include-path должен
# указывать на папку gtest/. А тестам нужен #include <gtest/gtest.h>
# или #include "gtest/gtest.h" — на всякий случай даём оба пути.
target_include_directories(gtest PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest
)

# Гасим предупреждения в чужом коде
target_compile_options(gtest PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-w>
    $<$<CXX_COMPILER_ID:MSVC>:/w>
)

# =====================================================================
# 2) Пример использования (samples/sample_matrix.cpp) — отдельный exe
# =====================================================================
add_executable(sample_matrix samples/sample_matrix.cpp)
target_include_directories(sample_matrix PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest
)

# =====================================================================
# 3) Тесты
# =====================================================================
enable_testing()

add_executable(run_tests
    test/test_main.cpp
    test/test_tmatrix.cpp
    test/test_tvector.cpp
)

target_include_directories(run_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest
)

target_link_libraries(run_tests PRIVATE gtest)

include(GoogleTest)
gtest_discover_tests(run_tests)
