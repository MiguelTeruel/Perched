#pragma once
#include "Motor3D.hpp"
#define KEYBOARD_KEYS 50

struct EventReceiver
{
    EventReceiver(GLFWwindow* w)
    {
        window = w;
    }
    EventReceiver(){}

    bool IsKeyDown(uint32_t keyCode)
    {
        if ((glfwGetKey(window, keyCode) == GLFW_PRESS))
            return true;
        return false;
    }
private:
    GLFWwindow* window;
};