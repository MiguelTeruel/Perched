#include "sound.hpp"
#include <chrono>

template <typename GameCTX_t>
SoundSystem_t<GameCTX_t>::SoundSystem_t() : sound{std::make_unique<MotorSonido_t>()}
{
    //el constructor del sistema de sonido:
    //-Inicializa los bancos de FMOD
    //-Inicializa 3 eventos, uno normal, uno de ambiente y uno con parámetro
    //-Reproduce el sonido ambiente

    InitBanks();

    InitEvent("event:/Prueba");

    //InitEvent("event:/Prueba2");

    //iniciar("event:/Prueba2");

    InitEventWithParameter("event:/Prueba3", "Cosa");
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::InitBanks()
{
    //llamamos al motor de sonido para que nos inicialice los master banks
    sound->InitBanks("fmod/assets/FMOD_BANKS/Master.bank", "fmod/assets/FMOD_BANKS/Master.strings.bank");
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::InitEvent(std::string evento)
{
    //pasandole el nombre del evento como parametro, inicializamos el evento de FMOD
    sound->InitEvent(evento);
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::InitEventWithParameter(std::string evento, std::string nombre) {
    //le pasamos al motor de sonido tanto el nombre del evento, 
    //como el nombre del parametro para inicializar el evento
    sound->InitEventWithParameter(evento, nombre);
}

template <typename GameCTX_t>
SoundSystem_t<GameCTX_t>::~SoundSystem_t()
{
    //el destructor del sistema de sonido se encarga de quitar la referencia al motor de sonido
    sound = nullptr;
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::updatePositions(GameCTX_t& g) noexcept {
    for (auto& sou: g.template getComponents<SoundComponent_t>()) {
        auto* col = g.template getRequiredComponent<SoundComponent_t, ColliderComponent_t>(sou);
        auto* phy = g.template getRequiredComponent<SoundComponent_t, PhysicsComponent_t>(sou);

        if (col != nullptr && phy != nullptr) {
            if (col->properties & ColliderComponent_t::P_IsPlayer) {
                FMOD_3D_ATTRIBUTES l_listenerAttributes {FMOD_VECTOR{phy->x, phy->y, 0}, FMOD_VECTOR{0,0,0}, FMOD_VECTOR{0,0,1}, FMOD_VECTOR{0,1,0}};
                
                sound->setListenerAttributes(&l_listenerAttributes);

                //std::cout << "Player " << l_listenerAttributes.position.x << " " << l_listenerAttributes.position.y << " " << l_listenerAttributes.position.z << "\n";

                break;
            }
        }
    }  
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::update(GameCTX_t& g) noexcept {
    updatePositions(g);
    
    for(auto& sou: g.template getComponents<SoundComponent_t>()){
        //std::cout << sou.event_id << sound->getplayback(sou.event_id).c_str() << "\n";
        if (sou.marked_for_init == 1) {
            sound->InitEvent(sou.event_id);

            if (sou.isEvent3D == true) {
                auto* phy = g.template getRequiredComponent<SoundComponent_t, PhysicsComponent_t>(sou);

                if (phy != nullptr) {
                    FMOD_3D_ATTRIBUTES l_eventAttributes {FMOD_VECTOR{phy->x, phy->y, 0}, FMOD_VECTOR{0,0,0}, FMOD_VECTOR{0,0,1}, FMOD_VECTOR{0,1,0}};

                    sound->set3DAttributes(sou.event_id, &l_eventAttributes);

                    //std::cout << "obj " << l_eventAttributes.position.x << " " << l_eventAttributes.position.y << " " << l_eventAttributes.position.z << "\n";   
                }
                
            } 
            sou.marked_for_init = 0;           
        }

        if (sou.marked_for_play == 1) {
            //std::cout << sound->getplayback(sou.event_id).c_str() << "\n";
            if (strcmp(sound->getplayback(sou.event_id).c_str(), "playing") != 0) {
                //std::cout << "hola\n";
                sound->playEvent(sou.event_id);
                sou.marked_for_play = 0;
            }            
        }

        if (sou.marked_for_stop == 1) {
            //llamar a stop event
            sound->stopEvent(sou.event_id);
            sou.marked_for_stop = 0;
        }
    }

    sound->update();
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::iniciar(std::string evento) {
    //reproduce el evento pasado por parametro
    sound->playEvent(evento);  
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::menos(std::string evento) {
    //al evento pasado por parametro, se le resta uno al valor del parametro del evento
    sound->menosValor(evento);
    sound->playEvent(evento);
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::mas(std::string evento) {
    //al evento pasado por parametro, se le suma uno al valor del parametro del evento
    sound->masValor(evento);
    sound->playEvent(evento);
}

template <typename GameCTX_t>
void SoundSystem_t<GameCTX_t>::reproduciendo(std::string evento) {
    sound->getplayback(evento);
}