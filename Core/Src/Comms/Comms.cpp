#include "Comms/Comms.hpp"
#include "Data.hpp"
#include "BMSL.hpp"

HeapPacket* Comms::voltage_data{};
HeapPacket* Comms::current_state{};

ServerSocket* Comms::control_station = nullptr;
DatagramSocket* Comms::control_station_udp = nullptr;
//Socket* Comms::HVSCU = nullptr;

void Comms::init() {
    control_station = new ServerSocket(IPV4(BMSL_IP), CONTROL_STATION_PORT,1000,500,10);
    control_station_udp = new DatagramSocket(IPV4(BMSL_IP), CONTROL_STATION_UDP_PORT,IPV4(CONTROL_SATION_IP), CONTROL_STATION_UDP_PORT);
    //HVSCU  = new Socket(IPV4(BMSL_IP), CLIENT_PORT, IPV4(HVSCU_IP), HVSCU_PORT,false);
    add_packets();
}

void Comms::add_packets(){
    if (Data::enableVoltageRead){
        voltage_data = new HeapPacket(static_cast<uint16_t>(Comms::IDPacket::VOLTAGE),
        Data::cells[0],
        Data::cells[1],
        Data::cells[2],
        Data::cells[3],
        Data::cells[4],
        Data::cells[5],
        Data::maximum_cell_voltage,
        Data::minimum_cell_voltage,
        Data::total_voltage,
        Data::balancing,
        Data::SOC,
        Data::current);
    }

    current_state = new HeapPacket(static_cast<uint16_t>(Comms::IDPacket::STATE), BMSL::BMSL_state);
}

void Comms::send_packets(){
    if (Data::enableVoltageRead){
        control_station_udp->send_packet(*voltage_data);
    }
    control_station_udp->send_packet(*current_state);
}