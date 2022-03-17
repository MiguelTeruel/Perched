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

struct LightLUM : public EntityLUM
{
    //light Attributes
    glm::vec3 lightPos{0.0f,0.0f,0.0f};
    glm::vec3 lightColor{0.0f,0.0f,0.0f};

    LightLUM(glm::vec3 pos, glm::vec3 color);  //luces puntuales
    void      setIntensity (glm::vec3);
    glm::vec3 getIntensity ();
    void      draw         (Shader &shader);
    std::string getPath();

    private:
    glm::vec3 intensity;
    glm::vec3 lightDirection;

};
