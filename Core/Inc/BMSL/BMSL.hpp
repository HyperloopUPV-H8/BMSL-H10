#ifndef BMSL_HPP
#define BMSL_HPP

#include "ST-LIB.hpp"
#include "BMS.hpp"
#include "state_machine.hpp"
#include "Data.hpp"
#include "Comms.hpp"
#include "DCLV/DCLV.hpp"


class BMSL{

    public:

    static inline BMSL_SM* state_machine{};
    static inline uint8_t* BMSL_state{};

    
    static void init();
    static void start(Comms::Master master_connection);
    static void update();

};





#endif