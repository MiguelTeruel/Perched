//#include "vendor/FMOD/inc/fmod_studio.h"
//#include "vendor/FMOD/inc/fmod_studio.hpp"
//#include "vendor/FMOD/inc/fmod_errors.h"
//
//#include <string>
//#include <iostream>
//#include "common.h"
//
//void ERRCHECK_FMOD2 (FMOD_RESULT result, const char * file, int line)
//{
//	if(result != FMOD_OK)
//	{
//        std::cerr << FMOD_ErrorString(result) << std::endl;
//		exit(-1);
//	}
//}
//#define ERRCHECK2(_result) ERRCHECK_FMOD2(_result, __FILE__, __LINE__)
//
//struct ProgrammerSoundContext
//{
//    FMOD::System* coreSystem;
//    FMOD::Studio::System* system;
//    const char* dialogueString;
//};
//
//
//#define CHECK_RESULT(op) \
//    { \
//        FMOD_RESULT res = (op); \
//        if (res != FMOD_OK) \
//        { \
//            return res; \
//        } \
//    }
//
//
//
//FMOD_RESULT F_CALLBACK programmerSoundCallback2(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* event, void *parameters)
//{
//    FMOD::Studio::EventInstance* eventInstance = (FMOD::Studio::EventInstance*)event;
//
//    if (type == FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND)
//    {
//        FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES* props = (FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES*)parameters;
//
//        // Get our context from the event instance user data
//        ProgrammerSoundContext* context = nullptr;
//        CHECK_RESULT( eventInstance->getUserData((void**)&context) );
//
//        // Find the audio file in the audio table with the key
//        FMOD_STUDIO_SOUND_INFO info;
//        CHECK_RESULT( context->system->getSoundInfo(context->dialogueString, &info) );
//
//        FMOD::Sound* sound = nullptr;
//        CHECK_RESULT( context->coreSystem->createSound(info.name_or_data, FMOD_LOOP_NORMAL | FMOD_CREATECOMPRESSEDSAMPLE | FMOD_NONBLOCKING | info.mode, &info.exinfo, &sound) );
//
//        // Pass the sound to FMOD
//        props->sound = (FMOD_SOUND*)sound;
//        props->subsoundIndex = info.subsoundindex;
//    }
//    else if (type == FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND)
//    {
//        FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES* props = (FMOD_STUDIO_PROGRAMMER_SOUND_PROPERTIES*)parameters;
//
//        // Obtain the sound
//        FMOD::Sound* sound = (FMOD::Sound*)props->sound;
//
//        // Release the sound
//        CHECK_RESULT( sound->release() );
//    }
//
//    return FMOD_OK;
//}
//
//int main2()
//{
//    FMOD::System* coreSystem;
//    FMOD::Studio::System* soundSystem;
//    std::string dialogueString;
//    
//    ERRCHECK2(FMOD::Studio::System::create(&soundSystem));
//    ERRCHECK2(soundSystem->getCoreSystem(&coreSystem));
//    ERRCHECK2(coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
//    ERRCHECK2(coreSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));
//    ERRCHECK2(soundSystem->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));
//
//    FMOD::Studio::Bank * masterBank = nullptr;
//    FMOD::Studio::Bank* stringsBank = nullptr;
//    FMOD::Studio::Bank* vocesBank = nullptr;
//
//    ERRCHECK2(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );
//    ERRCHECK2(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );
//    ERRCHECK2(soundSystem->loadBankFile("assets/FMOD_BANKS/Voces.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &vocesBank) );
//
//    unsigned int bankIndex = 0;
//    static const char* const banks[] = { "assets/FMOD_BANKS/Patrullas Bank_Normal.bank", "assets/FMOD_BANKS/Patrullas Bank_Radio.bank"};
//    
//    FMOD::Studio::Bank* localizedBank = nullptr;
//    ERRCHECK2(soundSystem->loadBankFile(banks[bankIndex], FMOD_STUDIO_LOAD_BANK_NORMAL, &localizedBank) );
//
//    FMOD::Studio::EventDescription* eventDescription = nullptr;
//    ERRCHECK2(soundSystem->getEvent("event:/Patrullas", &eventDescription) );
//
//    FMOD::Studio::EventInstance* eventInstance = nullptr;
//    ERRCHECK2(eventDescription->createInstance(&eventInstance));
//
//    unsigned int dialogueIndex = 0;
//    static const char* const dialogue[] = {"Contact", "Coverme", "Holdtheperimeter", "ImMoving", "LetsGo", "WatchyouSector"};
//
//    ProgrammerSoundContext programmerSoundContext;
//    programmerSoundContext.system = soundSystem;
//    programmerSoundContext.coreSystem = coreSystem;
//    programmerSoundContext.dialogueString = dialogue[dialogueIndex];
//
//    ERRCHECK2( eventInstance->setUserData(&programmerSoundContext) );
//    ERRCHECK2( eventInstance->setCallback(programmerSoundCallback2, FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND | FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) );
//
//    int n = 2;
//    do
//    {
//        if (n==0)
//        {
//            ERRCHECK2( localizedBank->unload() );
//
//            bankIndex = (bankIndex < 1) ? bankIndex + 1 : 0;
//            ERRCHECK2( soundSystem->loadBankFile(banks[bankIndex], FMOD_STUDIO_LOAD_BANK_NORMAL, &localizedBank) );
//        }
//
//        if (n==1)
//        {
//            dialogueIndex = (dialogueIndex < 5) ? dialogueIndex + 1 : 0;
//            programmerSoundContext.dialogueString = dialogue[dialogueIndex];
//        }
//
//        if (n==2)
//        {
//            ERRCHECK2( eventInstance->start() );
//        }
//        
//        ERRCHECK2(soundSystem->update() );
//
//        std::cout<< "Press 0 to change team" << std::endl;
//        std::cout<< "Press 1 to change voice line" << std::endl;
//        std::cout<< "Press 2 to play the event" << std::endl;
//        std::cout<<std::endl;
//        std::cout<<"Team:"<<std::endl;
//        std::string out1 = bankIndex == 0 ? ">" : " ";
//        std::cout<< out1 << " Normal team" <<std::endl;
//        out1 = bankIndex == 1 ? ">" : " ";
//        std::cout<< out1 << " Radio team" <<std::endl;
//        std::cout<<std::endl;
//        std::cout<<"Line:"<<std::endl;
//        out1 = dialogueIndex == 0 ? ">" : " ";
//        std::cout<< out1 << " Contact!" <<std::endl;
//        out1 = dialogueIndex == 1 ? ">" : " ";
//        std::cout<< out1 << " Cover me!" <<std::endl;
//        out1 = dialogueIndex == 2 ? ">" : " ";
//        std::cout<< out1 << " Hold the perimeter!" <<std::endl;
//        out1 = dialogueIndex == 3 ? ">" : " ";
//        std::cout<< out1 << " Im Moving!" <<std::endl;
//        out1 = dialogueIndex == 4 ? ">" : " ";
//        std::cout<< out1 << " Lets Go!" <<std::endl;
//        out1 = dialogueIndex == 5 ? ">" : " ";
//        std::cout<< out1 << " Watch you Sector!" <<std::endl;
//        std::cout<<std::endl;
//        std::cout<<"Press 8 to quit"<<std::endl;
//
//        std::cin >> n;
//        std::cout << "\x1B[2J\x1B[H";
//    }while (n != 8);
//
//    ERRCHECK2(eventDescription->releaseAllInstances());
//    ERRCHECK2(masterBank->unload());
//    ERRCHECK2(stringsBank->unload());
//    ERRCHECK2(localizedBank->unload());
//    ERRCHECK2(vocesBank->unload());
//    ERRCHECK2(soundSystem->unloadAll());
//
//    return 0;
//}