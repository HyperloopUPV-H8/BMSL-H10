#ifndef DATA_H
#define DATA_H

#include "BMS.hpp"
#include "ST-LIB.hpp"

#define N_BATTERIES 1
#define READING_PERIOD_US 10000
#define CAPACITY_AH 20.0f
#define REST_THRESHOLD 0.1f

#define RESISTANCE_REFERENCE 1000.0  // Ohm
#define VOLTAGE_REFERENCE 3.0        // V
#define R0 100.0                     // Ohm
#define TCR 0.00385

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
        static constexpr int32_t conv_rate_time_ms{1000};
    };

   public:
    static inline std::array<float*, 6> cells{};
    static inline float* total_voltage{};
    static inline float* GPIO_voltage{};
    static inline float* temperature{};
    static inline float* conv_rate{};

    static inline float* SOC{};

    static void init();
    static void start();
    static void read();
    static void read_temperature();

    static void update_SOC();
    static float ocv_battery_SOC(float c1,float c2, float c3, float c4, float c5, float c6);
    static float coulomb_counting_SOC(float current);
    static inline uint32_t last_reading_time{};
    static inline bool first_soc_flag {true};
    
    static inline LinearSensor<float>* current_sensor{};
    static inline float* current{};
    static inline DigitalOutput* LED_Operational{};
    static inline DigitalOutput* LED_Fault{};

    static constexpr BMS<BMSConfig> bms{};

    static inline auto& battery = bms.get_data();
    static inline int32_t us_counter{};

    private:
};

#endif