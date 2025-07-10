#include "BMSL/BMSL.hpp"

void BMSL::init(){
    state_machine = new BMSL_SM();
    BMSL_state = &state_machine->general_sm.current_state;

    ProtectionManager::add_standard_protections();
    ProtectionManager::initialize();
    ProtectionManager::link_state_machine(state_machine->general_sm, BMSL_SM::general_states::FAULT);
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
    state_machine->general_sm.check_transitions();
    state_machine->check_orders();
	ProtectionManager::check_protections();

}