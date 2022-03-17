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
//# GameTimer sirve para gestionar los FPS a los que va el juego.    #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once
#include <chrono>
#include <thread>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

class temporizador{

public:

    temporizador(){};
    ~temporizador(){};

    void init(time_t temp_duration){

        duration = temp_duration;
        total_time = 1.00;
        initial_time = time(NULL);
        //last_time = time(NULL) - initial_time;
    }


    void count(bool direction){

        auto actual = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        //time_t actual = time(NULL);
        actual = actual / 200;
        //std::cout<<actual<<"\n";

        if(last_time!=actual){
            /*
            if(direction){
                if(total_time==2.00 || total_time==4.00 || total_time==2.50 || total_time==4.50){
                    total_time += 0.5;
                }else{
                    total_time += 1.0;
                }
            }else{
                if(total_time==2.00 || total_time==4.00){
                    total_time -= 0.5;
                }else{
                    total_time -= 1.0;
                }
            }
            */
            
            if(direction){
                total_time++;
            }else{
                total_time--;
            }
            
            
            //last_time = time(NULL);
            last_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            last_time = last_time / 200;

            if(direction){
                if(total_time >= duration+1){
                    reset();
                }
            }else{
                if(total_time < 1){
                    total_time = duration;
                }
            }
            

        }
        
    }
    

    time_t getEllapsed(){
        return total_time;
    }

    void reset(){
        total_time = 1.00;
    }

    time_t duration;

    time_t last_time;
    double total_time;
    time_t initial_time;
};




struct GameTimer_t {
    using clk = std::chrono::steady_clock;
    using nano_t = std::chrono::duration<uint64_t, std::nano>;
    using timepoint_t = std::chrono::time_point<clk, nano_t>;

    explicit GameTimer_t() noexcept {
        start();
    };

    void start() { m_start = clk::now(); }

    uint64_t ellapsed() noexcept {
        auto ns_passed { clk::now() - m_start };

        return ns_passed.count();
    }

    uint64_t waitX_ns(uint64_t ns) {
        if (ellapsed() < ns) {
            auto towait { ns - ellapsed() };

            std::this_thread::sleep_for(nano_t { towait });

            return towait;
        }

        return 0;
    }

    private:
        timepoint_t m_start;
};
