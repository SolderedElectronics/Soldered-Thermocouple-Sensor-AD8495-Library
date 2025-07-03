/**
 **************************************************
 *
 * @file        AD8495-SOLDERED.h
 * @brief       Header file for Thermocouple sensor
 *              AD8495 breakout
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Josip Šimun Kuči @ Soldered.com
 ***************************************************/

#ifndef __AD8495_SOLDERED__
#define __AD8495_SOLDERED__

#include "Arduino.h"

class AD8495
{
  public:
    AD8495(uint8_t pin, uint16_t resolution_bits, float reference_voltage);
    float getTemperatureC(uint16_t samples);
    float getTemperatureF(uint16_t samples);
    float readVoltage(uint16_t samples);
    void readSensorData(float &temp, float &humidity, float &pressure);
    void setVoltageOffset(float newOffset);
    void setTemperatureOffset(float offset);
    float getTemperatureOffset();
    float getPrecision();
    float getSetpointVoltage(float temperature_c);

  private:
    int _pin;
    float _resolution;
    float _vref;
    float _voltage_offset_constant;
    float _lsb;
    float _offset;
    float _deg_per_mv;
};

#endif