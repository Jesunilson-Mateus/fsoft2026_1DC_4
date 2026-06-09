set(PROJECT_HEADERS
    Mock/MockData.h
    headers/controllers/Controller.h
    headers/repo/IPharmacyRepository.h
    headers/repo/PharmacyRepositoryMemory.h
    headers/model/Entidades/Data.h
    headers/model/Entidades/Funcionario.h
    headers/model/Entidades/Gestor.h
    headers/model/Entidades/Medicamento.h
    headers/model/Entidades/Produto.h
    headers/model/Entidades/Receita.h
    headers/model/Entidades/Venda.h
)

set(PROJECT_SOURCES
    Mock/MockData.cpp
    sources/Controller/Controllers.cpp
    sources/repo/PharmacyRepositoryMemory.cpp
    sources/model/Entidades/Data.cpp
    sources/model/Entidades/Funcionario.cpp
    sources/model/Entidades/Gestor.cpp
    sources/model/Entidades/Medicamento.cpp
    sources/model/Entidades/Produto.cpp
    sources/model/Entidades/Receita.cpp
    sources/model/Entidades/Venda.cpp
)

add_library(PharmacyCore ${PROJECT_HEADERS} ${PROJECT_SOURCES})

target_include_directories(PharmacyCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/repo
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/model/Entidades
)

target_compile_features(PharmacyCore PUBLIC cxx_std_11)
