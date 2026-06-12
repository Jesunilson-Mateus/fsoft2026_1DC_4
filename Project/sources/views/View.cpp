#include "../../headers/views/Views.h"
#include "../../headers/exceptions/DataConsistencyException.h"
#include "../../headers/exceptions/DuplicatedDataException.h"
#include "../../headers/exceptions/InvalidDataException.h"
#include "../../headers/exceptions/NoDataException.h"
#include "../../headers/views/ClienteView.h"
#include "../../headers/views/FuncionarioView.h"
#include "../../headers/views/ProdutoView.h"
#include "../../headers/views/RelatorioView.h"
#include "../../headers/views/StockView.h"
#include "../../headers/views/Utils.h"
#include "../../headers/views/VendaView.h"
#include <iostream>
#include <stdexcept>

void Views::iniciarSessao(Controller& controller) {
    while (controller.getUtilizadorAutenticado() == nullptr) {
        std::cout << "\nCredenciais de teste: gestora/1234 ou joao/abcd\n";
        std::string username = Utils::lerTexto("Username: ");
        std::string password = Utils::lerTexto("Password: ");

        if (controller.autenticar(username, password) == nullptr) {
            std::cout << "Credenciais invalidas.\n";
        }
    }

    std::cout << "Sessao iniciada como "
              << controller.getUtilizadorAutenticado()->getNome()
              << " (" << controller.getUtilizadorAutenticado()->getCargo() << ").\n";
}

void Views::mostrarMenu(const Controller& controller, const std::string& nomeFarmacia) {
    std::cout << "\n=== Sistema de Gestao de Farmacia - " << nomeFarmacia << " ===\n";
    std::cout << "1 - Listar produtos/stock\n";
    std::cout << "2 - Registar venda\n";
    std::cout << "3 - Listar receitas\n";
    std::cout << "4 - Listar clientes\n";

    if (controller.utilizadorEhGestor()) {
        std::cout << "5 - Gerir stock\n";
        std::cout << "6 - Gestao dos funcionarios\n";
        std::cout << "9 - Gerir relatorios\n";
        std::cout << "10 - Terminar sessao\n";
    } else {
        std::cout << "9 - Terminar sessao\n";
    }

    std::cout << "0 - Sair\n";
}

void Views::executar(Controller& controller, const std::string& ficheiroStock) {
    std::cout << "Sistema de Gestao de Farmacia\n";
    std::string nomeFarmacia = Utils::lerTexto("Nome da farmacia: ");
    if (nomeFarmacia.empty()) {
        nomeFarmacia = "Farmacia";
    }

    bool sair = false;
    while (!sair) {
        try {
            if (controller.getUtilizadorAutenticado() == nullptr) {
                iniciarSessao(controller);
            }

            mostrarMenu(controller, nomeFarmacia);
            int opcao = Utils::lerInteiro("Opcao: ");

            switch (opcao) {
                case 1:
                    ProdutoView::listarProdutos(controller);
                    break;
                case 2:
                    VendaView::registarVenda(controller, ficheiroStock);
                    break;
                case 3:
                    VendaView::listarReceitas(controller);
                    break;
                case 4:
                    ClienteView::listarClientes(controller);
                    break;
                case 5:
                    if (controller.utilizadorEhGestor()) {
                        StockView::gerirStock(controller, ficheiroStock);
                    } else {
                        std::cout << "Opcao invalida.\n";
                    }
                    break;
                case 6:
                    if (controller.utilizadorEhGestor()) {
                        FuncionarioView::gerirFuncionarios(controller);
                    } else {
                        std::cout << "Opcao invalida.\n";
                    }
                    break;
                case 9:
                    if (controller.utilizadorEhGestor()) {
                        RelatorioView::gerirRelatorios(controller);
                    } else {
                        controller.terminarSessao();
                        std::cout << "Sessao terminada.\n";
                    }
                    break;
                case 10:
                    if (controller.utilizadorEhGestor()) {
                        controller.terminarSessao();
                        std::cout << "Sessao terminada.\n";
                    } else {
                        std::cout << "Opcao invalida.\n";
                    }
                    break;
                case 0:
                    sair = true;
                    break;
                default:
                    std::cout << "Opcao invalida.\n";
                    break;
            }
        } catch (const InvalidDataException& erro) {
            std::cout << "Erro - Dados invalidos: " << erro.what() << "\n";
        } catch (const NoDataException& erro) {
            std::cout << "Erro - Dados nao encontrados: " << erro.what() << "\n";
        } catch (const DataConsistencyException& erro) {
            std::cout << "Erro - Inconsistencia de dados: " << erro.what() << "\n";
        } catch (const DuplicatedDataException& erro) {
            std::cout << "Erro - Dados duplicados: " << erro.what() << "\n";
        } catch (const std::exception& erro) {
            std::cout << "Erro desconhecido: " << erro.what() << "\n";
        }
    }

    std::cout << "Programa terminado.\n";
}
