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

#include "render.hpp"
    
template <typename GameCTX_t>
RenderSystem_t<GameCTX_t>::RenderSystem_t(uint32_t w, uint32_t h)
: m_w{ w }, m_h { h }
, motor{std::make_unique<Motor3DLUM>(m_w, m_h)}
{
    
};

template <typename GameCTX_t>
RenderSystem_t<GameCTX_t>::~RenderSystem_t() {
    //Cerramos la ventana
    //ptc_close();
    //motor->dropDevice();
}

template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::drawAllTexts(const GameCTX_t& g) const {
    auto& textcmps = g.template getComponents<TextComponent_t>();

    std::for_each(begin(textcmps), end(textcmps), [&](const auto& tx) {
        getMotor()->addText(tx.texts.texto, tx.xmin, tx.ymin, tx.xmax, tx.ymax);

        int y = 20;

        for (auto& texti : tx.texts.childs) {
            std::string texto = "";
            if (texti.parteVariable != -1) {
                texto = texti.parteFija + std::to_string(texti.parteVariable);
            } else {
                texto = texti.parteFija;
            }
            
            getMotor()->addText(texto, tx.xmin, tx.ymin + y, tx.xmax, tx.ymax);

            y = y+20;
        }
    });
}

template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::changeTextureIA(RenderComponent_t& ren, const char *path) const {
   // auto tex = std::unique_ptr<Texture>(motor->getTexture(path));
    //ren.entityNodes.node.node->setMaterialTexture(tex.get());
}

template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::checkActionsIA(RenderComponent_t& ren, IAComponent_t& ia) const {
    if (ia.action_chosen != nullptr) {
        switch (ia.enemy) {
            case type_enemy::Aguila:
                //depuracion aguila
                if (ia.action_chosen->change_attack == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-applyGoal.png");
                        break;
                        case BTState::check_see_player:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-checkSeePlayer.png");
                        break;
                        case BTState::ACTseek:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-actSeek.png");
                        break;
                        case BTState::reset_wait:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-resetWait.png");
                        break;
                        case BTState::do_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-doAct.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-changeTarget.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-actArrive.png");
                        break;
                    }
                    break;
                }
                if (ia.action_chosen->change_eat == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/aguila/comer/pajaro-comer.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/comer/pajaro-comer-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/comer/pajaro-comer-applyGoal.png");
                        break;
                        case BTState::search_target:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/comer/pajaro-comer-searchTarget.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/comer/pajaro-comer-actArrive.png");
                        break;
                        case BTState::do_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/comer/pajaro-comer-doAct.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/comer/pajaro-comer-changeTarget.png");
                        break;
                    }
                    break;
                }
                if (ia.action_chosen->change_make_nido == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/aguila/nidar/pajaro-nidar.png");
                    
                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/nidar/pajaro-nidar-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/nidar/pajaro-nidar-applyGoal.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/nidar/pajaro-nidar-changeTarget.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/nidar/pajaro-nidar-actArrive.png");
                        break;
                    }
                    break;
                }
                if (ia.action_chosen->change_protect == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/aguila/proteger/pajaro-proteger.png");
                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/proteger/pajaro-proteger-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/proteger/pajaro-proteger-applyGoal.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/proteger/pajaro-proteger-changeTarget.png");
                        break;
                        case BTState::do_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/proteger/pajaro-proteger-doAct.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/proteger/pajaro-proteger-actArrive.png");
                        break;
                    }
                    break;
                }
            break;
            case type_enemy::Aranya:
                //depuracion aranya
                if (ia.action_chosen->change_attack == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar-applyGoal.png");
                        break;
                        case BTState::check_see_player:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar-checkSeePlayer.png");
                        break;
                        case BTState::ACTseek:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar-actSeek.png");
                        break;
                        case BTState::reset_wait:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar-resetWait.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar-changeTarget.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar-actArrive.png");
                        break;
                    }
                    break;
                }
                if (ia.action_chosen->change_eat == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer-applyGoal.png");
                        break;
                        case BTState::check_see_player:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer-checkSeePlayer.png");
                        break;
                        //case BTState::throw_object:
                        //    changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer-throwObject.png");
                        //break;
                        case BTState::do_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer-doAct.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer-changeTarget.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer-actArrive.png");
                        break;
                    }
                    break;
                }
                if (ia.action_chosen->change_protect == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/aranya/proteger/aranya-proteger.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/proteger/aranya-proteger-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/proteger/aranya-proteger-applyGoal.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/proteger/aranya-proteger-changeTarget.png");
                        break;
                        case BTState::do_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/proteger/aranya-proteger-doAct.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/proteger/aranya-proteger-actArrive.png");
                        break;
                    }
                    break;
                }
            break;
            case type_enemy::Cabra:
                //depuracion cabra
                if (ia.action_chosen->change_attack == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/cabra/atacar/cabra-atacar.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/atacar/cabra-atacar-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/atacar/cabra-atacar-applyGoal.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/atacar/cabra-atacar-changeTarget.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/atacar/cabra-atacar-actArrive.png");
                        break;
                    }
                    break;
                }
                if (ia.action_chosen->change_eat == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/cabra/comer/cabra-comer.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/comer/cabra-comer-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/comer/cabra-comer-applyGoal.png");
                        break;
                        case BTState::do_action:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/comer/cabra-comer-doAct.png");
                        break;
                    }
                    break;
                }
                if (ia.action_chosen->change_protect == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger-applyGoal.png");
                        break;
                        case BTState::check_see_player:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger-checkSeePlayer.png");
                        break;
                        case BTState::seek_one_axis:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger-seekOneAxis.png");
                        break;
                        case BTState::reset_wait:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger-resetWait.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger-changeTarget.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger-actArrive.png");
                        break;
                    }
                    break;
                }
            break;
        }
    }
}

template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::drawAllEntities(GameCTX_t& g) const {
    //Con referencia (&) no usamos una copia usamos el array original
    auto& rencmps = g.template getComponents<RenderComponent_t>();
    int last_fps{0};
    float x,y,z;
    std::for_each(begin(rencmps), end(rencmps), [&](auto& rc) {
        //getRequiredComponent devuelve un componente a partir de otro
        auto* phy = g.template getRequiredComponent<RenderComponent_t, PhysicsComponent_t>(rc);

        if (phy != nullptr) {
            if(rc.entityNodes.node.node != nullptr){
                rc.entityNodes.node.node->setPosition(Vector3d(phy->x, phy->y, phy->z));
                rc.entityNodes.node.node->setRotation(Vector3d(phy->rotx, phy->roty, phy->rotz));

                /*cambia de color al personaje a verde cuando colisiona con algo*/
                auto* cc = g.template getRequiredComponent<RenderComponent_t, ColliderComponent_t>(rc);
                
                if (cc->properties & ColliderComponent_t::P_IsPlayer)
                {
                    if (rc.entityNodes.collides)
                    {
                      //  auto verde   = std::unique_ptr<Texture>(motor->getTexture("assets/textures/green.png"));
                      //  rc.entityNodes.node.node->setMaterialTexture(verde.get());
                        rc.entityNodes.collides = false;
                    }
                    else
                    {
                      //  auto blanco  = std::unique_ptr<Texture>(motor->getTexture("assets/textures/cuadroblanco.jpg"));
                       // rc.entityNodes.node.node->setMaterialTexture(blanco.get());
                    }
                }

                if (cc->properties == ColliderComponent_t::P_Enemy) {
                    //depuracion IA
                    auto* ia = g.template getRequiredComponent<RenderComponent_t, IAComponent_t>(rc);

                    if (ia != nullptr) {
                        checkActionsIA(rc, *ia);
                    }
                }
                
                if (!rc.entityNodes.childs.empty()) {
                    for (auto i=0; i<rc.entityNodes.childs.size(); i++) {
                        rc.entityNodes.childs.at(i).node->setRotation(Vector3d(phy->rotx, phy->roty, phy->rotz));

                        rc.entityNodes.childs.at(i).node->setPosition(Vector3d(rc.entityNodes.childs.at(i).x, rc.entityNodes.childs.at(i).y, rc.entityNodes.childs.at(i).z));
                    }        
                }
            }
        }               
    });
    motor->drawAll();
}

template <typename GameCTX_t>
bool RenderSystem_t<GameCTX_t>::update(GameCTX_t& g) const{
    auto m = motor.get();
    m->beginScene();
    drawAllEntities(g);
    //std::cout<<"fps_"<<m->getFPS()<<"\n";
    drawAllTexts(g);
    m->endScene();
    return m->run();
}

/*
template <typename GameCTX_t>
constexpr void RenderSystem_t<GameCTX_t>::renderSpriteClipped(const RenderComponent_t& ren, const PhysicsComponent_t& phy) const noexcept {
    //comprobar coordenadas de camara
    if (!m_currentCam.cam || !m_currentCam.phy) { return; }
    auto& camScr { *m_currentCam.cam };
    auto& camWrl { *m_currentCam.phy };

    //sprite -> world -> camera -> screen
    //     +pos    -poscam   +poscamscr
    struct {
        BoundingBox_t<float> world {};
        BoundingBox_t<float> camera {};
        BoundingBox_t<uint32_t> crop {};

        struct {
            uint32_t x {}, y {}, w{}, h{};
        } screen;
    } spr;

    //sprite -> world
    spr.world = {
        phy.x, //xleft
        phy.x + ren.w, //xright
        phy.y, //yup
        phy.y + ren.h //ydown
    };

    //sprite -> camera
    spr.camera = {
        spr.world.xLeft - camWrl.x, //xleft
        spr.world.xRight - camWrl.x, //xright
        spr.world.yUp - camWrl.y, //yup
        spr.world.yDown - camWrl.y //ydown
    };
    
    //sprite clipping
    if (spr.camera.xRight < 0 || spr.camera.xLeft > camScr.w ||
        spr.camera.yDown < 0 || spr.camera.yUp > camScr.h) {
        
        return;
    }

    //sprite cropping
    spr.crop = {
        //miro el trozo que sobresale, si no sobresale pongo 0
        static_cast<uint32_t>(std::round((spr.camera.xLeft < 0) ? -spr.camera.xLeft : 0)), //xleft
        static_cast<uint32_t>(std::round((spr.camera.xRight > camScr.w) ? spr.camera.xRight - camScr.w : 0)), //xright
        static_cast<uint32_t>(std::round((spr.camera.yUp < 0) ? -spr.camera.yUp : 0)), //yup
        static_cast<uint32_t>(std::round((spr.camera.yDown > camScr. h) ? spr.camera.yDown - camScr.h : 0)) //ydown
    };

    //sprite -> screen
    spr.screen = {
        static_cast<uint32_t>(std::round(spr.camera.xLeft) + camScr.srcx + spr.crop.xLeft), //x
        static_cast<uint32_t>(std::round(spr.camera.yUp) + camScr.srcy + spr.crop.yUp), //y
        ren.w - spr.crop.xLeft - spr.crop.xRight, //w
        ren.h - spr.crop.yUp - spr.crop.yDown //h
    };

    //dibujar la entidad
    auto screen = getScreenXY(spr.screen.x, spr.screen.y);
    auto sprite_it = begin(ren.sprite) + spr.crop.yUp*ren.w + spr.crop.xLeft;

    while (spr.screen.h--) {
        for (uint32_t i=0; i<spr.screen.w; ++i) {
            if (*sprite_it & 0xFF000000) {
                *screen = *sprite_it;
            }
            ++sprite_it;
            ++screen;
        }
        sprite_it += ren.w - spr.screen.w;
        screen += m_w - spr.screen.w;
    }
}

*/

/*
template <typename GameCTX_t>
constexpr void RenderSystem_t<GameCTX_t>::renderInScreenBox(uint32_t* screen, const BoundingBox_t<uint32_t>& box, uint32_t pixel) const noexcept {
    const uint32_t width { box.xRight - box.xLeft };
    uint32_t height { box.yDown - box.yUp };

    while (height--) {
        uint32_t x { width };

        while (x--) {
            *screen = pixel;
            screen++;
        }

        screen += m_w - width;
    }
}

template <typename GameCTX_t>
constexpr void RenderSystem_t<GameCTX_t>::renderInScreenLine(uint32_t* screen, uint32_t lenght, uint32_t stride, uint32_t pixel) const noexcept {
    while (lenght > 0) {
        *screen = pixel;
        --lenght;
        screen += stride;
    }
}

template <typename GameCTX_t>
constexpr void RenderSystem_t<GameCTX_t>::renderAlignedLineClipped(uint32_t x1, uint32_t x2, uint32_t y, bool yaxis, uint32_t pixel) const noexcept {
    uint32_t infinite { 4*m_w };
    uint32_t maxx { m_w };
    uint32_t maxy { m_h };
    uint32_t stride { 1 };
    uint32_t* screen { nullptr };

    //si el primer eje es el Y en vez del X, se cambian los valores de los ejes
    if (yaxis) {
        infinite = 4*m_h;
        maxx = m_h;
        maxy = m_w;
        stride = m_w;
    }

    //comprobar que la coordenada y esta en la pantalla
    if (y>=maxy) {
        return;
    }

    //definir y detectar el inicio y el final de la linea
    uint32_t xini { 0 }, xend { 0 };

    if (x1 > x2) {
        xini = x2;
        xend = x1;
    } else {
        xini = x1;
        xend = x2;
    }

    if (xini > infinite) {
        xini = 0;
    } else if (xini > maxx) {
        return;
    }
    if (xend > infinite) {
        xend = 0;
    } else if (xend > maxx) {
        xend = maxx;
    }
    if (xini > xend) {
        return;
    }

    //dibujar la linea
    if (yaxis) {
        screen = getScreenXY(y, xini);
    } else {
        screen = getScreenXY(xini, y);
    }

    renderInScreenLine(screen, xend-xini, stride, pixel);
}

template <typename GameCTX_t>
constexpr void RenderSystem_t<GameCTX_t>::renderAlignedBoxClipped(BoundingBox_t<uint32_t> box, uint32_t x, uint32_t y, uint32_t pixel) const noexcept {
    auto crop = [](uint32_t &val, uint32_t max, uint32_t inf) {
        if (val > inf) {
            val = 0;
        } else if (val > max) {
            val = max;
        }
    };

    uint32_t xinfinite { 4*m_w };
    uint32_t yinfinite { 4*m_h };

    //pasar la caja a coordenadas de la pantalla
    box.xLeft += x;
    box.xRight += x;
    box.yUp += y;
    box.yDown += y;

    //dibujar una linea en los limites de la caja
    crop(box.xLeft, m_w, xinfinite);
    crop(box.xRight, m_w, xinfinite);
    crop(box.yUp, m_h, yinfinite);
    crop(box.yDown, m_h, yinfinite);

    //no dibujar la caja si se encuentra fuera de la pantalla
    if (box.xRight == 0 || box.xLeft == m_w || box.yDown == 0 || box.yUp == m_h) {
        return;
    }

    //renderizar la caja
    renderInScreenBox(getScreenXY(box.xLeft, box.yUp), box, pixel);
}

template <typename GameCTX_t>
constexpr void RenderSystem_t<GameCTX_t>::drawBox(const BoundingBox_t<uint32_t>& box, uint32_t x, uint32_t y, uint32_t color) const noexcept {
    uint32_t x1 { x + box.xLeft };
    uint32_t x2 { x + box.xRight };
    uint32_t y1 { y + box.yUp };
    uint32_t y2 { y + box.yDown };

    renderAlignedLineClipped(x1, x2, y1, false, color);
    renderAlignedLineClipped(x1, x2, y2, false, color);
    renderAlignedLineClipped(y1, y2, x1, true, color);
    renderAlignedLineClipped(y1, y2, x2, true, color);
}

template <typename GameCTX_t>
constexpr void RenderSystem_t<GameCTX_t>::drawBoxTree(const BoundingBoxNode_t& boxNode, uint32_t x, uint32_t y, uint32_t color) const noexcept {
    if (boxNode.collided) {
        renderAlignedBoxClipped(boxNode.box, x, y, color);
    } else {
        drawBox(boxNode.box, x, y, color);
    }    

    for(auto& c : boxNode.childs) {
        drawBoxTree(c, x, y, color >> 1);
    }
}

*/


/*
template <typename GameCTX_t>
constexpr void RenderSystem_t<GameCTX_t>::drawAllCameras(const GameCTX_t& g) const {
    for (auto& cam : g.template getComponents<CameraComponent_t>()) {
        auto* phy = g.template getRequiredComponent<CameraComponent_t, PhysicsComponent_t>(cam);

        if (!phy) { return; }

        m_currentCam.cam = &cam;
        m_currentCam.phy = phy;

        drawAllEntities(g);
    }
}
*/


/*
template <typename GameCTX_t>
bool RenderSystem_t<GameCTX_t>::update(const GameCTX_t& g) const{
    auto screen = m_framebuffer.get();
    
    const auto size = m_w*m_h;
    //Ponemos el color de fondo de la pantalla en Rojo
    std::fill(screen, screen + size, kN);

    drawAllCameras(g);
    //drawAllEntities(g);

    ptc_update(screen);

    return !ptc_process_events();
}
*/