#pragma once
#include <string>
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"

extern "C" {
    #include "../../glad/glad.h"
    #include <GLFW/glfw3.h>
}

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct TextureLUM {

    public:

    unsigned int id;
    std::string type;
    std::string path;

};