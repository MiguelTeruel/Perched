#pragma once

#include "../../Motor3D/Vector3d.hpp"

struct Triangle
{
    Triangle(Vector3d, Vector3d, Vector3d);
    Triangle();
    ~Triangle();

    Vector3d _v1, _v2, _v3;
};
