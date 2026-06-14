#ifndef PROJECTTESTER_TESTUTILS_H
#define PROJECTTESTER_TESTUTILS_H

#include "../Project/headers/controllers/Controller.h"
#include "../Project/headers/repo/RepositorioFarmaciaMemoria.h"
#include <gtest/gtest.h>

struct AmbienteController {
    RepositorioFarmaciaMemoria repositorio;
    Controller controller;

    AmbienteController() : repositorio(), controller(&repositorio) {}
};

#endif // PROJECTTESTER_TESTUTILS_H
