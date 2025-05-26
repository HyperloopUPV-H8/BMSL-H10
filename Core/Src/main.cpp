#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif

#include "ST-LIB.hpp"
#include "BMSL/BMSL.hpp"

int main(void) {


    BMSL::init();
    STLIB::start("00:00:00:00:01:FE","192.168.1.254","255.255.255.0");
    BMSL::start();


    while (1) {
        STLIB::update();
        BMSL::update();
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
