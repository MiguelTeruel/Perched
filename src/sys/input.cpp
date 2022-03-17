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

#include "input.hpp"
  
//template <typename GameCTX_t>
//InputSystem_t<GameCTX_t>::InputSystem_t() {
//    ptc_set_on_keypress( onkeypress );
//    ptc_set_on_keyrelease( onkeyrelease );
//
//    ms_Keyboard.reset();
//}


template <typename GameCTX_t>
InputSystem_t<GameCTX_t>::InputSystem_t(Motor3D* motor) {
    eventReceiver = motor->getReceiver();

    ms_Keyboard.reset();

    characterTimer.init(4);
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::onkeypress(keys::KEY_CODE k) {
    ms_Keyboard.keyPressed(k);
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::onkeyrelease(keys::KEY_CODE k) {
    ms_Keyboard.keyReleased(k);
}

template <typename GameCTX_t>
bool InputSystem_t<GameCTX_t>::isKeyPressed (keys::KEY_CODE k) {
    if (ms_Keyboard.isKeyPressed(k, eventReceiver)) {
        return true;
    } else {
        return false;
    }
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::setDirectionMoving(PhysicsComponent_t* phy){
    if( phy->vx != 0 || phy->vy != 0){
        phy->v_linear = 1;
    } else return;
    

    auto torient{ std::atan2(phy->vy, phy->vx) };
    if ( torient < 0 ) torient += 2*PI;
    auto vang { torient - phy->orientation };
    if ( vang > PI ) vang -= 2*PI;
    else if ( vang < -PI ) vang += 2*PI;
    phy->v_angular = std::clamp( vang, -phy->KmaxVang, phy->KmaxVang );
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::checkMusgoHielo(int lf, int du, PhysicsComponent_t& phy) {
    if (phy.pasomusgo == true) {
        if (lf == -1) {
            phy.vx = -2.0;
        }
        
        if (lf == 1) {
            phy.vx = 2.0;
        }

        if (du == -1) {
            phy.vy = -2.0;
        }
        
        if (du == 1) {
            phy.vy = 2.0;
        }

        phy.pasomusgo = false;
    } else {
        if (phy.pasohielo == true) {
            if (lf == -1) {
                phy.vx = -0.5;
            }

            if (lf == 1) {
                phy.vx = 0.5;
            }

            if (du == -1) {
                phy.vy = -0.5;
            }

            if (du == 1) {
                phy.vy = 0.5;
            }

            phy.pasohielo = false;
        } else {
            if (lf == -1) {
                phy.vx = -1.0;
            }

            if (lf == 1) {
                phy.vx = 1.0;
            }

            if (du == -1) {
                phy.vy = -1.0;
            }

            if (du == 1) {
                phy.vy = 1.0;
            }
        }
    } 
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::sumarDistancia (PhysicsComponent_t& phy, RenderComponent_t& ren, size_t pos, float x, float y) {
    ren.entityNodes.childs.at(pos).x = phy.x + x;
    ren.entityNodes.childs.at(pos).y = phy.y + y;
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::moverExtremidadesLeftRight (int lf, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren) {
    for (auto i=0; i<ren.entityNodes.childs.size(); i++) {
        if(i==4){
            //movimiento a derecha
            if (lf == 1) {
                sumarDistancia(phy, ren, i, inp.distsCabeza.disxCabDR, inp.distsCabeza.disyCab); 
            }
            
            //movimiento a izquierda
            if (lf == -1) {
                sumarDistancia(phy, ren, i, inp.distsCabeza.disxCabDL, inp.distsCabeza.disyCab);
            }
        }

        if (i==0) {
            //SUPERIOR DERECHO
            if(characterTimer.getEllapsed()==3){   
                sumarDistancia(phy, ren, i, inp.distsBrazoD.disx1, inp.distsBrazoD.disy1); 
            }else{
                sumarDistancia(phy, ren, i, inp.distsBrazoD.disx2, inp.distsBrazoD.disy1); 
            }
        } 

        if (i==1) {
            //SUPERIOR IZQUIERDO
            if(characterTimer.getEllapsed()==1 || characterTimer.getEllapsed()==2){
                sumarDistancia(phy, ren, i, inp.distsBrazoI.disx1, inp.distsBrazoI.disy1); 
            }else{
                sumarDistancia(phy, ren, i, inp.distsBrazoI.disx2, inp.distsBrazoI.disy1); 
            }
        }

        if (i==2) {
            //INFERIOR DERECHO
            if(characterTimer.getEllapsed()==3 || characterTimer.getEllapsed()==4){
                sumarDistancia(phy, ren, i, inp.distsPiernaD.disx1, inp.distsPiernaD.disy1); 
            }else{
                sumarDistancia(phy, ren, i, inp.distsPiernaD.disx2, inp.distsPiernaD.disy1); 
            } 
        } 

        if (i==3) {
            //INFERIOR IZQUIERDO
            if(characterTimer.getEllapsed()==2){
                sumarDistancia(phy, ren, i, inp.distsPiernaI.disx1, inp.distsPiernaI.disy1); 
            }else{
                sumarDistancia(phy, ren, i, inp.distsPiernaI.disx2, inp.distsPiernaI.disy1);
            }
        }
    }
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::moverExtremidadesDownUp (int du, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren) {
    for (auto i=0; i<ren.entityNodes.childs.size(); i++) {
        if(i==4){
            sumarDistancia(phy, ren, i, inp.distsCabeza.disxCabU, inp.distsCabeza.disyCab);

            if(ms_Keyboard.isKeyPressed( inp.key_LEFT, eventReceiver )){
                if (du == -1) {
                    sumarDistancia(phy, ren, i, inp.distsCabeza.disxCabDL, inp.distsCabeza.disyCab);
                }

                if (du == 1) {
                    sumarDistancia(phy, ren, i, inp.distsCabeza.disxCabUL, inp.distsCabeza.disyCab);
                }
            }else if(ms_Keyboard.isKeyPressed( inp.key_RIGHT, eventReceiver )){
                if (du == -1) {
                    sumarDistancia(phy, ren, i, inp.distsCabeza.disxCabDR, inp.distsCabeza.disyCab);
                }
                
                if (du == 1) {
                    sumarDistancia(phy, ren, i, inp.distsCabeza.disxCabUR, inp.distsCabeza.disyCab);
                }
            }
        }

        if (i==0) {
            //SUPERIOR DERECHO
            if(characterTimer.getEllapsed()==3){    
                leg_Front_D = true;
                leg_Front_I = false;
            }else{
                leg_Front_D = false;
            }

            if(leg_Front_D){
                sumarDistancia(phy, ren, i, inp.distsBrazoD.disx2, inp.distsBrazoD.disy2);
            }else{
                sumarDistancia(phy, ren, i, inp.distsBrazoD.disx2, inp.distsBrazoD.disy1);
            }

            if(characterTimer.getEllapsed()==2){
                sumarDistancia(phy, ren, i, inp.distsBrazoD.disx2, inp.distsBrazoD.disy3);
            }

            if(characterTimer.getEllapsed()==1){
                sumarDistancia(phy, ren, i, inp.distsBrazoD.disx2, inp.distsBrazoD.disy4);
            }
        } 

        if (i==1) {
            //SUPERIOR IZQUIERDO
            if(characterTimer.getEllapsed()==1){
                leg_Front_I = true;
                leg_Front_D = false;
            }else{
                leg_Front_I = false;
            }

            if(leg_Front_I){
                sumarDistancia(phy, ren, i, inp.distsBrazoI.disx2, inp.distsBrazoI.disy2);
            }else{
                sumarDistancia(phy, ren, i, inp.distsBrazoI.disx2, inp.distsBrazoI.disy1);
            }

            if(characterTimer.getEllapsed()==4){
                sumarDistancia(phy, ren, i, inp.distsBrazoI.disx2, inp.distsBrazoI.disy3);
            }

            if(characterTimer.getEllapsed()==3){
                sumarDistancia(phy, ren, i, inp.distsBrazoI.disx2, inp.distsBrazoI.disy4);
            }
        }

        if (i==2) {
            //INFERIOR DERECHO
            if(characterTimer.getEllapsed()==4){
                leg_Back_D = true;
            }else{
                leg_Back_D = false;
            }

            if(leg_Back_D){
                sumarDistancia(phy, ren, i, inp.distsPiernaD.disx2, inp.distsPiernaD.disy2);
            }else{
                sumarDistancia(phy, ren, i, inp.distsPiernaD.disx2, inp.distsPiernaD.disy1);
            }

            if(characterTimer.getEllapsed()==2){
                sumarDistancia(phy, ren, i, inp.distsPiernaD.disx2, inp.distsPiernaD.disy3);
            }   
        }

        if (i==3) {
            //INFERIOR IZQUIERDO
            if(characterTimer.getEllapsed()==2){
                leg_Back_I = true;
            }else{
                leg_Back_I = false;
            }

            if(leg_Back_I){
                sumarDistancia(phy, ren, i, inp.distsPiernaI.disx2, inp.distsPiernaI.disy2);
            }else{
                sumarDistancia(phy, ren, i, inp.distsPiernaI.disx2, inp.distsPiernaI.disy1);
            }
            
            if(characterTimer.getEllapsed()==4){
                sumarDistancia(phy, ren, i, inp.distsPiernaI.disx2, inp.distsPiernaI.disy3);
            }
        }
    }
}

template <typename GameCTX_t>
bool InputSystem_t<GameCTX_t>::update(GameCTX_t& g){

    for (auto& inp : g.template getComponents<InputComponent_t>()) {
        auto* phy = g.template getRequiredComponent<InputComponent_t, PhysicsComponent_t>(inp);
        auto* ren = g.template getRequiredComponent<InputComponent_t, RenderComponent_t>(inp);

        if (phy != nullptr) {
            phy->v_angular = phy->v_linear = 0;
            phy->vx = 0;
            phy->vy = 0;

            auto* sou = g.template getRequiredComponent<PhysicsComponent_t, SoundComponent_t>(*phy);

            if (ms_Keyboard.isKeyPressed( inp.key_LEFT, eventReceiver )) {

                if (sou != nullptr) {
                    sou->marked_for_play = 1;
                }
                
                characterTimer.count(true);

                if(characterTimer.getEllapsed()==2 || characterTimer.getEllapsed()==4){
                    checkMusgoHielo(-1, 0, *phy);                  
                }else{
                    phy->vx = 0;
                }

                if (!ren->entityNodes.childs.empty()) {
                    moverExtremidadesLeftRight(-1, inp, *phy, *ren);       
                }
            } 

            if (ms_Keyboard.isKeyPressed( inp.key_RIGHT, eventReceiver )) {
                if (sou != nullptr) {
                    sou->marked_for_stop = 1;
                }

                characterTimer.count(true);

                if(characterTimer.getEllapsed()==2 || characterTimer.getEllapsed()==4){
                    checkMusgoHielo(1, 0, *phy);   
                }else{
                    phy->vx = 0;
                }

                if (!ren->entityNodes.childs.empty()) {
                    moverExtremidadesLeftRight(1, inp, *phy, *ren);       
                }
            } 

            if (ms_Keyboard.isKeyPressed( inp.key_UP, eventReceiver )) {
                characterTimer.count(true);

                if(characterTimer.getEllapsed()==2 || characterTimer.getEllapsed()==4){
                    checkMusgoHielo(0, 1, *phy);   
                }else{
                    phy->vy = 0;
                }

                if (!ren->entityNodes.childs.empty()) {
                    moverExtremidadesDownUp(1, inp, *phy, *ren);        
                }
            }

            if (ms_Keyboard.isKeyPressed( inp.key_DOWN, eventReceiver )) {
                characterTimer.count(true);

                if(characterTimer.getEllapsed()==2 || characterTimer.getEllapsed()==4){
                    checkMusgoHielo(0, -1, *phy); 
                }else{
                    phy->vy = 0;
                }

                if (!ren->entityNodes.childs.empty()) {
                    moverExtremidadesDownUp(-1, inp, *phy, *ren);       
                }
            }
        }  
    }

    if (g.template getComponents<InputComponent_t>().size() == 0) {
        return false;
    }

    return true;
} 