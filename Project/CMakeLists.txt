set(PROJECT_HEADERS
    Mock/MockData.h
    headers/controllers/Controller.h
    headers/exceptions/DataConsistencyException.h
    headers/exceptions/DuplicatedDataException.h
    headers/exceptions/InvalidDataException.h
    headers/exceptions/NoDataException.h
    headers/repo/IRepositorioFarmacia.h
    headers/repo/RepositorioFarmaciaMemoria.h
    headers/model/Entidades/Cliente.h
    headers/model/Entidades/Data.h
    headers/model/Entidades/Funcionario.h
    headers/model/Entidades/Gestor.h
    headers/model/Entidades/Medicamento.h
    headers/model/Entidades/Produto.h
    headers/model/Entidades/Receita.h
    headers/model/Entidades/Venda.h
    headers/views/ClienteView.h
    headers/views/FuncionarioView.h
    headers/views/ProdutoView.h
    headers/views/RelatorioView.h
    headers/views/StockView.h
    headers/views/Utils.h
    headers/views/VendaView.h
    headers/views/Views.h
)

set(PROJECT_SOURCES
    Mock/MockData.cpp
    sources/Controller/Controllers.cpp
    sources/Exceptions/DataConsistencyException.cpp
    sources/Exceptions/DuplicatedDataException.cpp
    sources/Exceptions/InvalidDataException.cpp
    sources/Exceptions/NoDataException.cpp
    sources/repo/RepositorioFarmaciaMemoria.cpp
    sources/model/Entidades/Cliente.cpp
    sources/model/Entidades/Data.cpp
    sources/model/Entidades/Funcionario.cpp
    sources/model/Entidades/Gestor.cpp
    sources/model/Entidades/Medicamento.cpp
    sources/model/Entidades/Produto.cpp
    sources/model/Entidades/Receita.cpp
    sources/model/Entidades/Venda.cpp
    sources/views/ClienteView.cpp
    sources/views/FuncionarioView.cpp
    sources/views/ProdutoView.cpp
    sources/views/RelatorioView.cpp
    sources/views/StockView.cpp
    sources/views/Utils.cpp
    sources/views/VendaView.cpp
    sources/views/View.cpp
)

add_library(PharmacyCore ${PROJECT_HEADERS} ${PROJECT_SOURCES})

target_include_directories(PharmacyCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/exceptions
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/repo
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/model/Entidades
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/views
)

target_compile_features(PharmacyCore PUBLIC cxx_std_11)
