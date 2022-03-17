#pragma once
#include "component.hpp"
#include <iostream>
#include <map>

struct SoundComponent_t : public ECS::ComponentBase_t<SoundComponent_t> {
    explicit SoundComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};

    std::string event_id;
    std::map<std::string, float> floatparameters;
    std::map<std::string, int> intparameters;

    uint8_t marked_for_parameter_update { 0 }; //actualizar parametro
    uint8_t marked_for_stop { 0 }; //parar evento
    uint8_t marked_for_play { 0 }; //reproducir evento
    uint8_t marked_for_init { 0 }; //inicializar evento

    uint8_t isEvent3D { false };
};