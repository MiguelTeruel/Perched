#include "MaterialLUM.hpp"

MaterialLUM::MaterialLUM(float ambiental, float diffuse){
    _ambiental = ambiental;
    _diffuse = diffuse;
}

MaterialLUM::MaterialLUM(){
    _ambiental = 0;
    _diffuse = 0;
}

