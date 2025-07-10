#ifndef BMSL_HPP
#define BMSL_HPP

#include "BMS.hpp"
#include "Comms.hpp"
#include "DCLV/DCLV.hpp"
#include "Data.hpp"
#include "ST-LIB.hpp"
#include "state_machine.hpp"

class BMSL {
    static void set_protection_name(Protection* protection, const std::string& name);

   public:
    static inline BMSL_SM* state_machine{};
    static inline uint8_t* BMSL_state{};

    static void init();
    static void start();
    static void update();
    static void add_protections();
};

#endif