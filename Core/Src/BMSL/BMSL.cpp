#include "BMSL/BMSL.hpp"

void BMSL::init() {
    state_machine = new BMSL_SM();
    BMSL_state = &state_machine->general_sm.current_state;

    ProtectionManager::link_state_machine(state_machine->general_sm,
                                          BMSL_SM::general_states::FAULT);
    ProtectionManager::add_standard_protections();
    //add_protections();
    ProtectionManager::initialize();
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
    Protection* soc_protection = &ProtectionManager::_add_protection(
        &Data::SOC, Boundary<float, OUT_OF_RANGE>{24.0f, 80.0f});
    set_protection_name(soc_protection, "SOC");

    /* Protection* temperature_1_protection = &ProtectionManager::_add_protection(
        &Data::temperature[0], Boundary<float, OUT_OF_RANGE>{10.0f, 50.0f});
    set_protection_name(temperature_1_protection, "Temperature 1");

    Protection* temperature_2_protection = &ProtectionManager::_add_protection(
        &Data::temperature[1], Boundary<float, OUT_OF_RANGE>{10.0f, 50.0f});
    set_protection_name(temperature_2_protection, "Temperature 2");

    Protection* temperature_3_protection = &ProtectionManager::_add_protection(
        &Data::temperature[2], Boundary<float, OUT_OF_RANGE>{10.0f, 50.0f});
    set_protection_name(temperature_3_protection, "Temperature 3");

    Protection* temperature_4_protection = &ProtectionManager::_add_protection(
        &Data::temperature[3], Boundary<float, OUT_OF_RANGE>{10.0f, 50.0f});
    set_protection_name(temperature_4_protection, "Temperature 4");

    Protection* bms_disconnection_protection =
        &ProtectionManager::_add_protection(&Data::conv_rate,
                                            Boundary<float, BELOW>{0.5f});
    set_protection_name(bms_disconnection_protection, "BMS Conversion Rate"); */
}

void BMSL::update() {
    state_machine->read_batteries();
    state_machine->read_dclv();
    state_machine->send_packets();
    state_machine->general_sm.check_transitions();
    state_machine->check_orders();
}