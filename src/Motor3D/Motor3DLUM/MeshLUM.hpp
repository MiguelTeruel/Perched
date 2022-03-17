#pragma once

#include "NodeLUM.hpp"
#include "Shaders/Shader.hpp"
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include "TextureLUM.hpp"
#include "VertexLUM.hpp"
extern "C" {
    #include "../../glad/glad.h"
    #include <GLFW/glfw3.h>
}

#include <iostream>
#include <vector>
using namespace std;




struct MeshLUM {
    // mesh Data
    vector<VertexLUM>       vertices;
    vector<unsigned int> indices;
    vector<TextureLUM>      textures;
    unsigned int VAO;

    // constructor
    MeshLUM(vector<VertexLUM> vertices, vector<unsigned int> indices, vector<TextureLUM> textures);
   

    // render the mesh
    void draw(Shader &shader);
   

    private:
    // render data 
    unsigned int VBO, EBO;
    // initializes all the buffer objects/arrays
    void setupMesh();
   
    
};

