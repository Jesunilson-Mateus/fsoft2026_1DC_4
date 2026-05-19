add_executable(ProjectTester main_test.cpp)
target_link_libraries(ProjectTester PRIVATE PharmacyCore)

add_test(NAME ProjectTester COMMAND ProjectTester)
