#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "Triangle.hpp"
#include "../../Motor3D/Vector3d.hpp"

struct NavMesh
{

    NavMesh(std::vector<Vector3d>, std::vector<unsigned int>);
    NavMesh();
    ~NavMesh();

    void debug();

    //NavMesh's Triangles
    std::vector<Triangle> triangles;
};
