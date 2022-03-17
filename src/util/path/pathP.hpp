#pragma once

#include <iostream>
#include <vector>
#include <time.h>

#include "../../cmp/collider.hpp"
#include "../../cmp/physics.hpp"
#include "../../cmp/entity.hpp"
#include "Casilla.hpp"

//Forward declaration
namespace ECS {
    struct EntityManager_t;
}

struct PathP_t {
    explicit PathP_t(uint tamx, uint tamy);   //Constructor

    void ponerSalientes(uint tamx, uint tamy, std::vector<ECS::Entity_t *> &bsalientes);
    void buscarSalientes(int x, int y, std::vector<ECS::Entity_t *> &bsalientes);

    bool isValid(int x, int y, int M, int N);
    void printPath(std::vector<int> const &path, int last, std::vector<std::vector<int>> const &mat);
    void findPaths(std::vector<std::vector<int>> const &mat, std::vector<int> &path, int i, int j, int M, int N);
    
    std::vector<Casilla> buscar(int xIni, int yIni, int xFin, int yFin);

    private:
        std::vector<std::vector<Casilla>> caminos;

        std::vector<std::vector<int>> mat;
        std::vector<std::vector<int>> salientes;
        
        //int sal[45][75];
        int dirX {0}, dirY {0};
        int sumX1 {0}, sumY1 {0}, sumX2 {0}, sumY2 {0}, sumDX {0}, sumDY {0};
        int MM {0};
        int NN {0};
};