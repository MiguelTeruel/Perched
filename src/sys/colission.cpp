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

#include "colission.hpp"

template <typename GameCTX_t>
ColissionSystem_t<GameCTX_t>::ColissionSystem_t(int32_t xmin, int32_t xmax, int32_t ymin, int32_t ymax) 
    : m_xmin (xmin), m_xmax (xmax), m_ymin (ymin), m_ymax (ymax) {

    //std::cout << "mxmin: " << m_xmin << " mxmax: " << m_xmax << " mymin: " << m_ymin << " mymax: " << m_ymax << "\n";
}

template <typename GameCTX_t>
void ColissionSystem_t<GameCTX_t>::sizeMapa(int32_t xmin, int32_t xmax, int32_t ymin, int32_t ymax) noexcept {
    m_xmin = xmin;
    m_xmax = xmax;
    m_ymin = ymin;
    m_ymax = ymax;

    //std::cout << "mxmin: " << m_xmin << " mxmax: " << m_xmax << " mymin: " << m_ymin << " mymax: " << m_ymax << "\n";
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::borrarAlBorde(GameCTX_t& g, const ColliderComponent_t& inflicter) const noexcept {
    auto* inHe = g.template getRequiredComponent<ColliderComponent_t, HealthComponent_t>(inflicter);

    if (!inHe) { return; }

    inHe->damage = 1;
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::checkMapColision(GameCTX_t& g, const ColliderComponent_t& col, PhysicsComponent_t& phy) const noexcept {
    
    if (phy.x < m_xmin || phy.x > m_xmax) {
        if (col.properties == ColliderComponent_t::P_Damages) {
            borrarAlBorde(g, col);
        } else {
            phy.x = phy.last_x;
            //std::cout << "choco x \n";
            //phy.x -= phy.vx; 
            //phy.vx = -phy.vx; 
        }
    }

    if (phy.y < m_ymin || phy.y > m_ymax) {
        if (col.properties == ColliderComponent_t::P_Damages) {
            borrarAlBorde(g, col);
        } else {
            phy.y = phy.last_y;
            //std::cout << "choco y\n";
            //phy.y -= phy.vy; 
            //phy.vy = -phy.vy;

            //if (phy.gravity) {
            //    phy.vy = 0;
            //} else {
            //    phy.vy = -phy.vy; 
            //}
        } 
    }
}

template <typename GameCTX_t>
BoundingBox_t<float> ColissionSystem_t<GameCTX_t>::moveToWorldCoords(const BoundingBox_t<float>& box, float x, float y, float z) const noexcept {
    BoundingBox_t<float> screenBox {
        x + box.xLeft,
        x + box.xRight,
        y + box.yUp,
        y + box.yDown,
        z + box.zFront,
        z + box.zBack
    };

    return screenBox;
}

/****************************************************************************************************/
/************************************COMPROBAR COLISION NORMAL***************************************/
/****************************************************************************************************/

template <typename GameCTX_t>
constexpr bool ColissionSystem_t<GameCTX_t>::checkObjectCercaCollision(float dist, BoundingBoxNode_t& bn1, BoundingBoxNode_t& bn2, const PhysicsComponent_t& phy1, const PhysicsComponent_t& phy2) const noexcept {
    auto b1 = moveToWorldCoords(bn1.box, phy1.x + bn1.disX, phy1.y + bn1.disY, phy1.z);
    auto b2 = moveToWorldCoords(bn2.box, phy2.x + bn2.disX, phy2.y + bn2.disY, phy2.z);

    auto checkIntervals = [](float L1, float R1, float L2, float R2) {
        if (L2 > R1) { return false; }
        if (L1 > R2) { return false; }

        return true;
    };

    //E1  L1----R1                     L1----R1
    //E2           L2----R2  L2----R2

    if (checkIntervals(b1.xLeft - dist, b1.xRight + dist, b2.xLeft - dist, b2.xRight + dist)) {
        if (checkIntervals(b1.yUp - dist, b1.yDown + dist, b2.yUp - dist, b2.yDown + dist)) {
            if (checkIntervals(b1.zFront - dist, b1.zBack + dist, b2.zFront - dist, b2.zBack + dist)) {
                //collision
                bn1.collided = true;
                bn2.collided = true;

                return true;
            }
        }
    }

    return false;
}

/****************************************************************************************************/
/************************************COMPROBAR SAVE PLAYER*******************************************/
/****************************************************************************************************/
template <typename GameCTX_t>
constexpr bool ColissionSystem_t<GameCTX_t>::checkPlayerSave(BoundingBoxNode_t& saliente, BoundingBoxNode_t& player, const PhysicsComponent_t& salientephy, const PhysicsComponent_t& playerphy) const noexcept {
    auto saliente1 = moveToWorldCoords(saliente.box, salientephy.x + saliente.disX, salientephy.y + saliente.disY, salientephy.z);
    auto player2   = moveToWorldCoords(player.box, playerphy.x + player.disX, playerphy.y + player.disY, playerphy.z);

    auto checkIntervals = [](float L1, float R1, float L2, float R2) {
        if (L2 > R1) { return false; }
        if (L1 > R2) { return false; }

        return true;
    };

    //E1  L1----R1                     L1----R1
    //E2           L2----R2  L2----R2

    if (checkIntervals(saliente1.xLeft, saliente1.xRight, player2.xLeft, player2.xRight)) {
        if (player2.yUp < saliente1.yDown) {
            //Debajo del saliente
            return true;
        }
        else{
            return false;
        }
    }

    return false;
}

template<typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::checkIfPlayerSave(GameCTX_t& g) const noexcept{
    //auto& bb = g.template getSingletonComponent<BlackboardComponent_t>();
    auto& bb = g.template getBlackBoard();
    auto* player =  g.template getEntityByID(bb.playerID);

    if (player) {
        auto* phyPlay = player->template getComponent<PhysicsComponent_t>();
        auto* collPlay = player->template getComponent<ColliderComponent_t>();

        if (phyPlay &&  collPlay) {

            for(std::size_t i = 0; i < bb.salientes_bb.size(); i++){
                auto* phySal = bb.salientes_bb[i]->template getComponent<PhysicsComponent_t>();
                auto* collSal = bb.salientes_bb[i]->template getComponent<ColliderComponent_t>();
                if (!phySal || !collSal) { continue; }

                for (auto& boxPlay: collPlay->boxes) {
                    for (auto& boxSal: collSal->boxes) {
                        if(checkPlayerSave(boxSal, boxPlay, *phySal, *phyPlay)){
                            bb.player_is_save = true;
                            break;
                        }
                        else{
                            bb.player_is_save = false;
                        }
                    }
                }
            }
        }
    }
}

/****************************************************************************************************/
/************************************EFECTO COLISION INTERACTUABLE***********************************/
/****************************************************************************************************/

template <typename GameCTX_t>
void ColissionSystem_t<GameCTX_t>::resetArbusto(GameCTX_t& g) noexcept {
    arbusto = 0;
}

template <typename GameCTX_t>
void ColissionSystem_t<GameCTX_t>::addArbusto(GameCTX_t& g) noexcept {
    arbusto++;
}

template <typename GameCTX_t>
void ColissionSystem_t<GameCTX_t>::resetCascada(GameCTX_t& g) noexcept {
    cascada = 0;
}

template <typename GameCTX_t>
void ColissionSystem_t<GameCTX_t>::addCascada(GameCTX_t& g) noexcept {
    cascada++;
}

template <typename GameCTX_t>
void ColissionSystem_t<GameCTX_t>::checkInteractuable(GameCTX_t& g){
    for(auto& c1 : g.template getComponents<ColliderComponent_t>()) {
        if (c1.properties & ColliderComponent_t::P_IsPlayer) {
            auto* phy = g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(c1);

            for(auto& c2 : g.template getComponents<ColliderComponent_t>()) {
                auto* phy2 = g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(c2);

                for (auto& boxC1: c1.boxes) {
                    for (auto& boxC2: c2.boxes) {
                        if (checkObjectCercaCollision(50, boxC1, boxC2, *phy, *phy2)) {
                            boxC1.collided = false;
                            boxC2.collided = false;

                            if (c2.properties == ColliderComponent_t::P_Cascada) { 
                                if (cascada == 1) {                            
                                    auto* sta = g.template getRequiredComponent<ColliderComponent_t, StaminaComponent_t>(c1);

                                    sta->cantStamina = sta->maxStamina;
                                }
                            } else {
                                if (c2.properties == ColliderComponent_t::P_Nido) {
                                    for (auto& fol : g.template getComponents<FollowComponent_t>()) {
                                        if (fol.followEntityID == phy2->getEntityID()) {

                                            fol.followEntityID = phy->getEntityID();
                                            fol.x = fol.x;
                                            fol.y = 0;
                                            fol.z = fol.z;

                                            setCrias(g);
                                        }
                                    } 
                                } else {
                                    if (c2.properties == ColliderComponent_t::P_Arbusto) {
                                        if (arbusto == 1) {
                                            auto* he = g.template getRequiredComponent<ColliderComponent_t, HealthComponent_t>(c1);
                                            
                                            if (he->health < 3) {
                                                he->health++;
                                            }                                    
                                        } 
                                    } 
                                }
                            }              
                        }
                    }
                }
            }

            continue;
        }
    }
}

/****************************************************************************************************/
/*******************************COMPROBAR COLISION AGUJERO-TRAMPOLIN*********************************/
/****************************************************************************************************/

template <typename GameCTX_t>
int ColissionSystem_t<GameCTX_t>::checkAgujeros(GameCTX_t& g){
    for(auto& c1 : g.template getComponents<ColliderComponent_t>()) {
        if (c1.properties & ColliderComponent_t::P_IsPlayer) {
            auto* phy = g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(c1);

            for(auto& c2 : g.template getComponents<ColliderComponent_t>()) {
                if ((c2.properties == ColliderComponent_t::P_Agujero) || (c2.properties == ColliderComponent_t::P_Trampolin)) {
                    auto* phy2 = g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(c2);

                    for (auto& boxC1: c1.boxes) {
                        for (auto& boxC2: c2.boxes) {
                            if (checkObjectCercaCollision(50, boxC1, boxC2, *phy, *phy2)) {
                                boxC1.collided = false;
                                boxC2.collided = false;

                                if (c2.quesubirbajar == 1) {
                                    return 1;
                                }
                                if (c2.quesubirbajar == 2) {
                                    return 2;
                                }
                                if (c2.quesubirbajar == 3) {
                                    return 3;
                                }              
                            }
                        }
                    }
                }
            }

            continue;
        }
    }
    return 0;
}

/****************************************************************************************************/
/***************************************EFECTO COLISION NORMAL***************************************/
/****************************************************************************************************/

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::inflictDamage(GameCTX_t& g, ColliderComponent_t& inflicter, ColliderComponent_t& receiver) const noexcept {
    auto* reHe = g.template getRequiredComponent<ColliderComponent_t, HealthComponent_t>(receiver);
    auto* inHe = g.template getRequiredComponent<ColliderComponent_t, HealthComponent_t>(inflicter);

    if (!reHe || !inHe) { return; }
    if (reHe->hurtCooldown == 0){
        reHe->damage += inHe->damageInflicted;
        reHe->hurtCooldown = 40;
    }
    
    inHe->damage += inHe->selfDamageOnInfliction;
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::puntoControl(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid) const noexcept {
    auto control = solid.getEntityID();

    auto* ct = g.template getRequiredComponent<ColliderComponent_t, ControlComponent_t>(mobile);
    auto* est = g.template getRequiredComponent<ColliderComponent_t, StaminaComponent_t>(mobile);

    if(est!=nullptr){
        est->cantStamina = est->maxStamina;
    }

    if (std::find(ct->puntosControl.begin(), ct->puntosControl.end(), control) == ct->puntosControl.end()) {
        ct->puntosControl.emplace_back(control);
    } else {
        ct->puntosControl.erase(std::find(ct->puntosControl.begin(), ct->puntosControl.end(), control));
        ct->puntosControl.emplace_back(control);
    }   
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::semilla(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid) const noexcept {
    auto* pun = g.template getRequiredComponent<ColliderComponent_t, PuntosComponent_t>(mobile);

    if (pun != nullptr) {
        pun->puntos += pun->cantSumable;

        auto* he = g.template getRequiredComponent<ColliderComponent_t, HealthComponent_t>(solid);

        if (!he) { return; }

        he->damage++;       
    }   
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::acelerar(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid) const noexcept {
    auto* moPhy = g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(mobile);
    moPhy->pasomusgo = true;
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::decelerar(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid) const noexcept {
    auto* moPhy = g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(mobile);
    moPhy->pasohielo = true;
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::undoCollision(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid, BoundingBoxNode_t& col1, BoundingBoxNode_t& col2) const noexcept {
    auto* moPhy = g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(mobile);
    auto* soPhy = g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(solid);

    if (!moPhy || !soPhy) { return; }

    //transladar a coordenadas de pantalla
    auto solidBox  = moveToWorldCoords(col2.box, soPhy->x + col2.disX, soPhy->y + col2.disY, soPhy->z);
    auto mobileBox = moveToWorldCoords(col1.box, moPhy->x + col1.disX, moPhy->y + col1.disY, moPhy->z);
    
    col1.collided = false;
    col2.collided = false;

    //        |---|  //Right
    //|---|          //Left
    //|-----------|  //Center
    //    |---|      //Center
    //   |-----|
    // xLeft  xRight

    //calcular interseccion
    auto intervalIntersection = [](float Ml, float Mr, float Sl, float Sr) -> float {
        if (Ml < Sl) {
            if (Mr < Sr) {
                //left
                return Sl - Mr;
            }
        } else if (Mr > Sr) {
            //right
            return Sr - Ml;
        }

        return 0;
    };

    float undoX = intervalIntersection (mobileBox.xLeft, mobileBox.xRight, solidBox.xLeft, solidBox.xRight);

    float undoY = intervalIntersection (mobileBox.yUp, mobileBox.yDown, solidBox.yUp, solidBox.yDown);

    float undoZ = intervalIntersection (mobileBox.zFront, mobileBox.zBack, solidBox.zFront, solidBox.zBack);

    if (undoX == 0 || (undoY != 0 && std::abs(undoY) <= std::abs(undoX))) {
        moPhy->y += undoY+0.01;
        //moPhy->vy = 0;

        moPhy->vx *= (moPhy->friction * soPhy->friction);
    } else { //if (undoY == 0 || (std::abs(undoY) > std::abs(undoX)))
        moPhy->x += undoX+0.01;
        //moPhy->vx = 0;

        moPhy->vy *= (moPhy->friction * soPhy->friction);
    } 
}

/****************************************************************************************************/
/***********************************ELEGIR EFECTO COLISION NORMAL************************************/
/****************************************************************************************************/

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::react2collision(GameCTX_t& g, ColliderComponent_t& c1, ColliderComponent_t& c2, BoundingBoxNode_t& col1, BoundingBoxNode_t& col2) noexcept {
    using CP = ColliderComponent_t;
    CP *player { &c1 }, *other { &c2 };

    if (c2.properties & CP::P_IsPlayer) {
        std::swap(player, other);
    } else if (!(c1.properties & CP::P_IsPlayer)) {
        // Miro a ver si alguno es ia para llamar a su comprobacion de colisiones
        if(c1.properties == CP::P_Enemy || c2.properties == CP::P_Enemy){
            react2collision_ia(g, c1, c2, col1, col2);
            return;
        }else{
            if (c1.properties == CP::P_Semilla) {
                col1.collided = false;
                col2.collided = false;
                return;
            } else {
                col1.collided = false;
                col2.collided = false;
                return;
            }  
        }       
    }

    if (other->properties == CP::P_Damages) {
        //daño
        inflictDamage(g, *other, *player);
    }

    if(other->properties == CP::P_EnemyVisual){	
            //undoCollision(g, *player, *other);
            
        auto& bb = g.template getBlackBoard();
        auto* phy = g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(*player);

        auto* ia = g.template getRequiredComponent<ColliderComponent_t, IAComponent_t>(*other);

        ia->visto = true;

        col1.collided = false;
        col2.collided = false;
        
        bb.player_tx = phy->x;
        bb.player_ty = phy->y;

    }

    if (other->properties ==  CP::P_Enemy) {	
        //daño
        inflictDamage(g, *other, *player);

        col1.collided = false;
        col2.collided = false;
    }
    
    if ((other->properties == CP::P_Agujero) || (other->properties == CP::P_Trampolin) 
        || (other->properties == CP::P_PlanoS) || (other->properties == CP::P_Saliente)
        || (other->properties == CP::P_IsSolid)) {
        undoCollision(g, *player, *other, col1, col2);
    } 
    
    if (other->properties == CP::P_Control) {
        puntoControl(g, *player, *other);

        col1.collided = false;
        col2.collided = false;
    }
    
    if (other->properties == CP::P_Semilla) {
        semilla(g, *player, *other);

        col1.collided = false;
        col2.collided = false;
    }

    if ((other->properties == CP::P_Cria) || (other->properties == CP::P_Nido) ||
        (other->properties == CP::P_Cascada) || (other->properties == CP::P_Arbusto)) {
        col1.collided = false;
        col2.collided = false;
    }

    if(other->properties == CP::P_Accelerate){
        acelerar(g, *player, *other);
        col1.collided = false;
        col2.collided = false;
    }

    if(other->properties == CP::P_Deccelerate){
        decelerar(g, *player, *other);
        col1.collided = false;
        col2.collided = false;
    }

    if (other->properties == CP::P_Meta) {
        undoCollision(g, *player, *other, col1, col2);
        //llegaMeta = true;
        setMeta(g, true);
    }
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::react2collision_ia(GameCTX_t& g, ColliderComponent_t& c1, ColliderComponent_t& c2, BoundingBoxNode_t& col1, BoundingBoxNode_t& col2) noexcept {
    using CP = ColliderComponent_t;
    CP *enemy { &c1 }, *other { &c2 };

    if (c2.properties == CP::P_Enemy) {
        std::swap(enemy, other);
    } else if (!(c1.properties == CP::P_Enemy)) {
        
        return;
    }

    if (other->properties == CP::P_IsSolid) {
        undoCollision(g, *enemy, *other, col1, col2);
    } 
    if (other->properties == CP::P_Telaranya){
        col1.collided = false;
        col2.collided = false;
    }
}

template <typename GameCTX_t>
bool ColissionSystem_t<GameCTX_t>::update(GameCTX_t& g) {
    auto& colVeccmp { g.template getComponents<ColliderComponent_t>() };

    //auto& bb = g.template getSingletonComponent<BlackboardComponent_t>();
    auto& bb = g.template getBlackBoard();
    bb.player_tx = 0;
    bb.player_ty = 0;
    

    checkIfPlayerSave(g);

    std::function<void(BoundingBoxNode_t&)> collidersFalse = [&](BoundingBoxNode_t& b) {
        b.collided = false;
    };

    for (auto& c : colVeccmp) {
        for (auto& box: c.boxes) {
            collidersFalse(box);
        }
    }

    for(std::size_t i=0; i<colVeccmp.size(); ++i){
        auto& c1 { colVeccmp[i] };

        //getRequiredComponent devuelve un componente a partir de otro
        auto* phy = g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(c1);

        if (!phy) { continue; }

        //limites con el mapa
        checkMapColision(g, c1, *phy); 

        //colisiones entre cosas
        for (std::size_t j=i+1; j<colVeccmp.size(); ++j) {
            auto& c2 { colVeccmp[j] };

            auto* phy2 = g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(c2);

            if (!phy2) { continue; }
                
            RenderComponent_t* r1 { g.template getRequiredComponent<ColliderComponent_t, RenderComponent_t>(c1) };
            RenderComponent_t* r2  { g.template getRequiredComponent<ColliderComponent_t, RenderComponent_t>(c2) };

            for (auto& boxC1: c1.boxes) {
                for (auto& boxC2: c2.boxes) {
                    if (!(c1.nomover == false || c2.nomover == false)) {
                        if (checkObjectCercaCollision(0, boxC1, boxC2, *phy, *phy2)) {
                            react2collision(g, c1, c2, boxC1, boxC2);
                            if (c1.properties & ColliderComponent_t::P_IsPlayer)
                            {
                                r1->entityNodes.collides = true;
                            }
                            else if (c2.properties & ColliderComponent_t::P_IsPlayer)
                            {
                                r2->entityNodes.collides = true;
                            }
                        }
                    }
                }
            } 
        }
    }

    return true;
}  

template <typename GameCTX_t>
bool ColissionSystem_t<GameCTX_t>::getMeta(GameCTX_t& g) noexcept {
    return llegaMeta;
}

template <typename GameCTX_t>
void ColissionSystem_t<GameCTX_t>::setMeta(GameCTX_t& g, bool llegar) noexcept {
    llegaMeta = llegar;
}

template <typename GameCTX_t>
int ColissionSystem_t<GameCTX_t>::getCrias(GameCTX_t& g) noexcept {
    return criasRescatadas;
}

template <typename GameCTX_t>
void ColissionSystem_t<GameCTX_t>::setCrias(GameCTX_t& g) noexcept {
    criasRescatadas++;
}