#include "Vector3d.hpp"

Vector3d::Vector3d(){ x=0; y=0; z=0;  }

Vector3d::Vector3d(float nx, float ny, float nz){
    x = nx;
    y = ny;
    z = nz;
}

Vector3d::~Vector3d()
{

}

float Vector3d::getVectorX(){return x;}
float Vector3d::getVectorY(){return y;}
float Vector3d::getVectorZ(){return z;}

void Vector3d::setVectorX(float mx){ x = mx; }
void Vector3d::setVectorY(float my){ y = my; }
void Vector3d::setVectorZ(float mz){ z = mz; }