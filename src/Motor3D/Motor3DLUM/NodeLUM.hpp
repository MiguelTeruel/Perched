#pragma once

#include "../Node.hpp"
#include "MaterialLUM.hpp"
#include "../Vector3d.hpp"
#include "EntityLUM.hpp"
#include <vector>
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include <memory>
extern "C" {
    #include "../../glad/glad.h"
    #include <GLFW/glfw3.h>
}
#include "Shape.hpp"

struct NodeLUM : public Node
{
    NodeLUM (const char*);
    NodeLUM (float);
    NodeLUM (){};
    void     remove      ();
    float    getX        ();
    float    getY        ();
    float    getZ        ();
    int      getNodeID   ();
    void     setID       (int);
    int      getSize     ();
    void     setPosition (Vector3d);
    void     setTarget   (Vector3d);
    Vector3d getPosition ();

    /* New Motor Implementations */

    // Parent and Children nodes
    int      addChild       (NodeLUM*);
    int      removeChild    (NodeLUM*);
    void     removeChildren ();
    NodeLUM* getParent      ();
    bool     setParent      (NodeLUM*);
    NodeLUM* camNode_;
    
    // Entity related to node
    bool       setEntity (EntityLUM*);
    EntityLUM* getEntity ();

    //LookFor
    void      loopThrough   (glm::mat4, Shader&);
    glm::mat4 calculateMat  ();

    // Setters for initial traslation, rotation and scale
    void setTranslation (Vector3d);
    void setRotation    (Vector3d);
    void setScale       (Vector3d);
    
    // Traslate, rotate and sclae modifiers
    void translate  (Vector3d);
    void scale      (Vector3d);
    void rotate     (Vector3d);
    void setMaterial(float, float);

    // Getters
    Vector3d    getTranslation ();
    Vector3d    getRotation    ();
    Vector3d    getScale       ();
    Vector3d    getTarget      ();
    MaterialLUM getMaterial    ();

    void setMatrixTrans      (glm::mat4);
    glm::mat4 getMTrans      ();
    
    /*debug*/
    std::string printChildren();
    bool isNodeOnFrustum(Node*, glm::mat4 & mat);

    private:
    float                      X,
    /*float*/                  Y,
    /*float*/                  Z;
    float                      size;
    EntityLUM*                 entity;
    std::vector<NodeLUM*>      children;
    NodeLUM*                   parent {nullptr}; 
    int                        id;
    bool                       updateMat{true};
    glm::vec3                  target;
    glm::vec3                  translation  = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3                  rotation     = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3                  scalation    = glm::vec3(1.0f,1.0f,1.0f);
    glm::mat4                  matTrans = glm::mat4(1.0f);
    MaterialLUM                material = MaterialLUM(0.9,0.7); //Provisional
};
