#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif

#include "ST-LIB.hpp"
#include "BMSL.hpp"

int main(void) {


    BMSL bmsl;
    STLIB::start("192.168.0.7");
    bmsl.init();


    while (1) {
        STLIB::update();
        bmsl.update();
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
