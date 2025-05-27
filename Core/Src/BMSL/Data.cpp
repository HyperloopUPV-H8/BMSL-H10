#include "BMSL/Data.hpp"
#include "BMSL/BMSL_Pinout.hpp"

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

//--------------- BMS CONFIG FOR LTC6810-DRIVER ----------------

void bms_config::SPI_transmit(const std::span<uint8_t> data) {
    SPI::Instance* spi = SPI::registered_spi[spi_id];
    HAL_SPI_Transmit(spi->hspi, data.data(), data.size(), 10);
}

void bms_config::SPI_receive(const std::span<uint8_t> buffer) {
    SPI::Instance* spi = SPI::registered_spi[spi_id];
    HAL_SPI_Receive(spi->hspi, buffer.data(), buffer.size(), 10);
}

void bms_config::SPI_CS_turn_on() {
    SPI::Instance* spi = SPI::registered_spi[spi_id];
    SPI::turn_on_chip_select(spi);
}

void bms_config::SPI_CS_turn_off() {
    SPI::Instance* spi = SPI::registered_spi[spi_id];
    SPI::turn_off_chip_select(spi);
}

int32_t bms_config::get_tick(){
    return Data::us_counter;
}

//---------------------------------------------------------------


void Data::init() {
    for (auto& cell : cells) cell = new float;

    maximum_cell_voltage = new float;
    minimum_cell_voltage = new float;
    total_voltage = new float;

    balancing = new bool;
    SOC = new float;

    current = new float;
    current_sensor = new LinearSensor<float>(
        CURRENT_SENSOR, current_sensor_slope, current_sensor_offset, current);

    LED_Operational = new DigitalOutput(LED_OPERATIONAL);
    LED_Fault = new DigitalOutput(LED_FAULT);
    
    bms_config::spi_id = SPI::inscribe(SPI::spi3);
}

void Data::start() {

    cells[0] = &battery[0].cells[0];
    cells[1] = &battery[0].cells[1];
    cells[2] = &battery[0].cells[2];
    cells[3] = &battery[0].cells[3];
    cells[4] = &battery[0].cells[4];
    cells[5] = &battery[0].cells[5];
    maximum_cell_voltage = &dummy_float; // REMEMBER, THIS IS DUMMY
    minimum_cell_voltage = &dummy_float; // REMEMBER, THIS IS DUMMY
    total_voltage = &battery[0].total_voltage;
    balancing = &dummy_bool; // REMEMBER, THIS IS DUMMY
    SOC = &dummy_float; // REMEMBER, THIS IS DUMMY

    Time::register_high_precision_alarm(500, +[]() { ++us_counter; });

    /* cells[0] = bmsl->external_adcs[0].battery.cells[0];
    cells[1] = bmsl->external_adcs[0].battery.cells[1];
    cells[2] = bmsl->external_adcs[0].battery.cells[2];
    cells[3] = bmsl->external_adcs[0].battery.cells[3];
    cells[4] = bmsl->external_adcs[0].battery.cells[4];
    cells[5] = bmsl->external_adcs[0].battery.cells[5];
    maximum_cell_voltage = &bmsl->external_adcs[0].battery.maximum_cell;
    minimum_cell_voltage = &bmsl->external_adcs[0].battery.minimum_cell;
    total_voltage = &bmsl->external_adcs[0].battery.total_voltage;

    balancing = &bmsl->external_adcs[0].battery.is_balancing;
    SOC = &bmsl->external_adcs[0].battery.SOC; */
}

void Data::read_temperature() { current_sensor->read(); }

void Data::read() {
    read_temperature();

    bms.update();
}