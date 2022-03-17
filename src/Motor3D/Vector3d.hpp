#pragma once

class Vector3d
{
private:
    float x, y, z;
public:
    Vector3d();
    Vector3d(float x, float y, float z);
    ~Vector3d();

    float getVectorX();
    float getVectorY();
    float getVectorZ();
    void setVectorX(float mx);
    void setVectorY(float my);
    void setVectorZ(float mz);
};

