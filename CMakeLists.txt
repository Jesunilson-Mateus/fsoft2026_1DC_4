cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(PharmacyManagementSystem VERSION 1.0)

enable_testing()

# Add subdirectories for the main project and the tester
add_subdirectory(Project)

add_executable(PharmacyManagementSystemApp main.cpp)
target_link_libraries(PharmacyManagementSystemApp PRIVATE PharmacyCore)

add_subdirectory(ProjectTester)
