#ifndef DATA_H
#define DATA_H

#include "ST-LIB.hpp"
#include "BMS.hpp"

#define N_BATTERIES 1
#define READING_PERIOD_US 10000

struct bms_config {
    static inline uint8_t spi_id{};
    static constexpr size_t n_LTC6810{1};
    static void SPI_transmit(const std::span<uint8_t> data);
    static void SPI_receive(const std::span<uint8_t> buffer);
    static void SPI_CS_turn_on();
    static void SPI_CS_turn_off();
    static int32_t get_tick();
    static constexpr int32_t tick_resolution_us{500};
    static constexpr int32_t period_us{READING_PERIOD_US};
};

class Data {
   public:
    static std::array<float*, 6> cells;
    static float* maximum_cell_voltage;
    static float* minimum_cell_voltage;
    static float* total_voltage;

    static bool* balancing;
    static float* SOC;

    static void init();
    static void start();
    static void read();
    static void read_temperature();

    static LinearSensor<float>* current_sensor;
    static float* current;
    static DigitalOutput* LED_Operational;
    static DigitalOutput* LED_Fault;

    static constexpr BMS<bms_config> bms{};

    static inline auto& battery = bms.get_data();
    static inline auto& driver_diag = bms.get_diag();
    static inline float dummy_float{7.77};
    static inline bool dummy_bool{false};
    //static inline float total_voltage{};
    static inline int32_t us_counter{};

    static void read_total_voltage();
};

#endif