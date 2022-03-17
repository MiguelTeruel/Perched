#pragma once

#include "EntityLUM.hpp"
#include "MeshLUM.hpp"
#include "TextureLUM.hpp"
#include "VertexLUM.hpp"
extern "C" {
    #include "../../glad/glad.h"
    #include <GLFW/glfw3.h>
}
#include <math.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "Shaders/Shader.hpp"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct ModelLUM : public EntityLUM
{
   
    public:
    // model data 
    vector<TextureLUM> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<MeshLUM>    meshes;
    string directory;
    bool gammaCorrection;

    // constructor, expects a filepath to a 3D model.
    ModelLUM(string const &path, bool gamma);

    // draws the model, and thus all its meshes
    void draw(Shader &shader);
    std::string getPath();
  
private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const &path);
    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene);
    MeshLUM processMesh(aiMesh *mesh, const aiScene *scene);
    unsigned int TextureFromFile(const char *path, const string &directory, bool gamma);
    vector<TextureLUM> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    std::string path_;
};

