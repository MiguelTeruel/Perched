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
//# Keyboard sirve para almacenar las teclas que se pueden pulsar    #
//#   y gestionar las pulsaciones de teclado.                        #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once

#include "../util/MyKeycodes.h"
#include "../Motor3D/Motor3D.hpp"

#include <X11/X.h>
#include <X11/keysym.h>
#include <unordered_map>
#include <optional>

namespace ECS {
    struct Keyboard_t {
        using OpIter = std::optional<std::unordered_map<keys::KEY_CODE, bool>::iterator>;

        explicit Keyboard_t() = default;

        Keyboard_t(const Keyboard_t&) = delete;
        Keyboard_t(Keyboard_t&&) = delete;
        Keyboard_t& operator=(const Keyboard_t&) = delete;
        Keyboard_t& operator=(Keyboard_t&&) = delete;

        bool isKeyPressed (keys::KEY_CODE k, EventReceiver* receiver) noexcept;

        void keyPressed(keys::KEY_CODE k) noexcept {
            auto it = getIterator(k);

            if (it) {
                (*it)->second = true;
            }
        }

        void keyReleased(keys::KEY_CODE k) noexcept {
            auto it = getIterator(k);

            if (it) {
                (*it)->second = false;
            }
        }

        void reset() noexcept {
            for (auto& [_ , st] : m_pressedKeys) {
                st = false;
            }
        }

        private:
            OpIter getIterator(keys::KEY_CODE k) noexcept;

            std::unordered_map<keys::KEY_CODE, bool> m_pressedKeys {

                {keys::KEY_ESCAPE, false},
                {keys::KEY_KEY_A, false},
                {keys::KEY_KEY_B, false},
                {keys::KEY_KEY_C, false},            
                {keys::KEY_KEY_D, false},            
                {keys::KEY_KEY_E, false},            
                {keys::KEY_KEY_F, false},            
                {keys::KEY_KEY_G, false},            
                {keys::KEY_KEY_H, false},            
                {keys::KEY_KEY_I, false},            
                {keys::KEY_KEY_J, false},            
                {keys::KEY_KEY_K, false},            
                {keys::KEY_KEY_L, false},            
                {keys::KEY_KEY_M, false},            
                {keys::KEY_KEY_N, false},            
                {keys::KEY_KEY_O, false},            
                {keys::KEY_KEY_P, false},            
                {keys::KEY_KEY_Q, false},            
                {keys::KEY_KEY_R, false},            
                {keys::KEY_KEY_S, false},            
                {keys::KEY_KEY_T, false},            
                {keys::KEY_KEY_U, false},            
                {keys::KEY_KEY_V, false},            
                {keys::KEY_KEY_W, false},            
                {keys::KEY_KEY_X, false},            
                {keys::KEY_KEY_Y, false},            
                {keys::KEY_KEY_Z, false}
            };
    };
}