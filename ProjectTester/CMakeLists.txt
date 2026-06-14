include(FetchContent)

find_package(GTest CONFIG QUIET)

if(NOT GTest_FOUND)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(ProjectTester
    main_test.cpp
    ProdutoTest.cpp
    ClienteTest.cpp
    FuncionarioTest.cpp
    ControllerTest.cpp
    VendaTest.cpp
    RelatorioTest.cpp
)
target_link_libraries(ProjectTester PRIVATE PharmacyCore GTest::gtest)

add_test(NAME ProjectTester COMMAND ProjectTester)
