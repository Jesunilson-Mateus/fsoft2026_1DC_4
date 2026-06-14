add_executable(ProjectTester
    main_test.cpp
    ProdutoTest.cpp
    ClienteTest.cpp
    FuncionarioTest.cpp
    ControllerTest.cpp
    VendaTest.cpp
    RelatorioTest.cpp
)
target_link_libraries(ProjectTester PRIVATE PharmacyCore)

add_test(NAME ProjectTester COMMAND ProjectTester)
