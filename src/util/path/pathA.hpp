#pragma once
#include "../../cmp/collider.hpp"
#include "../../cmp/physics.hpp"
#include <iterator>
#include <iostream>
#include <exception>
#include <stack>
#include <vector>
#include <array>
#include <cfloat>
#include <tgmath.h>
#include "Casilla.hpp"
#define X_MAX 900
#define X_STEP 20
#define Y_MAX 1500
#define Y_STEP 20

#include "../../man/entitymanager.hpp"

#include "../navMesh/NavMesh.hpp"
#include "../navMesh/Triangle.hpp"

//Forward declaration
namespace ECS {
    struct EntityManager_t;
}

   
inline bool operator< (const Casilla& lhs, const Casilla& rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.fCost < rhs.fCost;
}

struct PathA_t {

    explicit PathA_t() = default;   //Constructor

	bool isValid(int x, int y, std::vector<ECS::Entity_t *> &bsalientes); //If our Node is an obstacle it is not valid
		
	bool isDestination(int x, int y, Casilla& dest);
		
	double calculateH(int x, int y,Casilla& dest);
	
	std::vector<Casilla> makePath(std::array<std::array < Casilla, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& map, Casilla& dest);
	
	std::vector<Casilla> aStar(Casilla& player, Casilla& dest, std::vector<ECS::Entity_t *> &bsalientes);

	//NavMesh
	Triangle checkStartingTriangle(NavMesh, Vector3d);

	private:
		bool pointIsideTriangle(Vector3d p, Vector3d a, Vector3d b, Vector3d c);
		bool sameSide(Vector3d p1, Vector3d p2, Vector3d a, Vector3d b);
		Vector3d crossProduct(Vector3d a, Vector3d b);
		float dotProduct(Vector3d p1, Vector3d p2);
};