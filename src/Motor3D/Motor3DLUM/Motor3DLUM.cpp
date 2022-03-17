#include "Motor3DLUM.hpp"

Motor3DLUM::Motor3DLUM(uint32_t w, uint32_t h) : width_{w}, height_{h}
{    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window_ = glfwCreateWindow (
        width_,
        height_,
        "Perched!",
        NULL,
        NULL
    );
    
    if (window_ == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window_);
    glfwSetWindowUserPointer(window_, this);
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
    glfwSetCursorPosCallback(window_, GLFWcursorposfun(mouse_callback));
    glfwSetScrollCallback(window_, GLFWscrollfun(scroll_callback));
    // tell GLFW to capture our mouse
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD :: Motor3DLUM.cpp:33" << std::endl;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);  
    ourShader_.createShader
    (
        "src/Motor3D/Motor3DLUM/Shaders/Shader.vs",
        "src/Motor3D/Motor3DLUM/Shaders/Shader.fs"
    );
    SingleColor_.createShader
    (
        "src/Motor3D/Motor3DLUM/Shaders/shaderborde.vts",
        "src/Motor3D/Motor3DLUM/Shaders/shaderSingleColor.fts"
    );
    eventR_ = EventReceiver(window_);
    camera_ = createCamera(Vector3d(210,50,95),Vector3d(0,0,0));
    light =   createLight(Vector3d(0.0f,-2000.0f, -200.0f),Vector3d(1.0f, 1.0f, 1.0f));
}
Motor3DLUM::~Motor3DLUM()
{
    camera_ = nullptr;
    window_ = nullptr;
}
/* Bucle */
void Motor3DLUM::beginScene ()
{
    auto nlumcam {(NodeLUM*)(camera_)};
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime_ = currentFrame - lastFrame_;
    lastFrame_ = currentFrame;
    processInput(window_);
    
    glClearColor(0.1f , 0.5f , 0.9f , 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    // set uniforms

    LightLUM* li {(LightLUM*)(light->getEntity())};

    nlumcam->calculateMat();
    CameraLUM* cami {(CameraLUM*)(camera_->getEntity())};
    //Preguntar a sergio el lunes 4/3/22
    glm::mat4 model(1.0f);
    glm::mat4 projection {};
    if (cami->mode_)
    {
        projection = glm::perspective(glm::radians(90.0f), (float)width_ / (float)height_, 0.1f, 100.0f);
    }
    else
    {
        projection = glm::ortho(glm::radians(90.0f), (float)width_ / (float)height_, 0.1f, 100.0f);
    }
    glm::mat4 view {glm::inverse(nlumcam->getMTrans())};

    SingleColor_.use(); 
    SingleColor_.setMat4("view", view);
    SingleColor_.setMat4("projection", projection);
    
    //ourmodel.draw(SingleColor);

    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CLIP_DISTANCE0);

    //*********************************
    //Configuracion del Shader
    //*********************************
    ourShader_.use();
    ourShader_.setVec3("viewPos", cami->Position); 

    ourShader_.setVec3("lightColor", li->lightColor);
    ourShader_.setVec3("lightPos", li->lightPos);
    ourShader_.setVec3("lightDirection",1.0f, 1.0f, 1.0f);	    
    
    ourShader_.setMat4("projection", projection);
    ourShader_.setMat4("view", view);

    glm::mat4 projViewMod {projection*view*model};
    cami->calculateFrustrum(projViewMod);
    cami->clipping(ourShader_);
    cami->clipping(SingleColor_);
}
void Motor3DLUM::endScene ()
{
    glfwSwapBuffers(window_);
    glfwPollEvents();
}
bool Motor3DLUM::run ()
{
    if (!glfwWindowShouldClose(window_))
    {
        return true;
    }
    glfwTerminate();
    return false;
} 
void Motor3DLUM::drawAll ()
{
    ++fps_;
    if (s_ < getTime() || getTime() == 0 && s_ > 0)
    {
        std::cout << "Motor3DLUM.cpp:150 FPS = " << fps_ << "\n";
        fps_ = 0;
    }
    s_ = getTime();

    for (size_t i = 0; i < nodes_.size(); i++)
    {
        nodes_[i]->camNode_ = (NodeLUM*)(camera_);
        glm::mat4 model {glm::mat4(1.0f)};
        if(nodes_[i]!=nullptr && nodes_[i].get()!=nullptr)
        {
            if (nodes_[i].get()->getParent()==nullptr)
            {
                glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
                glStencilMask(0x00);
                glDisable(GL_DEPTH_TEST);
                SingleColor_.use();
                SingleColor_.setFloat("scale",0.2);
                SingleColor_.setMat4("model", model);
                nodes_[i].get()->loopThrough(model,SingleColor_); 
                glStencilMask(0xFF);
                glStencilFunc(GL_ALWAYS, 0, 0xFF);
                glStencilMask(0xFF);
                glEnable(GL_DEPTH_TEST);
                ourShader_.use();
                ourShader_.setFloat("Ka",nodes_[i].get()->getMaterial()._ambiental);
                ourShader_.setFloat("Kd",nodes_[i].get()->getMaterial()._diffuse);
                //model = glm::mat4(1.0f);
                ourShader_.setMat4("model", model);
                nodes_[i].get()->loopThrough(model,ourShader_); 
            }
        }
    }
}
void Motor3DLUM::dropDevice ()
{

}
/* Nodos, camaras y texto */
Node* Motor3DLUM::createCamera (Vector3d pos,Vector3d up)
{
    glm::vec3 a,b;
    a.x = pos.getVectorX();
    a.y = pos.getVectorY();
    a.z = pos.getVectorZ();

    b.x = up.getVectorX();
    b.y = up.getVectorY();
    b.z = up.getVectorZ();

    rm_.cameras_.push_back(std::make_unique<CameraLUM>(a,b));
    nodes_.push_back(std::make_unique<NodeLUM>(1.0f));
    nodes_[nodes_.size()-1]->setEntity(rm_.cameras_[rm_.cameras_.size()-1].get());
    nodes_[nodes_.size()-1]->setTranslation(pos);
    camera_ = nodes_[nodes_.size()-1].get();
    return nodes_[nodes_.size()-1].get();
}

Node* Motor3DLUM::createLight (Vector3d pos,Vector3d color){
    glm::vec3 a,b;
    a.x = pos.getVectorX();
    a.y = pos.getVectorY();
    a.z = pos.getVectorZ();

    b.x = color.getVectorX();
    b.y = color.getVectorY();
    b.z = color.getVectorZ();

    rm_.lights_.push_back(std::make_unique<LightLUM>(a,b));
    nodes_.push_back(std::make_unique<NodeLUM>(1.0f));
    nodes_[nodes_.size()-1]->setEntity(rm_.lights_[rm_.lights_.size()-1].get());
    nodes_[nodes_.size()-1]->setTranslation(pos);
    light = nodes_[nodes_.size()-1].get();
    return nodes_[nodes_.size()-1].get();
}

void  Motor3DLUM::addStaticText (const wchar_t*, int, int, int, int)
{

}
void  Motor3DLUM::addText (std::string, int, int, int, int)
{

}
Node* Motor3DLUM::createCubeNode (float size)
{
     auto aux = rm_.modelLoaded(rm_.models_,"assets/pruebi2.obj");
    if (aux!=nullptr)
    {
        nodes_.push_back(std::make_unique<NodeLUM>());
        nodes_[nodes_.size()-1]->setEntity(aux);
    }
    else
    {
        rm_.models_.push_back(std::make_unique<ModelLUM>("assets/pruebi2.obj",false));
        nodes_.push_back(std::make_unique<NodeLUM>());
        nodes_[nodes_.size()-1]->setEntity(rm_.models_[rm_.models_.size()-1].get());
    }
    return nodes_[nodes_.size()-1].get();
}
Node* Motor3DLUM::createMeshNode (std::string const &path, bool gamma)
{
    auto aux = rm_.modelLoaded(rm_.models_, path);
    if (aux!=nullptr)
    {
        nodes_.push_back(std::make_unique<NodeLUM>());
        nodes_[nodes_.size()-1]->setEntity(aux);
    }
    else
    {
        rm_.models_.push_back(std::make_unique<ModelLUM>(path,gamma));
        nodes_.push_back(std::make_unique<NodeLUM>());
        nodes_[nodes_.size()-1]->setEntity(rm_.models_[rm_.models_.size()-1].get());
    }
    return nodes_[nodes_.size()-1].get();
}

//Texture* Motor3DLUM::getTexture (const char*)
//{
//    return nullptr;
//}
//bool Motor3DLUM::setTexture (const char*, int)
//{
//    return false;
//}

bool Motor3DLUM::removeNode (Node* n)
{
    for (size_t i = 0; i < nodes_.size(); i++)
    {
       if(nodes_[i].get()==n){
           nodes_.erase(nodes_.begin()+i);
       }
    }
    
    return false;
}
bool Motor3DLUM::removeCamera (Node*)
{
    return false;
}
EventReceiver* Motor3DLUM::getReceiver()
{
    return &eventR_;
}
/* Tiempo */
int Motor3DLUM::getTime()
{
    time_t lhs;
    lhs = time (NULL);
    time_t rhs {10*(lhs/10)};
    time_t s   {lhs-rhs};
    return s;
}
int Motor3DLUM::getFPS()
{
    return fps_;
}
Node* Motor3DLUM::getCamera()
{
    return camera_;
}

GLFWwindow* Motor3DLUM::getWindow()
{
    return window_;
}

/* OpenGL Functions */
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Motor3DLUM::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
 
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------

void Motor3DLUM::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    Motor3DLUM* m = static_cast<Motor3DLUM*>(glfwGetWindowUserPointer(window));
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    
    if (m->firstMouse)
    {
        m->lastX_ = xpos;
        m->lastY_ = ypos;
        m->firstMouse = false;
    }
    
    float xoffset = xpos - m->lastX_;
    float yoffset = m->lastY_ - ypos; // reversed since y-coordinates go from bottom to top
    
    m->lastX_ = xpos;
    m->lastY_ = ypos;
    EntityLUM* ent {m->camera_->getEntity()};
    CameraLUM* cam {(CameraLUM*)(ent)};
    cam->ProcessMouseMovement(xoffset, yoffset,true);
}
 
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Motor3DLUM::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Motor3DLUM* m  {static_cast<Motor3DLUM*>(glfwGetWindowUserPointer(window))};
    EntityLUM* ent {m->camera_->getEntity()};
    CameraLUM* cam {(CameraLUM*)(ent)};
    cam->ProcessMouseScroll(static_cast<float>(yoffset));
}

void Motor3DLUM::processInput(GLFWwindow* window)
{
    Motor3DLUM* m  {static_cast<Motor3DLUM*>(glfwGetWindowUserPointer(window))};
    EntityLUM* ent {m->camera_->getEntity()};
    CameraLUM* cam {(CameraLUM*)(ent)};
    if (m->eventR_.IsKeyDown(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cam->ProcessKeyboard(FORWARD, m->deltaTime_);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cam->ProcessKeyboard(BACKWARD, m->deltaTime_);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cam->ProcessKeyboard(LEFT, m->deltaTime_);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cam->ProcessKeyboard(RIGHT, m->deltaTime_);
    }
}

std::vector<Vector3d> Motor3DLUM::getNodeVertices(Node * node){

    std::vector<Vector3d> nodeVertices;

    ModelLUM* model = (ModelLUM* )node->getEntity();
    if(model == nullptr){ return nodeVertices; }

    for (size_t i = 0; i < model->meshes.size(); i++)
    {
        for (size_t j = 0; j < model->meshes[i].vertices.size(); j++)
        {   
            float x = model->meshes[i].vertices[j].Position.x;
            float y = model->meshes[i].vertices[j].Position.y;
            float z = model->meshes[i].vertices[j].Position.z;

            Vector3d vertex = Vector3d(x,y,z);
            nodeVertices.push_back(vertex);
        }
    }

    return nodeVertices;
}

std::vector<unsigned int> Motor3DLUM::getNodeIndexes(Node* node){

    std::vector<unsigned int> nodeIndexes;

    ModelLUM* model = (ModelLUM*)node->getEntity();
    if(model == nullptr){ return nodeIndexes; }

    for (size_t i = 0; i < model->meshes.size(); i++)
    {
        for (size_t j = 0; j < model->meshes[i].vertices.size(); j++)
        {   
            nodeIndexes.push_back(model->meshes[i].indices[j]);
        }
    }

    return nodeIndexes;

}

void Motor3DLUM::setMaterialToNode(Node* node, float ambiental, float diffuse){
    NodeLUM* n = (NodeLUM*)node;
    n->setMaterial(ambiental, diffuse);
}