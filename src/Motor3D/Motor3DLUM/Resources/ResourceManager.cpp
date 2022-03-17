#include "ResourceManager.hpp"

ModelLUM* ResourceManager::modelLoaded(std::vector<std::unique_ptr<ModelLUM>> & models, std::string path)
{
    for (size_t i = 0; i < models.size(); i++)
    {
        if (models[i].get()->getPath() == path)
        {
            return models[i].get(); 
        } 
    }
    return nullptr;
}