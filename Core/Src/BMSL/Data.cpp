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
    *SOC = calculate_battery_SOC();
}

void Data::read_temperature() {}

float Data::calculate_cell_SOC(float voltage) {
    if (voltage <= voltages.front()) {
        return socs.front();
    }
    if (voltage >= voltages.back()) {
        return socs.back();
    }

    size_t left{0};
    size_t right{voltages.size() - 1};

    while (right - left > 1) {
        size_t mid = (left + right) / 2;
        if (voltage < voltages[mid]) {
            right = mid;
        } else {
            left = mid;
        }
    }

    float v1 = voltages[left];
    float v2 = voltages[right];
    float soc1 = socs[left];
    float soc2 = socs[right];

    return soc1 + (soc2 - soc1) * (voltage - v1) / (v2 - v1);
}

float Data::calculate_battery_SOC() {
    float total_soc = 0.0f;

    for (size_t i = 0; i < N_CELLS; ++i) {
        float cell_soc = calculate_cell_SOC(*cells[i]);
        total_soc += cell_soc;
    }

    return (total_soc / static_cast<float>(N_CELLS));
}

void Data::update_SOC() { *SOC = calculate_battery_SOC(); }

void Data::read() {
    bms.update();
    current_sensor->read();
    update_SOC();
    read_temperature();
}