#pragma once

#include "Vector3d.hpp"
#include <string>
#include "Motor3DLUM/EntityLUM.hpp"
#include "Motor3DLUM/CameraLUM.hpp"
class Node
{

public:

    virtual void remove() = 0;
    virtual float getX() = 0;
    virtual float getY() = 0;
    virtual float getZ() = 0;
    virtual void setID(int) = 0;
    virtual int getNodeID() = 0;
    virtual int getSize() = 0;
    virtual Vector3d getPosition() = 0;
    virtual void setPosition(Vector3d) = 0;
    virtual void setTarget(Vector3d) = 0;
    virtual Vector3d getTarget() = 0;
    virtual EntityLUM* getEntity() = 0;
    virtual bool setEntity(EntityLUM*) = 0;
    // Setters for initial traslation, rotation and scale
    virtual void setTranslation      (Vector3d) = 0;
    virtual void setRotation         (Vector3d) = 0;
    virtual void setScale            (Vector3d) = 0;
    // Traslate, rotate and sclae modifiers
    virtual void translate           (Vector3d) = 0;
    virtual void scale               (Vector3d) = 0;
    virtual void rotate              (Vector3d) = 0;
    // Getters
    virtual Vector3d  getTranslation () = 0;
    virtual Vector3d  getRotation    () = 0;
    virtual Vector3d  getScale       () = 0;
};
