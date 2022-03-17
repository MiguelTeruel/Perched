#pragma once

#include "../ModelLUM.hpp"
#include "../LightLUM.hpp"

#include <vector>
#include <memory>
struct ResourceManager
{
    ResourceManager() : cameras_{}, models_{}, lights_{}{}
    ModelLUM* modelLoaded(std::vector<std::unique_ptr<ModelLUM>> &, std::string);
    std::vector<std::unique_ptr<CameraLUM>> cameras_;
    std::vector<std::unique_ptr<ModelLUM>> models_;
    std::vector<std::unique_ptr<LightLUM>> lights_;
};