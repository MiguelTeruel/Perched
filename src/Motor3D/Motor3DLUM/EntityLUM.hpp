#pragma once

#include "../../glm/glm.hpp"
extern "C" {
    #include "../../glad/glad.h"
    #include <GLFW/glfw3.h>
}
#include <iostream>
#include "Shaders/Shader.hpp"
struct EntityLUM
{
    //~EntityLUM();
    virtual void draw(Shader &shader) = 0;
    virtual std::string getPath()     = 0;
};
