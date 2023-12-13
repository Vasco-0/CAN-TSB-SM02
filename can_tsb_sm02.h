#ifndef CAN_TSB_SM02_h
#define CAN_TSB_SM02_h

#if defined(__AVR_AT90CAN32__) || defined(__AVR_AT90CAN64__) || defined(__AVR_AT90CAN128__)
#include "../../avr_can/src/avr_can.h"
#include <Arduino.h>
#elif defined(__IMXRT1062__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)
#include "../utility/FlexCAN_T4.h"
#include <TimeLib.h>
#endif

#include "../utility/ArduinoJson.h"
#include "buffer.h"

#define MAXEQ(A, B) (A) = max((A), (B))
#define MAX_NUM_NODES 15
#define MGM_OFFSET 0

class Throttle_Data
{
public:
  int8_t value;                  // Resquested power [-100;100]
  uint8_t status;                       // Status bits

  StaticJsonDocument<256> toJson();     // Subject to size change...
};

// --------------------------------------------------------

class BMS_Data
{

public:
  uint8_t status;                       // Status of the battery
  uint16_t ltc_status;                  // Status of the LTC
  bool *cells_balancing;                // Which cells are balancing
  uint8_t warnings;                     // Warnings

  float soc;                            // Battery State of Charge
  float voltage;                        // Battery pack voltage
  float current;                        // Battery pack current
  float solar_current;                  // Solar Panels current

  float *cellvoltages;                  // Cell Voltages
  float *solar_voltages;                // Solar Array Voltages
  float *temperatures;                  // Temperatures
  float maxTemp;                        // Cells and Bus Bars Max Temperature
  
  StaticJsonDocument<4096> toJson();    // Subject to size change... (Maybe 2048?)
};

// --------------------------------------------------------

class VESC_Data
{

public:
  float motor_current;                  // Motor Current
  float input_current;                  // VESC Input Current

  float duty_cycle;                     // VESC duty cycle
  int32_t rpm;                          // Motor rpm
  float voltage;                        // VESC input voltage

  float temp_mos_1;                     // VESC Mos 1 Temp
  float temp_mos_2;                     // VESC Mos 2 Temp
  float temp_mos_3;                     // VESC Mos 3 Temp
  float temp_mos_max;
  float temp_mot;                       // Motor temperature

  uint8_t fault;                        // VESC Fault code
  uint8_t id;                           // VESC id
  int16_t asked_current;                // Throttle asked current
  int16_t pid_speed;                    // Throttle PID speed

  StaticJsonDocument<512> toJson();     // Subject to size change...
};



