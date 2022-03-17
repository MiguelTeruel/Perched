#include "MotorSonido.hpp"
#include "../util/fmod/common.h"
#include <chrono>

MotorSonido_t::MotorSonido_t()
{
    ERRCHECK(FMOD::Studio::System::create(&system));
    ERRCHECK(system->getCoreSystem(&coreSystem));
    ERRCHECK(coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
    //ERRCHECK(coreSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));

    //sustituir FMOD_STUDIO_INIT_NORMAL por FMOD_STUDIO_INIT_LIVEUPDATE para profiler
    
    ERRCHECK(system->initialize(48, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));
}

MotorSonido_t::~MotorSonido_t()
{
    //el destructor del motor de sonido libera la memoria de los eventos, de los bancos
    // y del sistema de FMOD

    for(const auto& eventDesc : eventMap)
    {
        eventDesc.second->releaseAllInstances();
    }

    for(const auto& instance : eventInstances)
    {
        instance.second->release();
    }

    ERRCHECK(eventInstance->release());

    ERRCHECK(masterBank->unload());
    ERRCHECK(stringsBank->unload());
    ERRCHECK(system->release());
}

void MotorSonido_t::InitBanks(std::string sMaster, std::string sMasterString)
{
    ERRCHECK(system->loadBankFile(sMaster.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank));
    ERRCHECK(system->loadBankFile(sMasterString.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank));
}

void MotorSonido_t::AddEvent(std::string evento) {
    //nos pasan un evento por parametro y se inserta en los maps de descripciones e instancias

    ERRCHECK(system->getEvent(evento.c_str(), &eveDescription) );

    eventMap.insert({evento, eveDescription});

    ERRCHECK(eveDescription->createInstance(&eventInstance));

    eventInstances.insert({evento, eventInstance});
}

void MotorSonido_t::InitEvent(std::string evento)
{
    //nos pasan un evento por parametro, sino es encontrado en el map, se inserta en el

    auto it = eventMap.find(evento);

    if (it == eventMap.end()) {
        AddEvent(evento);
    } else {
        std::cout << "Init: El evento ya estaba creado" << evento << "\n";
    }    
}

void MotorSonido_t::InitEventWithParameter(std::string evento, std::string nombreParam) {
    //nos pasan un evento por parametro y el nombre del parametro que se modificara
    //, sino es encontrado en el map, se inserta en el

    auto it = eventMap.find(evento);

    if (it == eventMap.end()) {
        AddEvent(evento);

        eveDescription->getParameterDescriptionByName("Cosa", &paramDesc);
        surfaceID = paramDesc.id;

        eventInstance->setParameterByID(surfaceID, surfaceParameterValue);
    } else {
        std::cout << "InitP: El evento ya estaba creado" << evento << "\n";
    }
}

void MotorSonido_t::setListenerAttributes(FMOD_3D_ATTRIBUTES *att) {
    ERRCHECK( system->setListenerAttributes(0, att) );
}

void MotorSonido_t::set3DAttributes(std::string evento, FMOD_3D_ATTRIBUTES *att) {
    auto it = eventInstances.find(evento);

    if (it != eventInstances.end()) {
        ERRCHECK( it->second->set3DAttributes(att) );
    } else {
        std::cout << "3DAt: No existe ese evento" << evento << "\n";
    }     
}

void MotorSonido_t::update() const noexcept {
    ERRCHECK(system->update());
}

void MotorSonido_t::playEvent(std::string evento) {
    //nos pasan un evento por parametro, si es encontrado en el map, se reproduce

    auto it = eventInstances.find(evento);

    if (it != eventInstances.end()) {
        ERRCHECK(it->second->start());
    } else {
        std::cout << "Play: No existe ese evento" << evento << "\n";
    }    
}

void MotorSonido_t::menosValor(std::string evento) {
    //nos pasan un evento por parametro, si es encontrado en el map, 
    // se le resta uno al valor del parametro que tiene el evento

    auto it = eventInstances.find(evento);

    if (it != eventInstances.end()) {
        surfaceParameterValue = std::max(paramDesc.minimum, surfaceParameterValue - 1.0f);
        ERRCHECK(it->second->setParameterByID(surfaceID, surfaceParameterValue));
    } else {
        std::cout << "Menos: No existe ese evento" << evento << "\n";
    } 
}

void MotorSonido_t::masValor(std::string evento) {
    //nos pasan un evento por parametro, si es encontrado en el map, 
    // se le suma uno al valor del parametro que tiene el evento

    auto it = eventInstances.find(evento);

    if (it != eventInstances.end()) {
        surfaceParameterValue = std::min(surfaceParameterValue + 1.0f, paramDesc.maximum);
        ERRCHECK(it->second->setParameterByID(surfaceID, surfaceParameterValue));
    } else {
        std::cout << "Mas: No existe ese evento" << evento << "\n";
    } 
}

void MotorSonido_t::stopEvent(std::string evento) {
    auto it = eventInstances.find(evento);

    if (it != eventInstances.end()) {
        ERRCHECK(it->second->stop(FMOD_STUDIO_STOP_IMMEDIATE));
    } else {
        std::cout << "Stop: No existe ese evento" << evento << "\n";
    } 
}

std::string MotorSonido_t::getplayback(std::string evento) {
    auto it = eventInstances.find(evento);

    std::string estado = "";

    if (it != eventInstances.end()) {
        FMOD_STUDIO_PLAYBACK_STATE playback;

        it->second->getPlaybackState(&playback);

        switch (playback) {
            case FMOD_STUDIO_PLAYBACK_PLAYING:
                //playbackeStateStr = "PLAYING"; break;
                //std::cout << "playing\n";
                estado = "playing";
                break;
            case FMOD_STUDIO_PLAYBACK_STOPPED:
                //playbackeStateStr = "STOPPED"; break;
                //std::cout << "stopped\n";
                estado = "stopped";
                break;
            case FMOD_STUDIO_PLAYBACK_SUSTAINING:
                //playbackeStateStr = "SUSTAINING"; break;
                //std::cout << "sustaining\n";
                estado = "sustaining";
                break;
        }    
    } else {
        std::cout << "Playback: No existe ese evento" << evento << "\n";
    } 

    return estado;
}