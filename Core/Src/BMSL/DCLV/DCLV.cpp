#include "BMSL/DCLV/DCLV.hpp"
#include "BMSL/Data.hpp"

DualPWM* DCLV::pfm;
DCLV::PFM_STATES DCLV::pfm_state;
DigitalOutput* DCLV::buffer_en;
DCLV::BUFFER_STATES DCLV::buffer_state;
DigitalOutput* DCLV::reset;
DCLV::RESET_STATES DCLV::reset_state;
uint32_t DCLV::frequency{0};
uint32_t DCLV::dead_time{300};

void DCLV::init() {
    pfm = new DualPWM(PWM_HIGH, PWM_LOW);
    pfm_state = PFM_STATES::INACTIVE;
    buffer_en = new DigitalOutput(PWM_BUFFER_EN);  // LOW ACTIVE
    reset = new DigitalOutput(PWM_RESET);

    pfm->set_duty_cycle(duty);
    pfm->set_frequency(frequency);
    pfm->set_dead_time(std::chrono::nanoseconds(dead_time));

    buffer_en->turn_on();
    buffer_state = BUFFER_STATES::HIGH;
}

void DCLV::turn_on_pfm() {
    buffer_en->turn_off();
    buffer_state = BUFFER_STATES::LOW;
    reset->turn_on();
    reset_state = RESET_STATES::HIGH;
    pfm->turn_on();
    pfm_state = PFM_STATES::ACTIVE;
}

void DCLV::turn_off_pfm(){
    buffer_en->turn_on();
    buffer_state = BUFFER_STATES::HIGH;
    reset->turn_off();
    reset_state = RESET_STATES::LOW;
    pfm->turn_off();
    pfm_state = PFM_STATES::INACTIVE;
}

void DCLV::set_pfm_frequency(uint32_t frequency) {
    pfm->set_frequency(frequency);
}

void DCLV::set_pfm_dead_time(uint32_t dead_time) {
    pfm->set_dead_time(std::chrono::nanoseconds(dead_time));
}