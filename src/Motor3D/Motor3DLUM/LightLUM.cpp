#include "Motor3DLUM.hpp"
#include "LightLUM.hpp"

LightLUM::LightLUM(glm::vec3 pos, glm::vec3 color){
    
    lightPos = pos;
    lightColor = color;

}


void LightLUM::setIntensity (glm::vec3){



}

glm::vec3 LightLUM::getIntensity (){

    return intensity;
}
    

void LightLUM::draw (Shader &shader){


}
std::string LightLUM::getPath()
{
    return "no path for a light\n";
}

