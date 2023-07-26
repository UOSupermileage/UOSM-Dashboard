//
// Created by Jeremy Cote on 2023-07-25.
//

#include "DataAggregationModule.h"

static velocity_t motorRPM;
static voltage_t voltage;

void SystemSetMotorRPM(velocity_t rpm) {
    motorRPM = rpm;
}
velocity_t SystemGetMotorRPM(void) {
    return motorRPM;
}

PUBLIC void SystemSetBatteryVoltage(voltage_t v) {
    voltage = v;
}
PUBLIC voltage_t SystemGetBatteryVoltage(void) {
    return voltage;
}