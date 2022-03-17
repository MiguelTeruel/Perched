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
//#                                                                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//####################################################################

#include "keyboard.hpp"

namespace ECS {
    bool Keyboard_t::isKeyPressed (keys::KEY_CODE k, EventReceiver* receiver) noexcept {
        auto it = getIterator(k);

        if (it) {
            if(receiver->IsKeyDown(k)){
                return true;
            }
        }
        
        return false;
    };

    Keyboard_t::OpIter Keyboard_t::getIterator (keys::KEY_CODE k) noexcept {
        auto it = m_pressedKeys.find(k);

        if (it != m_pressedKeys.end()) {
            return it;
        }
        
        return {};
    }
}