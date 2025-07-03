/**
 **************************************************
 *
 * @file        AD8495-SOLDERED.cpp
 * @brief       Library for the Thermocouple sensor
 *              AD8495 breakout
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Josip Šimun Kuči @ Soldered.com
 ***************************************************/

#include <AD8495-SOLDERED.hpp>

/**
 * Constructor for the AD8495 sensor interface.
 *
 * @param pin Analog pin connected to the sensor (e.g., A0).
 * @param resolution_bits ADC resolution in bits (default: 12).
 * @param reference_voltage Reference voltage for the ADC (default: 3.3V).
 */
AD8495::AD8495(uint8_t pin, uint16_t resolution_bits, float reference_voltage)
{
    _pin = pin;
    _resolution = pow(2, resolution_bits) - 1;
    _vref = reference_voltage;
    _voltage_offset_constant = 2.5;
    _lsb = _vref / _resolution;
    _offset = 0.0;
    _deg_per_mv = 1.0 / 0.005;  // 5 mV/°C

    #ifndef __AVR__
    analogReadResolution(resolution_bits);
    #endif
}

/**
 * Set a temperature offset in degrees Celsius.
 *
 * @param offset Temperature offset in °C.
 */
void AD8495::setTemperatureOffset(float offset)
{
    _offset = offset;
}

/**
 * Get the current temperature offset in degrees Celsius.
 *
 * @return Temperature offset in °C.
 */
float AD8495::getTemperatureOffset()
{
    return _offset;
}

/**
 * Get the ADC precision (LSB size) in volts.
 *
 * @return LSB voltage.
 */
float AD8495::getPrecision()
{
    return _lsb;
}

/**
 * Read and average analog voltage from the sensor.
 *
 * @param samples Number of ADC samples to average (default: 1).
 * @return Averaged voltage in volts.
 */
float AD8495::readVoltage(uint16_t samples)
{
    uint32_t total = 0;
    for (uint16_t i = 0; i < samples; i++)
    {
        total += analogRead(_pin);
    }
    float avg_raw = static_cast<float>(total) / samples;
    return avg_raw * _lsb;
}

/**
 * Read temperature in degrees Celsius.
 *
 * @param samples Number of ADC samples to average.
 * @return Temperature in °C.
 */
float AD8495::getTemperatureC(uint16_t samples)
{
    float voltage = readVoltage(samples);
    float temp_c = (voltage - _voltage_offset_constant) / 0.005;
    return temp_c + _offset;
}

/**
 * Read temperature in degrees Fahrenheit.
 *
 * @param samples Number of ADC samples to average.
 * @return Temperature in °F.
 */
float AD8495::getTemperatureF(uint16_t samples)
{
    return getTemperatureC(samples) * 1.8 + 32.0;
}

/**
 * Convert a given Celsius temperature to the equivalent output voltage of the sensor.
 *
 * @param temperature_c Temperature in °C.
 * @return Equivalent voltage in volts.
 */
float AD8495::getSetpointVoltage(float temperature_c)
{
    return temperature_c / _deg_per_mv;
}

/**
 * Set a new voltage offset to calibrate the sensor.
 *
 * @param newOffset New voltage offset in volts.
 */
void AD8495::setVoltageOffset(float newOffset)
{
    _voltage_offset_constant = newOffset;
}