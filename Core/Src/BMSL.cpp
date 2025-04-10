#include "BMSL.hpp"

uint8_t* BMSL::BMSL_state;

BMSL::BMSL(){
    state_machine = new BMSL_SM();
    BMSL_state = &state_machine->BMSL_SM_State_Machine.current_state;

    ProtectionManager::add_standard_protections();
    ProtectionManager::initialize();
    ProtectionManager::link_state_machine(state_machine->BMSL_SM_State_Machine, BMSL_SM::BMSL_SMStates::FAULT);
	ProtectionManager::set_id(Boards::ID::BMSA);

    Data::init();
}

void BMSL::start(){
    Data::start();
    Comms::init();
}

void BMSL::update(){
    state_machine->read_batteries();
    state_machine->send_packets();
    state_machine->BMSL_SM_State_Machine.check_transitions();
	ProtectionManager::check_protections();

}