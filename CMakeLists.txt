cmake_minimum_required(VERSION 3.14)
project(MyProject LANGUAGES CXX)

# Устанавливаем современный стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================
# 1. АВТОМАТИЧЕСКОЕ ПОДКЛЮЧЕНИЕ GOOGLE TEST
# ==========================================
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Важно для Windows (MSVC): предотвращает конфликты настроек рантайма
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Скачиваем и подключаем gtest
FetchContent_MakeAvailable(googletest)

# ==========================================
# 2. ОСНОВНАЯ ПРОГРАММА (Папка samples)
# ==========================================
file(GLOB APP_SOURCES "samples/*.cpp")

if(APP_SOURCES)
    add_executable(my_app ${APP_SOURCES})
    # Подключаем папку include для основных исходников
    target_include_directories(my_app PRIVATE include)
endif()

# ==========================================
# 3. ТЕСТЫ (Папка test)
# ==========================================
enable_testing()

file(GLOB TEST_SOURCES "test/*.cpp")

if(TEST_SOURCES)
    add_executable(my_tests ${TEST_SOURCES})

    # Подключаем вашу папку include (если тесты тестируют ваш код)
    target_include_directories(my_tests PRIVATE include)

    # ВАЖНО: Используем GTest::gtest, а НЕ GTest::gtest_main, 
    # так как свой int main() у вас уже написан в test_main.cpp
    target_link_libraries(my_tests PRIVATE GTest::gtest)

    # Регистрируем тесты в CTest
    include(GoogleTest)
    add_test(NAME my_tests COMMAND my_tests)
endif()