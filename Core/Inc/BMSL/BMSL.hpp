#ifndef BMSL_HPP
#define BMSL_HPP

#include "ST-LIB.hpp"
#include "BMS-LIB.hpp"
#include "state_machine.hpp"
#include "Data.hpp"
#include "Comms.hpp"

class BMSL{

    public:

    BMSL_SM* state_machine;
    static uint8_t* BMSL_state;

    BMSL();

    void start();
    void update();

};





#endif