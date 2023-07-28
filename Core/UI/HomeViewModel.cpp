//
// Created by Jeremy Cote on 2023-07-27.
//

#include "HomeViewModel.hpp"
#include "DataAggregationModule.h"
#include <cstdlib>

static lv_timer_t* dataTimer;

static void FetchData(lv_timer_t* timer) {
//    DebugPrint("Fetching data");
//    voltage_t voltage = SystemGetBatteryVoltage();
//    uint32_t n = voltage * 33 * 185 / 40960;
//    lv_label_set_text_fmt(batteryVoltageLabel, "%d.%d Volts", n / 10, n % 10);
//
//    velocity_t velocity = SystemGetMotorRPM();
//    lv_label_set_text_fmt(motorRPMLabel, "%d RPM", velocity);
}