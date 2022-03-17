//####################################################################
//# GNU Free Documentation License                                   #
//# Version 1.3, 3 November 2008                                     #
//#                                                                  #
//# Copyright (C) 2021 Lumina Studio                                 #
//# (Paula Garcia Morales, Laura Gil Lopez, Jorge Perez Dominguez,   #
//#  Alba Ruiz Maiques, Javier Sibada Lopez, Miguel Teruel Carvajal) #
//#                                                                  #
//# Everyone is permitted to copy and distribute verbatim copies     #
//# of this license document, but changing it is not allowed.        #
//####################################################################
//#                                                                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//####################################################################



#pragma once

#include "EntityLUM.hpp"
#include "../Vector3d.hpp"
#include "Shaders/Shader.hpp"
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
extern "C" {
    #include "../../glad/glad.h"
    #include <GLFW/glfw3.h>
    
}

enum Camera_Movement {

    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW         = 0.0f;
const float PITCH       = 0.0f;
const float SPEED       = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM        = 45.0f;    


struct CameraLUM : public EntityLUM
{
     // camera Attributes
    glm::vec3 Position{0.0f,0.0f,0.0f};
    glm::vec3 Front{0.0f,0.0f,0.0f};
    glm::vec3 Up{0.0f,0.0f,0.0f};
    glm::vec3 Right{0.0f,0.0f,0.0f};
    glm::vec3 WorldUp{0.0f,0.0f,0.0f};
    glm::vec3 Target{0.0f,0.0f,0.0f};
    // euler Angles
    float Yaw = 0.0f;
    float Pitch = 0.0f;
    // camera options
    float MovementSpeed = 0.0f;
    float MouseSensitivity = 0.0f;
    float Zoom = 0.0f;

    /*Frustum Culling and clipping*/
    glm::vec4 frustum_[6];
    void calculateFrustrum(glm::mat4 & transform);
    void clipping(Shader & shader);
    
    CameraLUM();
    CameraLUM(glm::vec3 position, glm::vec3 target);
    CameraLUM(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    bool setPerspective ();
    bool setParallel    ();
    bool mode_{true};
    void draw           (Shader &shader);
     // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);
    void ProcessMouseScroll(float yoffset);
    std::string getPath();
    
    private:

    float X,
          Y,
          Z;
    bool  isPerspective;
    float near,
          distant;

    void updateCameraVectors();
};

