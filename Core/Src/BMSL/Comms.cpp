#include "BMSL/Comms.hpp"
#include "BMSL/Data.hpp"
#include "BMSL/BMSL.hpp"
#include "BMSL/DCLV/DCLV.hpp"

// Callbacks
void Comms::turn_on_pfm_callback() {
    received_turn_on_pfm = true;
}
void Comms::turn_off_pfm_callback() {
    received_turn_off_pfm = true;
}
void Comms::set_pfm_frequency_callback() {
    received_set_pfm_frequency = true;
}
void Comms::set_pfm_dead_time_callback() {
    received_set_pfm_dead_time = true;
}

void Comms::init() {

    control_station = new ServerSocket(IPV4(BMSL_IP), CONTROL_STATION_PORT);
    

    control_station_udp = new DatagramSocket(IPV4(BMSL_IP), CONTROL_STATION_UDP_PORT,IPV4(CONTROL_SATION_IP), CONTROL_STATION_UDP_PORT);
    
    add_packets();
    add_orders();
}

void Comms::add_packets(){
    battery_data = new HeapPacket(static_cast<uint16_t>(Comms::IDPacket::BATTERY),
        &Data::cells[0].get(),
        &Data::cells[1].get(),
        &Data::cells[2].get(),
        &Data::cells[3].get(),
        &Data::cells[4].get(),
        &Data::cells[5].get(),
        &Data::min_cell,
        &Data::max_cell,
        &Data::total_voltage,
        &Data::SOC,
        &Data::temperature_1,
        &Data::temperature_2,
        &Data::min_temp,
        &Data::max_temp,
        Data::current);

    current_state = new HeapPacket(static_cast<uint16_t>(Comms::IDPacket::STATE), BMSL::BMSL_state);

    dclv_data = new HeapPacket(static_cast<uint16_t>(Comms::IDPacket::DCLV),
        &DCLV::pfm_state,
        &DCLV::buffer_state,
        &DCLV::reset_state,
        &DCLV::frequency,
        &DCLV::dead_time,
        DCLV::output_current,
        DCLV::input_current,
        DCLV::output_voltage,
        DCLV::input_voltage
    );
    }

void Comms::send_packets(){
    control_station_udp->send_packet(*battery_data);
    control_station_udp->send_packet(*current_state);
    control_station_udp->send_packet(*dclv_data);
}

void Comms::add_orders(){
    turn_on_pfm = new HeapOrder(static_cast<uint16_t>(Comms::IDOrder::TURN_ON_PFM),&turn_on_pfm_callback);
    turn_off_pfm = new HeapOrder(static_cast<uint16_t>(Comms::IDOrder::TURN_OFF_PFM),&turn_off_pfm_callback);
    set_pfm_frequency = new HeapOrder(static_cast<uint16_t>(Comms::IDOrder::SET_PFM_FREQUENCY),&set_pfm_frequency_callback,&DCLV::frequency);
    set_pfm_dead_time = new HeapOrder(static_cast<uint16_t>(Comms::IDOrder::SET_PFM_DEAD_TIME),&set_pfm_dead_time_callback,&DCLV::dead_time);
}