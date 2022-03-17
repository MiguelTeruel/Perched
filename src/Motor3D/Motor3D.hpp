#pragma once

#include "Node.hpp"
#include "EventReceiver.hpp"
#include <iostream>
#include <memory>
#include <vector>

struct Motor3D
{
    /* Bucle de renderizado */
    ~Motor3D(){};
    virtual bool run()        = 0;
    virtual void beginScene() = 0;
    virtual void endScene()   = 0;
    virtual void drawAll()    = 0;
    virtual void dropDevice() = 0;

    /* Camaras */
    virtual Node* createCamera(Vector3d,Vector3d)  = 0;
    virtual bool  removeCamera(Node*)              = 0;
    
    /* Nodos (Cajas y meshes) */    
    virtual Node* createCubeNode(float size)           = 0;
    virtual Node* createMeshNode(std::string const &path, bool gamma) = 0;
    virtual bool  removeNode(Node*)                    = 0;
      
    /* Texturas*/     
    //virtual Texture* getTexture(const char* path)  = 0;
    //virtual bool  setTexture (const wchar_t*, int) = 0;

    /* Texto */
    virtual void addStaticText(const wchar_t*, int, int, int, int) = 0;
    virtual void addText(std::string, int, int, int, int)          = 0;


    /* Tiempo */
    virtual int getTime()                = 0;
    virtual int getFPS ()                = 0;
    /*Event Receiver*/ 
    virtual EventReceiver* getReceiver() = 0;
    virtual Node* getCamera() = 0;

    //Vertices e Indices
    virtual std::vector<Vector3d> getNodeVertices(Node*) = 0;
    virtual std::vector<unsigned int> getNodeIndexes(Node *) = 0;

    //Materiales
    virtual void setMaterialToNode(Node*, float, float) = 0;
};



