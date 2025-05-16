#include "BMSL/BMSL.hpp"

uint8_t* BMSL::BMSL_state;
BMSL_SM* BMSL::state_machine;

void BMSL::init(){
    state_machine = new BMSL_SM();
    BMSL_state = &state_machine->BMSL_SM_State_Machine.current_state;

    ProtectionManager::add_standard_protections();
    ProtectionManager::initialize();
    ProtectionManager::link_state_machine(state_machine->BMSL_SM_State_Machine, BMSL_SM::BMSL_SMStates::FAULT);
	ProtectionManager::set_id(Boards::ID::BMSA);

    Data::init();
    DCLV::init();
}

void BMSL::start(){
    Data::start();
    Comms::init();
}

void BMSL::update(){
    state_machine->read_batteries();
    state_machine->read_dclv();
    state_machine->send_packets();
    state_machine->BMSL_SM_State_Machine.check_transitions();
    state_machine->check_orders();
	ProtectionManager::check_protections();

}