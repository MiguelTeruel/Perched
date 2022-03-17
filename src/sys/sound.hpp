#pragma once

#include "../MotorSonido/MotorSonido.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <stdio.h>
#include <string.h>

#include "../cmp/collider.hpp"
#include "../cmp/physics.hpp"
#include "../cmp/sound.hpp"

template <typename GameCTX_t>
struct SoundSystem_t {
    SoundSystem_t();
    ~SoundSystem_t();

    void InitBanks();
    void InitEvent(std::string evento);
    void InitEventWithParameter(std::string evento, std::string nombre);

    void updatePositions(GameCTX_t& g) noexcept;
    void update(GameCTX_t& g) noexcept;

    void iniciar(std::string evento);

    void menos(std::string evento);
    void mas(std::string evento);

    void reproduciendo(std::string evento);

    private:
        std::unique_ptr<MotorSonido_t> sound {nullptr};
        //En el sistema de sonido nos guargamos un puntero del motor de sonido para llamar a sus funciones

        //FMOD_3D_ATTRIBUTES attributes = { { 0 } };
};