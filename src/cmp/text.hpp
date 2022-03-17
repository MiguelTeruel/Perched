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
//# TextComponent sirve para guardar los datos necesarios que        #
//#   necesita una entidad como el tamanyo del rectangulo, y que     #
//#   texto mostrar.                                                 #
//#                                                                  #
//####################################################################

#pragma once
#include "component.hpp"
#include <iostream>

struct TextHijo_t {
    std::string parteFija = "";
    int32_t parteVariable { 0 };
};

struct TextPadre_t {
    std::string texto;
    std::vector<TextHijo_t> childs;
};

struct TextComponent_t : public ECS::ComponentBase_t<TextComponent_t> {
    explicit TextComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};

    int32_t xmin { 0 }, ymin { 0 }, xmax { 0 }, ymax { 0 };

    TextPadre_t texts {};
};