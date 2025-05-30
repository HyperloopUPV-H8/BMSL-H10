#ifndef DATA_H
#define DATA_H

#include "BMS.hpp"
#include "ST-LIB.hpp"

#define N_BATTERIES 1
#define READING_PERIOD_US 10000

class Data {
    struct BMSConfig {
        static inline uint8_t spi_id{};
        static constexpr size_t n_LTC6810{1};
        static void SPI_transmit(const std::span<uint8_t> data);
        static void SPI_receive(std::span<uint8_t> buffer);
        static void SPI_CS_turn_on(void);
        static void SPI_CS_turn_off(void);
        static int32_t get_tick(void);
        static constexpr int32_t tick_resolution_us{500};
        static constexpr int32_t period_us{READING_PERIOD_US};
    };

   public:
    static inline std::array<float*, 6> cells{};
    static inline float* maximum_cell_voltage{};
    static inline float* minimum_cell_voltage{};
    static inline float* total_voltage{};

    static inline bool* balancing{};
    static inline float* SOC{};

    static void init();
    static void start();
    static void read();
    static void read_temperature();

    static inline LinearSensor<float>* current_sensor{};
    static inline float* current{};
    static inline DigitalOutput* LED_Operational{};
    static inline DigitalOutput* LED_Fault{};

    static constexpr BMS<BMSConfig> bms{};

    static inline auto& battery = bms.get_data();
    static inline auto& driver_diag = bms.get_diag();
    static inline float dummy_float{7.77};
    static inline bool dummy_bool{false};
    static inline int32_t us_counter{};

};

#endif