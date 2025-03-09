#include "Comms/Comms.hpp"
#include "Data.hpp"
#include "BMSL.hpp"
HeapPacket* Comms::battery_data;
HeapPacket* Comms::current_state;

ServerSocket* Comms::control_station = nullptr;
DatagramSocket* Comms::control_station_udp = nullptr;

void Comms::start() {
    control_station = new ServerSocket(IPV4(BMSL_IP), CONTROL_STATION_PORT,1000,500,10);
    control_station_udp = new DatagramSocket(IPV4(BMSL_IP), CONTROL_STATION_UDP_PORT,IPV4(CONTROL_SATION_IP), CONTROL_STATION_UDP_PORT);
    add_packets();
}

void Comms::add_packets(){
    battery_data = new HeapPacket(static_cast<uint16_t>(Comms::IDPacket::VOLTAGE), Data::cells[0], Data::cells[1], Data::cells[2], Data::cells[3], Data::cells[4], Data::cells[5],Data::total_voltage);
    current_state = new HeapPacket(static_cast<uint16_t>(Comms::IDPacket::STATE), BMSL::BMSL_state);
}

void Comms::send_packets(){
    control_station_udp->send_packet(*battery_data);
    control_station_udp->send_packet(*current_state);
}