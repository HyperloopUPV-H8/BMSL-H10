#ifndef BMSL_HPP
#define BMSL_HPP

#include "ST-LIB.hpp"
#include "BMS-LIB.hpp"
#include "state_machine.hpp"
#include "Data.hpp"
#include "Comms.hpp"
#include "DCLV/DCLV.hpp"

class BMSL{

    public:

    static BMSL_SM* state_machine;
    static uint8_t* BMSL_state;

    
    static void init();
    static void start();
    static void update();

};





#endif