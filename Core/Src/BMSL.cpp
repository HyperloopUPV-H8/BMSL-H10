#include "BMSL.hpp"
uint8_t* BMSL::BMSL_state;
BMSL::BMSL(){
    state_machine = new BMSL_SM();
    BMSL_state = &state_machine->BMSL_SM_State_Machine.current_state;
}

void BMSL::init(){
    Data::init();
    Comms::start();
}

void BMSL::update(){
    state_machine->read_batteries();
    state_machine->send_packets();
    state_machine->BMSL_SM_State_Machine.check_transitions();
}