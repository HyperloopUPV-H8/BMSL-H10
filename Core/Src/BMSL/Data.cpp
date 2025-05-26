#include "BMSL/Data.hpp"
#include "BMSL/BMSL.hpp"
#include "BMS-LIB.hpp"

#define current_sensor_offset -0.751
#define current_sensor_slope 10.236

std::array<float*, 6> Data::cells{};
float* Data::maximum_cell_voltage{};
float* Data::minimum_cell_voltage{};
float* Data::total_voltage{};

bool* Data::balancing{};
float* Data::SOC{};

LinearSensor<float>* Data::current_sensor{};
float* Data::current{};

DigitalOutput* Data::LED_Operational{};
DigitalOutput* Data::LED_Fault{};

BMSH* Data::bmsl;

void Data::init() {
    for (auto& cell : cells) cell = new float;

    maximum_cell_voltage = new float;
    minimum_cell_voltage = new float;
    total_voltage = new float;

    balancing = new bool;
    SOC = new float;

    current = new float;
    current_sensor = new LinearSensor<float> (CURRENT_SENSOR, current_sensor_slope, current_sensor_offset, current);

    LED_Operational = new DigitalOutput(LED_OPERATIONAL);
    LED_Fault = new DigitalOutput(LED_FAULT);

    bmsl = new BMSH(SPI::spi3);
}

void Data::start() {
    bmsl->initialize();

    cells[0] = bmsl->external_adcs[0].battery.cells[0];
    cells[1] = bmsl->external_adcs[0].battery.cells[1];
    cells[2] = bmsl->external_adcs[0].battery.cells[2];
    cells[3] = bmsl->external_adcs[0].battery.cells[3];
    cells[4] = bmsl->external_adcs[0].battery.cells[4];
    cells[5] = bmsl->external_adcs[0].battery.cells[5];
    maximum_cell_voltage = &bmsl->external_adcs[0].battery.maximum_cell;
    minimum_cell_voltage = &bmsl->external_adcs[0].battery.minimum_cell;
    total_voltage = &bmsl->external_adcs[0].battery.total_voltage;

    balancing = &bmsl->external_adcs[0].battery.is_balancing;
    SOC = &bmsl->external_adcs[0].battery.SOC;

}

void Data::read_temperature() {
    current_sensor->read();
}

void Data::read() {
    read_temperature();
    bmsl->wake_up();

    bmsl->update_cell_voltages();

    bmsl->external_adcs[0].battery.update_data();
}