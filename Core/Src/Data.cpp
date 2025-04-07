#include "Data.hpp"
#include "BMS-LIB.hpp"
#include "BMSL.hpp"

bool Data::enableVoltageRead{true};

std::array<float*, 6> Data::cells{};
float* Data::maximum_cell_voltage{};
float* Data::minimum_cell_voltage{};
float* Data::total_voltage{};

bool* Data::balancing{};
float* Data::SOC{};

BMSH* Data::bmsl;

void Data::init() {
    for (auto& cell : cells) cell = new float;

    maximum_cell_voltage = new float;
    minimum_cell_voltage = new float;
    total_voltage = new float;

    balancing = new bool;
    SOC = new float;

    bmsl = new BMSH(SPI::spi3);
}

void Data::start() {
    bmsl->initialize();

    if (enableVoltageRead) {
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

}

void Data::read() {
    bmsl->wake_up();

    if (enableVoltageRead) {
        bmsl->update_cell_voltages();
    }

    bmsl->external_adcs[0].battery.update_data();
}