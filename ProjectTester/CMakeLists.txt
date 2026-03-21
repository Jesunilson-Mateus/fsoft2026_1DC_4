# CMakeLists.txt for ProjectTester

cmake_minimum_required(VERSION 3.10)

# Project name
project(ProjectTester)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable testing
enable_testing()

# Add test executable
add_executable(ProjectTester test_main.cpp)

# Add tests
add_test(NAME Test1 COMMAND ProjectTester)
