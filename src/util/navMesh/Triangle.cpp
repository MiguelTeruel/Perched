#include "Triangle.hpp"

Triangle::Triangle(Vector3d v1, Vector3d v2, Vector3d v3) : _v1 {v1}, _v2 {v2}, _v3 {v3} { }

Triangle::Triangle() {
    _v1 = Vector3d();
    _v2 = Vector3d();
    _v3 = Vector3d();
}

Triangle::~Triangle(){}