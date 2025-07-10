#include "BMSL/BMSL.hpp"

void BMSL::init() {
    state_machine = new BMSL_SM();
    BMSL_state = &state_machine->general_sm.current_state;

    ProtectionManager::add_standard_protections();
    //add_protections();
    ProtectionManager::initialize();
    ProtectionManager::link_state_machine(state_machine->general_sm,
                                          BMSL_SM::general_states::FAULT);
    ProtectionManager::set_id(Boards::ID::BMSA);

    Data::init();
    DCLV::init();
}

void BMSL::start() {
    Data::start();
    Comms::init();
}

void BMSL::set_protection_name(Protection* protection,
                               const std::string& name) {
    protection->set_name((char*)malloc(name.size() + 1));
    sprintf(protection->get_name(), "%s", name.c_str());
}

void BMSL::add_protections() {
    Protection* soc_below_protection = &ProtectionManager::_add_protection(
        Data::SOC, Boundary<float, BELOW>{25.0f});
    set_protection_name(soc_below_protection, "SOC below 20%");

    Protection* soc_above_protection = &ProtectionManager::_add_protection(
        Data::SOC, Boundary<float, ABOVE>{75.0f});
    set_protection_name(soc_above_protection, "SOC above 20%");

    Protection* temperature_protection = &ProtectionManager::_add_protection(
        Data::temperature, Boundary<float, ABOVE>{50.0f});
    set_protection_name(temperature_protection, "Battery above 50ºC");

    Protection* bms_disconnexion_protection = &ProtectionManager::_add_protection(
        Data::conv_rate, Boundary<float, BELOW>{0.5f});
    set_protection_name(bms_disconnexion_protection, "BMS disconnection");
}

void BMSL::update() {
    state_machine->read_batteries();
    state_machine->read_dclv();
    state_machine->send_packets();
    state_machine->general_sm.check_transitions();
    state_machine->check_orders();
    ProtectionManager::check_protections();
}