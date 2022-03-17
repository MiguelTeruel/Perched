#pragma once

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
 
extern "C" {
    #include "../../glad/glad.h"
    #include <GLFW/glfw3.h>
    #include <GLFW/glfw3native.h>    
}
#include "Shaders/Shader.hpp"
#include "Resources/ResourceManager.hpp"
#include "../Motor3D.hpp"
#include "NodeLUM.hpp"
#include "CameraLUM.hpp"
#include "ModelLUM.hpp"
#include "LightLUM.hpp"
#include <exception>
#include <iostream>
#include <ctime>

struct Motor3DLUM : public Motor3D
{   
    Motor3DLUM  (uint32_t, uint32_t);
    ~Motor3DLUM ();

    /* Bucle */
    void beginScene ();
    void endScene   ();
    bool run        (); 
    void drawAll    ();
    void dropDevice ();

    /* Nodos, camaras y texto */
    Node*    createCamera     (Vector3d,Vector3d);
    Node*    createLight      (Vector3d,Vector3d);
    void     addStaticText    (const wchar_t*, int, int, int, int);
    void     addText          (std::string, int, int, int, int);
    Node*    createCubeNode   (float);
    Node*    createMeshNode   (std::string const &path, bool gamma);
    Node*    createSphereNode (float);
    Node*    drawA3DLine      (float,float,float,float);

    //Texture* getTexture       (const char*);
    //bool     setTexture       (const char*, int);

    std::vector<std::unique_ptr<NodeLUM>> nodes_;
    bool removeNode   (Node*);
    bool removeCamera (Node*);
    EventReceiver* getReceiver();
    /* Tiempo */
    int getTime();
    int getFPS ();

    Node* getCamera();
    void processInput(GLFWwindow *window);
    GLFWwindow* getWindow();

    // Vertecies e Indices
    std::vector<Vector3d> getNodeVertices(Node *);
    std::vector<unsigned int> getNodeIndexes(Node *);

    private:
    uint32_t width_{}, height_{};
    GLFWwindow* window_;
    EventReceiver eventR_;
    Node* light;
    ResourceManager rm_;
    Node* camera_;
    int fps_ {0};
    int s_   {0};

    /* Camera and movement callback functions (OpenGL) */
    
    Shader ourShader_   {};
    Shader SingleColor_ {};
    ResourceManager rManager_;
    bool firstMouse {true};
    float lastX_ {width_/2.0f};
    float lastY_ {height_/2.0f};
    float deltaTime_ {0.0f};
    float lastFrame_ {0.0f};
    
    /* Camera and movement callback functions (OpenGL) */
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    /* Set Material*/
    void setMaterialToNode(Node*, float, float);
};