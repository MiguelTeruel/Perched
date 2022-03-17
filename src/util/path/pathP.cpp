#include "pathP.hpp"

PathP_t::PathP_t(uint tamx, uint tamy) {
    int i = 1;

    for (int x = 0; x < tamx; x++) {
        std::vector<int> v1;

		for (int y = 0; y < tamy; y++) { 
            v1.push_back(i);
            i++;
        }
        mat.push_back(v1);
    }

//    for (int x = 0; x < 75; x++) {
//		for (int y = 0; y < 45; y++) { 
//            std::cout << mat[x][y];
//        }
//        std::cout << "\n";
//    }

    for (int x = 0; x < tamy; x++) {
        std::vector<int> v1;
		for (int y = 0; y < tamx; y++) { 
            v1.push_back(0);
        }
        salientes.push_back(v1);
    }
}

void PathP_t::ponerSalientes(uint tamx, uint tamy, std::vector<ECS::Entity_t *> &bsalientes) {
    for (int x = 0; x < tamy; x++) {
		for (int y = 0; y < tamx; y++) { 
            buscarSalientes(x, y, bsalientes);
        }
    }

//    for (int x = 0; x < tamy; x++) {
//		for (int y = 0; y < tamx; y++) { 
//            std::cout << salientes[x][y];
//        }
//        std::cout << "\n";
//    }
}

void PathP_t::buscarSalientes(int x, int y, std::vector<ECS::Entity_t *> &bsalientes)
{
    for(auto& sal: bsalientes){

        auto* col = sal->getComponent<ColliderComponent_t>();
        auto* phy = sal->getComponent<PhysicsComponent_t>();

		if(col != nullptr && phy != nullptr && col->properties == ColliderComponent_t::P_Saliente){
            for (auto& box: col->boxes) {
                if(x*20 > (box.box.xLeft + box.disX)+phy->x && x*20 <= (box.box.xRight + box.disX)+phy->x
                && y*20 > (box.box.yUp + box.disY)+phy->y && y*20 <= (box.box.yDown + box.disY)+phy->y){

                    salientes[x][y] = 1;
                }
            }
		}
	
	}
}
 
// Function to check if (i, j) is a valid matrix coordinate
bool PathP_t::isValid(int x, int y, int M, int N) {
    if (dirX == 1 && dirY == 1) { //right-up
        return (x >= 0 && (x < M || x == M) && y >= 0 && (y < N || y == N));
    }

    if (dirX == -1 && dirY == 1) { //left-up
        //std::cout << M << " " << x << " " << y << " " << N << "\n";
        return (x >= 0 && (M < x || M == x) && y >= 0 && (y < N || y == N));
    }

    if (dirX == -1 && dirY == -1) { //left-down
        return (x >= 0 && (M < x || M == x) && y >= 0 && (N < y || N == y));
    }

    if (dirX == 1 && dirY == -1) { //right-down
        return (x >= 0 && (x < M || x == M) && y >= 0 && (N < y || N == y));
    }

    return false;
}
 
// Function to print the route taken
void PathP_t::printPath(std::vector<int> const &path, int last, std::vector<std::vector<int>> const &mat)
{
    std::vector<Casilla> camino;

    for (int i: path) {
        //std::cout << i << "( ";

        for (int x = 0; x < 75; x++) {
            for (int y = 0; y < 45; y++) { 
                if (mat[x][y] == i) {
                    Casilla uno;
                    uno.x = x;
                    uno.y = y;
                    //std::cout << x << "," << y;
                    camino.push_back(uno);
                }
            }
        }
        //std::cout << " ),";
    }

    //std::cout << last << "( ";

    for (int x = 0; x < 75; x++) {
        for (int y = 0; y < 45; y++) { 
            if (mat[x][y] == last) {
                Casilla ultima;
                ultima.x = x;
                ultima.y = y;
                //std::cout << x << "," << y;
                camino.push_back(ultima);
            }
        }
    }
    //std::cout << " )\n";
    caminos.push_back(camino);
    //std::cout << "\n";
}

void PathP_t::findPaths(std::vector<std::vector<int>> const &mat, std::vector<int> &path, int i, int j, int M, int N)
{
    // base case
    if (mat.size() == 0) {
        return;
    }
 
    // if the last cell is reached, print the route
    if (i == MM && j == NN)
    {
        printPath(path, mat[i][j], mat);
        return;
    } 
 
    // include the current cell in the path
    path.push_back(mat[i][j]);

    if (salientes[i+sumX1][j+sumY1]==1 && salientes[i+sumX2][j+sumY2]==1) {
        //move diagonal 
        if (salientes[i+sumDX][j+sumDY]!=1 && isValid(i+sumDX, j+sumDY, M, N)) {
            findPaths(mat, path, i+sumDX, j+sumDY, M, N);
        }
    } else {
        // move X
        if (salientes[i+sumX1][j+sumY1]!=1 && isValid(i+sumX1, j+sumY1, M, N)) {
            findPaths(mat, path, i+sumX1, j+sumY1, M, N);
        }
        
        // move Y
        if (salientes[i+sumX2][j+sumY2]!=1 && isValid(i+sumX2, j+sumY2, M, N)) {
            findPaths(mat, path, i+sumX2, j+sumY2, M, N);
        }
    }
 
    // backtrack: remove the current cell from the path
    path.pop_back();
}

std::vector<Casilla> PathP_t::buscar(int xIni, int yIni, int xFin, int yFin)
{ 
    std::vector<Casilla> ruta;

    std::vector<int> path;
 
    // start cell (x,y) - destination cell (M,N)
    //int x = 28, y = 9;
    //int M = 23, N = 0;

    if (xIni <= xFin) {
        dirX = 1;

        if (xIni == xFin) {
            MM = xFin;
        } else {
            MM = xFin-1;
        }

        sumDX = -1; //diagonal X left
        sumX1 = +1; //move right
        sumX2 = 0;
    } else {
        dirX = -1;

        MM = xFin+1;
        sumDX = +1; //diagonal X right
        sumX1 = -1; //move right
        sumX2 = 0;
    }

    if (yIni <= yFin) {
        dirY = 1;

        if (yIni == yFin) {
            NN = yFin;  
        } else {
            NN = yFin-1;
        }

        sumDY = +1; //diagonal Y up
        sumY1 = 0;
        sumY2 = +1; //move up
    } else {
        dirY = -1;

        NN = yFin+1;
        sumDY = -1; //diagonal Y down
        sumY1 = 0;
        sumY2 = -1; //move down
    }

    //comprobar si start cell es distinta a final cell
    //comprobar que final cell no es saliente
    if ((xIni!=xFin || yIni!=yFin) && salientes[xFin][yFin]!=1) {
        findPaths(mat, path, xIni, yIni, xFin, yFin);

        //std::cout << "Size: " << caminos.size() << "\n";

        srand (time(NULL));

        //std::cout << caminos.size() << "\n";

        if (caminos.size() > 0) {
            if (caminos.size() != 1) {
                int randi = rand() % caminos.size();

                return caminos[randi];
            } else {
                return caminos[0];
            }
            
        } else {
            //std::cout << "No hay caminos\n";
            
            return ruta;
        }

        //for (int x = 0; x < caminos.size(); x++) {
        //    for (int y = 0; y < caminos[x].size(); y++) { 
        //        std::cout << "( " << caminos[x][y].x << "," << caminos[x][y].y << " ) ";
        //    }
        //    std::cout << "\n";
        //}
    } else {
        std::cout << "Soy el destino o mi destino es saliente\n";
    }
 
    return ruta;
}