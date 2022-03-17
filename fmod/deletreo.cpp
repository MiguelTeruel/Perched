//#include "vendor/FMOD/inc/fmod_studio.h"
//#include "vendor/FMOD/inc/fmod_studio.hpp"
//#include "vendor/FMOD/inc/fmod_errors.h"
//
//#include <string>
//#include <iostream>
//#include "common.h"
//#include <chrono>
//
//void ERRCHECK_FMOD1 (FMOD_RESULT result, const char * file, int line)
//{
//	if(result != FMOD_OK)
//	{
//        std::cerr << FMOD_ErrorString(result) << std::endl;
//		exit(-1);
//	}
//}
//#define ERRCHECK1(_result) ERRCHECK_FMOD1(_result, __FILE__, __LINE__)
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
//FMOD_RESULT F_CALLBACK programmerSoundCallback1(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* event, void *parameters)
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
//int ejecutar_sonido(int p, std::string palabra) {
//    int indice=0;
//
//    if (palabra[p]=='A') {
//        indice = 0;
//    } 
//    if (palabra[p]=='B') {
//        indice = 1;
//    }
//    if (palabra[p]=='C') {
//        indice = 2;
//    }
//    if (palabra[p]=='D') {
//        indice = 3;
//    }
//    if (palabra[p]=='E') {
//        indice = 4;
//    }
//    if (palabra[p]=='F') {
//        indice = 5;
//    }
//    if (palabra[p]=='G') {
//        indice = 6;
//    }
//    if (palabra[p]=='H') {
//        indice = 7;
//    }
//    if (palabra[p]=='I') {
//        indice = 8;
//    }
//    if (palabra[p]=='J') {
//        indice = 9;
//    }
//    if (palabra[p]=='K') {
//        indice = 10;
//    }
//    if (palabra[p]=='L') {
//        indice = 11;
//    }
//    if (palabra[p]=='M') {
//        indice = 12;
//    }
//    if (palabra[p]=='N') {
//        indice = 13;
//    }
//    if (palabra[p]=='O') {
//        indice = 14;
//    }
//    if (palabra[p]=='P') {
//        indice = 15;
//    }
//    if (palabra[p]=='Q') {
//        indice = 16;
//    }
//    if (palabra[p]=='R') {
//        indice = 17;
//    }
//    if (palabra[p]=='S') {
//        indice = 18;
//    }
//    if (palabra[p]=='T') {
//        indice = 19;
//    }
//    if (palabra[p]=='U') {
//        indice = 20;
//    }
//    if (palabra[p]=='V') {
//        indice = 21;
//    }
//    if (palabra[p]=='W') {
//        indice = 22;
//    }
//    if (palabra[p]=='X') {
//        indice = 23;
//    }
//    if (palabra[p]=='Y') {
//        indice = 24;
//    }
//    if (palabra[p]=='Z') {
//        indice = 25;
//    }
//
//    return indice;
//}
//
//int main1()
//{
//    FMOD::System* coreSystem;
//    FMOD::Studio::System* soundSystem;
//    std::string dialogueString;
//    
//    ERRCHECK1(FMOD::Studio::System::create(&soundSystem));
//    ERRCHECK1(soundSystem->getCoreSystem(&coreSystem));
//    ERRCHECK1(coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
//    ERRCHECK1(coreSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));
//    ERRCHECK1(soundSystem->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));
//
//    FMOD::Studio::Bank * masterBank = nullptr;
//    FMOD::Studio::Bank* stringsBank = nullptr;
//
//    ERRCHECK1(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );
//    ERRCHECK1(soundSystem->loadBankFile("assets/FMOD_BANKS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );
//
//
//    FMOD::Studio::EventDescription* eventDescription = nullptr;
//    ERRCHECK1(soundSystem->getEvent("event:/Deletrear", &eventDescription) );
//
//    FMOD::Studio::EventInstance* eventInstance = nullptr;
//    ERRCHECK1(eventDescription->createInstance(&eventInstance));
//
//    unsigned int dialogueIndex = 0;
//    static const char* const dialogue[] = {"Alpha", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel", "India", "Juliet", "Kilo", "Lima", "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo", "Sierra", "Tango", "Uniform", "Victor", "Whiskey", "Xray", "Yankee", "Zulu"};
//
//    ProgrammerSoundContext programmerSoundContext;
//    programmerSoundContext.system = soundSystem;
//    programmerSoundContext.coreSystem = coreSystem;
//    programmerSoundContext.dialogueString = dialogue[dialogueIndex];
//
//    ERRCHECK1( eventInstance->setUserData(&programmerSoundContext) );
//    ERRCHECK1( eventInstance->setCallback(programmerSoundCallback1, FMOD_STUDIO_EVENT_CALLBACK_CREATE_PROGRAMMER_SOUND | FMOD_STUDIO_EVENT_CALLBACK_DESTROY_PROGRAMMER_SOUND) );
//
//    int n = 0;
//    std::string palabra;
//    int p=0;
//    bool end=false;
//    double elapsed=0.0;
//
//    do
//    {
//        if (n==0) {
//            std::cout<< "Introduce una palabra" << std::endl;
//            std::cin >> palabra;
//            std::cout<<"Palabrita: "<<palabra<<std::endl;
//
//            p=0;
//            end=false;
//            elapsed=0.0;
//        }
//
//        if (n==1)
//        {
//            while (end!=true) {
//                //iniciar cronometro
//                auto ini_crono=std::chrono::system_clock::now();
//
//                if (elapsed>8000) {
//                    elapsed=0.0;
//
//                    p++;
//                } 
//
//                if (palabra[p]==palabra[-1]) {
//                    end=true;
//                    break;
//                }
//
//                if (elapsed==0.0) {
//                    int index=ejecutar_sonido(p, palabra);
//
//                    programmerSoundContext.dialogueString = dialogue[index];
//
//                    ERRCHECK1( eventInstance->start() );
//
//                    ERRCHECK1(soundSystem->update() );
//                }
//
//                //finalizar cronometro
//                auto fin_crono=std::chrono::system_clock::now();
//
//                elapsed += std::chrono::duration_cast<std::chrono::microseconds>(fin_crono - ini_crono).count();
//            }            
//        }       
//        
//
//        std::cout<< "Press 0 to introduce a word" << std::endl;
//        std::cout<< "Press 1 to play the letter" << std::endl;
//        std::cout<<std::endl;
//        
//        std::cout<<"Press 8 to quit"<<std::endl;
//
//        std::cin >> n;
//        std::cout << "\x1B[2J\x1B[H";
//    }while (n != 8);
//
//    ERRCHECK1(eventDescription->releaseAllInstances());
//    ERRCHECK1(masterBank->unload());
//    ERRCHECK1(stringsBank->unload());
//    ERRCHECK1(soundSystem->unloadAll());
//
//    return 0;
//}