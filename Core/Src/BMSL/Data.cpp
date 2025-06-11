#include "BMSL/Data.hpp"

#include "BMSL/BMSL_Pinout.hpp"

//--------------- BMS CONFIG FOR LTC6810-DRIVER ----------------

void Data::BMSConfig::SPI_transmit(const span<uint8_t> data) {
    SPI::Instance* spi = SPI::registered_spi[spi_id];
    HAL_SPI_Transmit(spi->hspi, data.data(), data.size(), 10);
}

void Data::BMSConfig::SPI_receive(span<uint8_t> buffer) {
    SPI::Instance* spi = SPI::registered_spi[spi_id];
    HAL_SPI_Receive(spi->hspi, buffer.data(), buffer.size(), 10);
}

void Data::BMSConfig::SPI_CS_turn_off() {
    SPI::Instance* spi = SPI::registered_spi[spi_id];
    SPI::turn_off_chip_select(spi);
}

void Data::BMSConfig::SPI_CS_turn_on() {
    SPI::Instance* spi = SPI::registered_spi[spi_id];
    SPI::turn_on_chip_select(spi);
}

int32_t Data::BMSConfig::get_tick() { return Data::us_counter; }

//---------------------------------------------------------------

void Data::init() {
    for (auto& cell : cells) cell = new float;

    total_voltage = new float;

    SOC = new float;

    current = new float;
    current_sensor =
        new LinearSensor<float>(CURRENT_SENSOR, 10.236f, -0.751f, current);

    LED_Operational = new DigitalOutput(LED_OPERATIONAL);
    LED_Fault = new DigitalOutput(LED_FAULT);

    BMSConfig::spi_id = SPI::inscribe(SPI::spi3);
}

void Data::start() {
    Time::register_high_precision_alarm(500, +[]() { ++us_counter; });

    cells[0] = &battery[0].cells[0];
    cells[1] = &battery[0].cells[1];
    cells[2] = &battery[0].cells[2];
    cells[3] = &battery[0].cells[3];
    cells[4] = &battery[0].cells[4];
    cells[5] = &battery[0].cells[5];
    total_voltage = &battery[0].total_voltage;
    last_reading_time = HAL_GetTick();
}

void Data::read_temperature(){
    
}

float Data::coulomb_counting_SOC(float current) {
    uint32_t current_time = HAL_GetTick();

    float delta_time = (current_time - last_reading_time) / 1000.0f;
    last_reading_time = current_time;

    float delta_SOC = current * delta_time / CAPACITY_AH * 100.0f;
    return delta_SOC;
}

float Data::ocv_battery_SOC(float c1, float c2, float c3, float c4, float c5,
                            float c6) {
    float total_voltage = c1 + c2 + c3 + c4 + c5 + c6;
    float x =
        total_voltage - 20.0;  // to get a bigger difference between values so
                               // the polynomial is more accurate
    float result = -62.5 + (14.9 * x) + (21.9 * x * x) + (-4.18 * x * x * x);
    return result;
}

void Data::update_SOC() {
    if (first_soc_flag == true) {
        *SOC = ocv_battery_SOC(*cells[0], *cells[1], *cells[2], *cells[3],
                               *cells[4], *cells[5]);
        first_soc_flag = false;
    } else {
        if (std::abs(*current) < REST_THRESHOLD) {
            *SOC += coulomb_counting_SOC(*current);
        } else {
            *SOC = ocv_battery_SOC(*cells[0], *cells[1], *cells[2], *cells[3],
                                   *cells[4], *cells[5]);
        }
    }
}

void Data::read() {
    bms.update();
    current_sensor->read();
    update_SOC();
    read_temperature();
}