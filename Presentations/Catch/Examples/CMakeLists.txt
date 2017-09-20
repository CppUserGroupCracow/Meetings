project(CatchDemo)
cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_executable(main main.cpp animalsTest.cpp assertionsTest.cpp factorialTest.cpp floatsTest.cpp matchersTest.cpp fixturesTest.cpp)

target_link_libraries(main ${CONAN_LIBS})
