//####################################################################
//# GNU Free Documentation License                                   #
//# Version 1.3, 3 November 2008                                     #
//#                                                                  #
//# Copyright (C) 2021 Lumina Studio                                 #
//# (Paula Garcia Morales, Laura Gil Lopez, Jorge Perez Dominguez,   #
//#  Alba Ruiz Maiques, Javier Sibada Lopez, Miguel Teruel Carvajal) #
//#                                                                  #
//# Everyone is permitted to copy and distribute verbatim copies     #
//# of this license document, but changing it is not allowed.        #
//####################################################################
//#                                                                  #
//# StateManager sirve para gestionar los estados por los que pasa   #
//#   el juego, como el menu, el juego, ...                          #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once
#include <stack>
#include <memory>

struct StateBase_t {
    virtual void update() = 0;
    virtual bool alive() = 0;
    virtual ~StateBase_t() = default;
};

struct StateManager_t {
    explicit StateManager_t() = default;

    //typename... indica que recibire un paquete de parametros
    template <typename State_t, typename... Ts>
    void addState(Ts&&... args) {
        static_assert(std::is_base_of<StateBase_t, State_t>::value, "ERROR, Invalid State_t");

        //forward<decltype> lo convierte otra vez a temporal
        m_States.push( std::make_unique<State_t>(std::forward<decltype(args)>(args)... ));
    }

    void update() {
        if (alive()) {
            auto& state { m_States.top() };

            if (state && state->alive()) {
                state->update();
            } else {
                m_States.pop();
            }
        }
    }

    bool alive() {
        return !m_States.empty();
    }

    private:
        std::stack<std::unique_ptr<StateBase_t>> m_States;
};