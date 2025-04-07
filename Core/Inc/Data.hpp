#ifndef DATA_H
#define DATA_H

#include "BMS-LIB.hpp"


class Data{

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

    static bool enableVoltageRead;

    static BMSH* bmsl;

};

#endif