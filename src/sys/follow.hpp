#pragma once
#include "../util/typealiases.hpp"

template <typename GameCTX_t>
struct FollowSystem_t {
    //El explicit se recomienda ponerlo en todos los constructores
    //Sirve para que el programa no haga conversiones implicitas a la hora de construir objetos
    //explicit CameraSystem() = default; //Constructor por defecto
    explicit FollowSystem_t() = default;   //Constructor
                                                        //Destructor

    //            Este const implica que las variables con las que va a trabajar el metodo son conts del ambito de RenderSystem
    constexpr void update(GameCTX_t& g) const noexcept; //El GameContext no es const para que puedan modificarse los valores de las velocidades
};