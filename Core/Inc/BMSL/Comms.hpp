#ifndef COMMS_H
#define COMMS_H

#include "ST-LIB.hpp"

class Comms {
   public:

    enum class IDPacket : uint16_t {
        BATTERY = 777,
        STATE = 778,
        DCLV = 779
    };

    enum class IDOrder : uint16_t {
        TURN_ON_PFM = 502,
        TURN_OFF_PFM = 503,
        SET_PFM_FREQUENCY = 504,
        SET_PFM_DEAD_TIME = 505
    };

    enum class Master : uint8_t {
        CONNECTED,
        DISCONNECTED
    };


    // -----------------IP's/Ports-----------------

    static const uint16_t CONTROL_STATION_PORT = 50500;
    static const uint16_t CLIENT_PORT = 50300;
    static const uint16_t CONTROL_STATION_UDP_PORT = 50400;
    static const uint16_t HVSCU_PORT = 50900;
    static const uint16_t VCU_PORT = 0;

    static constexpr std::string CONTROL_SATION_IP = "192.168.0.9";
    static constexpr std::string BMSL_IP = "192.168.1.254";
    static constexpr std::string HVSCU_IP = "192.168.1.7";
    static constexpr std::string VCU_IP = "192.168.1.2";


    // -----------------Sockets-----------------

    static inline ServerSocket* control_station{};
    static inline DatagramSocket* control_station_udp{};


    // -----------------Packets-----------------

    static inline HeapPacket* battery_data{};
    static inline HeapPacket* current_state{};
    static inline HeapPacket* dclv_data{};


    // -----------------Orders-----------------

    static inline HeapOrder* turn_on_pfm{};
    static inline HeapOrder* turn_off_pfm{};
    static inline HeapOrder* set_pfm_frequency{};
    static inline HeapOrder* set_pfm_dead_time{};


    // -----------------Functions-----------------

    static void init();
    static void add_packets();
    static void send_packets();
    static void add_orders();

    static void turn_on_pfm_callback();
    static void turn_off_pfm_callback();
    static void set_pfm_frequency_callback();
    static void set_pfm_dead_time_callback();

    // -----------------Flags-----------------
    static inline bool received_turn_on_pfm{};
    static inline bool received_turn_off_pfm{};
    static inline bool received_set_pfm_frequency{};
    static inline bool received_set_pfm_dead_time{};

};

#endif