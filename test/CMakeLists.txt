cmake_minimum_required(VERSION 3.14)

project(frequencyppTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/windows-set-path.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake)

if(PROJECT_IS_TOP_LEVEL)
    find_package(frequencypp REQUIRED)
    include(CTest)
endif()

find_package(Catch2 REQUIRED)
include(Catch)

add_executable(frequencypp_test
    source/frequencypp_test.cpp
)
target_link_libraries(frequencypp_test
    PRIVATE
    Catch2::Catch2
    frequencypp::frequencypp
)
target_compile_features(frequencypp_test
    PRIVATE
    cxx_std_17
)

catch_discover_tests(frequencypp_test)
