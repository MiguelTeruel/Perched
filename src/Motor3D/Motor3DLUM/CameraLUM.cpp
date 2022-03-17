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
#include "CameraLUM.hpp"

#include <iostream>


    CameraLUM::CameraLUM()
    {

    }
    CameraLUM::CameraLUM(glm::vec3 position, glm::vec3 target){

        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        Yaw = YAW;
        Pitch = PITCH;
        Position.x = position.x;
        Position.y = position.y*-1.0f;
        Position.z = position.z*-1.0f;
        Front = glm::vec3{0.0f,0.0f,-1.0f};
        WorldUp = up;
        MovementSpeed = SPEED;
        MouseSensitivity = SENSITIVITY;
        Zoom = ZOOM;
        updateCameraVectors();
    }

    CameraLUM::CameraLUM(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch){
        
        Front = glm::vec3(0.0f, 0.0f, -1.0f);
        MovementSpeed = SPEED;
        MouseSensitivity = SENSITIVITY;
        Zoom = ZOOM;
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        X = posX;
        Y = posY;
        Z = posZ;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    
     // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 CameraLUM::GetViewMatrix(){
        
        return glm::lookAt(Position, Front + Position, Up);
    }
    bool CameraLUM::setPerspective()
    {
        mode_ = true;
    }
    bool CameraLUM::setParallel()
    {
        mode_ = false;
    }
    void CameraLUM::updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }

    void CameraLUM::ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Up * velocity;
        if (direction == BACKWARD)
            Position -= Up * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void CameraLUM::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void CameraLUM::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f; 
}
void CameraLUM::draw(Shader &shader)
{
}
std::string CameraLUM::getPath()
{
    return "no path for a camera\n";
}

    /*Frustum Culling and clipping*/
void CameraLUM::calculateFrustrum(glm::mat4 & transform)
{
    glm::vec4
        top  { 
                transform[0].w-transform[0].y,
                transform[1].w-transform[1].y,
                transform[2].w-transform[2].y,
                transform[3].w-transform[3].y
            },
        bot  { 
                transform[0].w+transform[0].y,
                transform[1].w+transform[1].y,
                transform[2].w+transform[2].y,
                transform[3].w+transform[3].y
            },
        rght {
                transform[0].w-transform[0].x,
                transform[1].w-transform[1].x,
                transform[2].w-transform[2].x,
                transform[3].w-transform[3].x
            },
        left {
                transform[0].w+transform[0].x,
                transform[1].w+transform[1].x,
                transform[2].w+transform[2].x,
                transform[3].w+transform[3].x
            },
        near {
                transform[0].w+transform[0].z,
                transform[1].w+transform[1].z,
                transform[2].w+transform[2].z,
                transform[3].w+transform[3].z
            },
        far  {
                transform[0].w-transform[0].z,
                transform[1].w-transform[1].z,
                transform[2].w-transform[2].z,
                transform[3].w-transform[3].z
            };

    frustum_[0] = top;
    frustum_[1] = bot;
    frustum_[2] = rght;
    frustum_[3] = left;
    frustum_[4] = near;
    frustum_[5] = far;
}
void CameraLUM::clipping(Shader & shader)
{
    shader.setVec4("ClipPlaneTop", frustum_[0]);
    shader.setVec4("ClipPlaneBot", frustum_[1]);
    shader.setVec4("ClipPlaneRht", frustum_[2]);
    shader.setVec4("ClipPlaneLft", frustum_[3]);
    shader.setVec4("ClipPlaneNer", frustum_[4]);
    shader.setVec4("ClipPlaneFar", frustum_[5]);
}