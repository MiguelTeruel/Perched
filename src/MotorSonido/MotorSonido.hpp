#pragma once

#include "../../fmod/fmod/studio/inc/fmod_studio.hpp"
#include "../../fmod/fmod/core/inc/fmod.hpp"
#include <iostream>
#include <map>

struct MotorSonido_t {
    MotorSonido_t();
    ~MotorSonido_t();

    void InitBanks(std::string sMaster, std::string sMasterString);
    void AddEvent(std::string evento);
    void InitEvent(std::string evento);
    void InitEventWithParameter(std::string evento, std::string nombreParam);

    std::string getplayback(std::string evento);
    void stopEvent(std::string evento);

    void setListenerAttributes(FMOD_3D_ATTRIBUTES *att);
    void set3DAttributes(std::string evento, FMOD_3D_ATTRIBUTES *att);

    void update() const noexcept;

    void playEvent(std::string evento);

    void menosValor(std::string evento);
    void masValor(std::string evento);

    private:
        FMOD::System* coreSystem = NULL;
        FMOD::Studio::System* system = NULL;

        FMOD::Studio::Bank* masterBank = NULL;
        FMOD::Studio::Bank* stringsBank = NULL;

        FMOD::Studio::EventDescription* eveDescription = NULL;
        FMOD::Studio::EventInstance* eventInstance = NULL;

        FMOD_STUDIO_PARAMETER_DESCRIPTION paramDesc;
        FMOD_STUDIO_PARAMETER_ID surfaceID;
        float surfaceParameterValue = 1.0f;

        std::map<std::string, FMOD::Studio::EventDescription*> eventMap;
        std::map<std::string, FMOD::Studio::EventInstance*> eventInstances;
};