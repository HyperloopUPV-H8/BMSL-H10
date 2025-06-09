#ifndef DATA_H
#define DATA_H

#include "BMS.hpp"
#include "ST-LIB.hpp"

#define N_BATTERIES 1
#define READING_PERIOD_US 10000
#define CAPACITY_AH 20.0f
#define REST_THRESHOLD 0.1f

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

    static const inline std::vector<float> voltages = {
        2.509f, 2.541f, 2.568f, 2.593f, 2.620f, 2.643f, 2.665f, 2.689f, 2.716f,
        2.742f, 2.764f, 2.788f, 2.809f, 2.831f, 2.851f, 2.873f, 2.893f, 2.914f,
        2.934f, 2.954f, 2.973f, 2.993f, 3.013f, 3.030f, 3.048f, 3.066f, 3.088f,
        3.106f, 3.126f, 3.145f, 3.164f, 3.186f, 3.204f, 3.222f, 3.240f, 3.256f,
        3.273f, 3.289f, 3.301f, 3.317f, 3.331f, 3.342f, 3.354f, 3.362f, 3.368f,
        3.376f, 3.382f, 3.391f, 3.397f, 3.401f, 3.408f, 3.414f, 3.418f, 3.424f,
        3.428f, 3.436f, 3.441f, 3.446f, 3.452f, 3.460f, 3.466f, 3.470f, 3.477f,
        3.481f, 3.487f, 3.493f, 3.498f, 3.501f, 3.508f, 3.514f, 3.518f, 3.523f,
        3.526f, 3.531f, 3.535f, 3.541f, 3.544f, 3.549f, 3.551f, 3.558f, 3.561f,
        3.564f, 3.568f, 3.574f, 3.578f, 3.583f, 3.587f, 3.591f, 3.595f, 3.600f,
        3.604f, 3.609f, 3.613f, 3.618f, 3.624f, 3.628f, 3.634f, 3.639f, 3.645f,
        3.651f, 3.655f, 3.662f, 3.665f, 3.673f, 3.679f, 3.685f, 3.690f, 3.697f,
        3.702f, 3.707f, 3.714f, 3.718f, 3.732f, 3.733f, 3.734f, 3.735f, 3.747f,
        3.752f, 3.757f, 3.762f, 3.769f, 3.773f, 3.780f, 3.786f, 3.790f, 3.796f,
        3.800f, 3.804f, 3.810f, 3.813f, 3.819f, 3.824f, 3.828f, 3.832f, 3.836f,
        3.842f, 3.847f, 3.850f, 3.855f, 3.860f, 3.863f, 3.869f, 3.874f, 3.881f,
        3.888f, 3.892f, 3.898f, 3.906f, 3.913f, 3.920f, 3.928f, 3.934f, 3.942f,
        3.952f, 3.958f, 3.966f, 3.974f, 3.979f, 3.985f, 3.992f, 3.999f, 4.005f,
        4.010f, 4.013f, 4.018f, 4.021f, 4.022f, 4.026f, 4.029f, 4.031f, 4.034f,
        4.034f, 4.037f, 4.039f, 4.041f, 4.044f, 4.047f, 4.049f, 4.053f, 4.055f,
        4.061f, 4.064f, 4.070f, 4.077f, 4.085f, 4.095f, 4.110f, 4.126f, 4.146f,
        4.168f};

    static const inline std::vector<float> socs = {
        0.174f,  0.232f,  0.365f,  0.442f,  0.597f,  0.675f,  0.786f,  0.977f,
        1.165f,  1.422f,  1.594f,  1.809f,  2.067f,  2.325f,  2.635f,  2.996f,
        3.331f,  3.718f,  4.130f,  4.517f,  4.955f,  5.471f,  6.013f,  6.554f,
        7.122f,  7.689f,  8.231f,  8.772f,  9.340f,  9.855f,  10.371f, 10.938f,
        11.506f, 12.073f, 12.641f, 13.208f, 13.775f, 14.343f, 14.910f, 15.477f,
        16.045f, 16.612f, 17.179f, 17.747f, 18.314f, 18.881f, 19.449f, 20.016f,
        20.583f, 21.151f, 21.718f, 22.285f, 22.853f, 23.420f, 23.988f, 24.555f,
        25.122f, 25.690f, 26.257f, 26.824f, 27.392f, 27.959f, 28.526f, 29.094f,
        29.661f, 30.228f, 30.796f, 31.363f, 31.930f, 32.498f, 33.065f, 33.632f,
        34.200f, 34.767f, 35.335f, 35.902f, 36.469f, 37.037f, 37.604f, 38.171f,
        38.739f, 39.306f, 39.873f, 40.441f, 41.008f, 41.575f, 42.143f, 42.710f,
        43.277f, 43.845f, 44.412f, 44.979f, 45.547f, 46.114f, 46.682f, 47.249f,
        47.816f, 48.384f, 48.951f, 49.518f, 50.086f, 50.653f, 51.220f, 51.788f,
        52.355f, 52.922f, 53.490f, 54.057f, 54.624f, 55.192f, 55.759f, 56.326f,
        56.861f, 57.461f, 58.029f, 58.640f, 59.163f, 59.731f, 60.298f, 60.865f,
        61.433f, 62.000f, 62.567f, 63.135f, 63.702f, 64.269f, 64.837f, 65.404f,
        65.971f, 66.539f, 67.106f, 67.674f, 68.241f, 68.808f, 69.376f, 69.943f,
        70.510f, 71.078f, 71.645f, 72.212f, 72.780f, 73.347f, 73.914f, 74.482f,
        75.049f, 75.616f, 76.184f, 76.751f, 77.318f, 77.886f, 78.453f, 79.021f,
        79.588f, 80.155f, 80.723f, 81.290f, 81.857f, 82.425f, 82.992f, 83.559f,
        84.127f, 84.694f, 85.261f, 85.829f, 86.396f, 86.963f, 87.531f, 88.098f,
        88.665f, 89.233f, 90.368f, 89.800f, 90.935f, 91.502f, 92.070f, 92.637f,
        93.204f, 93.772f, 94.339f, 94.906f, 95.474f, 96.041f, 96.608f, 97.176f,
        97.743f, 98.310f, 98.878f, 99.394f, 99.799f, 99.987f};

   public:
    static inline std::array<float*, 6> cells{};
    static inline float* total_voltage{};

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
    static inline auto& driver_diag = bms.get_diag();
    static inline int32_t us_counter{};

    private:
};

#endif