#ifndef COMMS_H
#define COMMS_H

#include "ST-LIB.hpp"

class Comms {
   public:

    enum class IDPacket : uint16_t {
        VOLTAGE = 777,
        STATE = 778
    };


    // -----------------IP's/Ports-----------------

    static const uint16_t CONTROL_STATION_PORT = 50500;
    static const uint16_t CLIENT_PORT = 50300;
    static const uint16_t CONTROL_STATION_UDP_PORT = 50400;
    static const uint16_t HVSCU_PORT = 50900;

    static constexpr std::string CONTROL_SATION_IP = "192.168.0.9";
    static constexpr std::string BMSL_IP = "192.168.1.254";
    static constexpr std::string HVSCU_IP = "192.168.1.7";


    // -----------------Sockets-----------------

    //static ServerSocket* control_station;
    static DatagramSocket* control_station_udp;
    static Socket* HVSCU;


    // -----------------Packets-----------------

    static HeapPacket* voltage_data;
    static HeapPacket* current_state;


    // -----------------Functions-----------------

    static void init();
    static void add_packets();
    static void send_packets();
};

#endif