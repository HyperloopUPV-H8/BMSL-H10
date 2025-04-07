#ifndef DATA_H
#define DATA_H

#include "BMS-LIB.hpp"


class Data{

    public:


    static std::array<float*, 6> cells;
    static float* maximum_cell_voltage;
    static float* minimum_cell_voltage;
    static float* total_voltage;

    static float* low_battery_temperature_1;
    static float* low_battery_temperature_2;

    static void init();
    static void start();
    static void read();

    static bool enableVoltageRead;
    static bool enableTemperatureRead;

    static BMSH* bmsl;

};

#endif