#ifndef DCLV_HPP
#define DCLV_HPP

#include "ST-LIB.hpp"

class DCLV {
    public:

        enum class BUFFER_STATES : uint8_t{
            HIGH,
            LOW
        };

        enum class RESET_STATES : uint8_t{
            LOW,
            HIGH
        };

        enum class PFM_STATES : uint8_t{
            INACTIVE,
            ACTIVE
        };
        
        static DualPWM* pfm;
        static PFM_STATES pfm_state;
        static DigitalOutput* buffer_en;
        static BUFFER_STATES buffer_state;
        static DigitalOutput* reset;
        static RESET_STATES reset_state;

        constexpr static float duty{50.0f};
        static uint32_t frequency;
        static uint32_t dead_time;

        static void init();
        static void toggle_buffer();
        static void toggle_reset();
        static void turn_on_pfm();
        static void turn_off_pfm();
        static void set_pfm_frequency(uint32_t freq);
        static void set_pfm_dead_time(uint32_t dt);

};

#endif