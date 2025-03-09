#ifndef DATA_H
#define DATA_H

#include "BMS-LIB.hpp"


class Data{

    public:

    Data(){}

        static std::array<float*, 6> cells;
        static float* total_voltage;

        static void init();
        static void read();

        static float* low_battery_temperature_1;
	    static float* low_battery_temperature_2;

        static bool enableVoltageRead;
        static bool enableTemperatureRead;
    
        static BMSH* bmsl;

};

#endif