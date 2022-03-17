#include "NodeLUM.hpp"
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"

extern "C" {
    #include "../../glad/glad.h"
    #include <GLFW/glfw3.h>
}

NodeLUM::NodeLUM (float s)
{
    X = 0;
    Y = 0;
    Z = 0;
    size = 1;
    id = -1;
    translation = glm::vec3(0.0f,0.0f,0.0f);
    rotation = glm::vec3(0.0f,0.0f,0.0f);
    scalation = glm::vec3(1.0f,1.0f,1.0f);
    matTrans = glm::mat4(1.0f);
}
NodeLUM::NodeLUM (const char* path)
{
    X = 0;
    Y = 0;
    Z = 0;
    size = 1;
    id = -1;
    translation = glm::vec3(0.0f,0.0f,0.0f);
    rotation = glm::vec3(0.0f,0.0f,0.0f);
    scalation = glm::vec3(1.0f,1.0f,1.0f);
    matTrans = glm::mat4(1.0f);
}
void NodeLUM::remove()
{
    this->setParent(nullptr);
    for (size_t i = 0; i < children.size(); i++)
    {
        children[i]->remove();
    }
    children.clear();
    delete this;
}
float NodeLUM::getX()
{
    return X;
}
float NodeLUM::getY()
{
    return Y;
}
float NodeLUM::getZ()
{
    return Z;
}
int NodeLUM::getNodeID()
{
    return id;
}
void NodeLUM::setID(int i)
{
    if (i>=0)
    {
        id = i;
    }
}
int NodeLUM::getSize()
{
    return size;
}
Vector3d NodeLUM::getTarget ()
{
    return Vector3d{target.x,target.y,target.z};
}

void NodeLUM::setPosition (Vector3d a)
{
    X = a.getVectorX();
    Y = a.getVectorY();
    Z = a.getVectorZ();
    setTranslation(a);
}
void NodeLUM::setTarget(Vector3d v)
{
    target.x = v.getVectorX();
    target.y = v.getVectorY();
    target.z = v.getVectorZ();
    //cogido con pinzas
    glm::vec3 aux {-target.y,-target.x,0};
    rotation = aux;
}
Vector3d NodeLUM::getPosition ()
{
    return Vector3d(X,Y,Z);
}

/* NEW MOTOR IMPLEMENTATIONS */

int NodeLUM::addChild (NodeLUM* child)
{
    bool b = child->setParent(this);
    if (b)
    {
        children.push_back(child);
        return children.size()-1;   
    }
    return -1;
}
int NodeLUM::removeChild (NodeLUM* child)
{
    for (size_t i = 0; i < children.size(); i++)
    {
        if (children[i] == child)
        {
            children[i]->setParent(nullptr);
            children.erase(children.begin()+i);
        }
        return i;   
    }
    return -1;
}
void NodeLUM::removeChildren()
{
    children.clear();
}
NodeLUM* NodeLUM::getParent ()
{
    if (parent!=nullptr)
    {
        return parent;
    }
    return nullptr;
}
bool NodeLUM::setParent (NodeLUM* n)
{
    parent = n;
    return true;
}
bool NodeLUM::setEntity(EntityLUM * ent)
{
    if (ent!=nullptr)
    {
        entity = ent;    
        return true;
    }
    return false;
}
EntityLUM* NodeLUM::getEntity()
{
    return entity;
}

void NodeLUM::loopThrough (glm::mat4 matPlus, Shader &s)
{
    if (updateMat)
    {
        matTrans = matPlus*calculateMat();
    }
    s.setMat4("model", matTrans);
    if(this->entity!=nullptr && isNodeOnFrustum(this, this->matTrans) && this!=camNode_){
        this->entity->draw(s);
    }
    for (size_t i = 0; i < children.size(); i++)
    {
        if(children[i]!=nullptr)
        children[i]->loopThrough(matTrans, s);
    }
}
glm::mat4 NodeLUM::calculateMat ()
{
    //revisar lo de la rotacion
    glm::mat4 trans = glm::translate (glm::mat4(1.0f), glm::vec3(translation.x, translation.y, translation.z));
    glm::mat4 sca   = glm::scale     (glm::mat4(1.0f), glm::vec3(scalation.x,   scalation.y,   scalation.z));

    glm::mat4 rotX  = glm::rotate    (glm::mat4(1.0f), glm::radians(rotation.x),   glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotY  = glm::rotate    (glm::mat4(1.0f), glm::radians(rotation.y),   glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotZ  = glm::rotate    (glm::mat4(1.0f), glm::radians(rotation.z),   glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 rot   = rotX  * rotY * rotZ;

    glm::mat4 aux   = trans * rot  * sca;
   
    return aux;
}
void NodeLUM::setTranslation (Vector3d transVec)
{
    translation.x = transVec.getVectorX();
    translation.y = transVec.getVectorY();
    translation.z = transVec.getVectorZ();
}
void NodeLUM::setRotation (Vector3d rotVec)
{
    rotation.x = rotVec.getVectorX();
    rotation.y = rotVec.getVectorY();
    rotation.z = rotVec.getVectorZ();
}
void NodeLUM::setScale (Vector3d scVec)
{
    scalation.x = scVec.getVectorX();
    scalation.y = scVec.getVectorY();
    scalation.z = scVec.getVectorZ();
}
void NodeLUM::translate (Vector3d transVec)
{
    translation.x += transVec.getVectorX();
    translation.y += transVec.getVectorY();
    translation.z += transVec.getVectorZ();
}
void NodeLUM::scale (Vector3d scVec)
{
    scalation.x += scVec.getVectorX();
    scalation.y += scVec.getVectorY();
    scalation.z += scVec.getVectorZ();
}
void NodeLUM::rotate (Vector3d rotVec)
{
    rotation.x += rotVec.getVectorX();
    rotation.y += rotVec.getVectorY();
    rotation.z += rotVec.getVectorZ();
}
Vector3d NodeLUM::getTranslation ()
{
    return Vector3d(translation.x,translation.y,translation.z);
}
Vector3d NodeLUM::getRotation ()
{
    return Vector3d(rotation.x,rotation.y,rotation.z);
}
Vector3d NodeLUM::getScale ()
{
    return Vector3d(scalation.x,scalation.y,scalation.z);
}

void NodeLUM::setMatrixTrans (glm::mat4 mat)
{
    matTrans = mat;
}
glm::mat4 NodeLUM::getMTrans ()
{
    return matTrans;
}

MaterialLUM NodeLUM::getMaterial(){
    return material;
}

std::string NodeLUM::printChildren()
{
    std::string s;
    if (!children.empty())
    {
        for (size_t i = 0; i < children.size(); ++i)
        {
            s+=std::to_string(children[i]->getNodeID());
            s+="\n";
        }
    }
    else
    {
        s="No tiene hijos.\n";
    }
    
    return s;
}

void NodeLUM::setMaterial(float am, float di){
    material = MaterialLUM(am, di);
}
bool NodeLUM::isNodeOnFrustum(Node* thisNode, glm::mat4 & mat)
{
    if (camNode_!=thisNode)
    {
        auto camEnt {(CameraLUM*)(camNode_->getEntity())};
        Shape s{};
        return s.isOnFrustum(camEnt, mat);
    }
    return true;   
}