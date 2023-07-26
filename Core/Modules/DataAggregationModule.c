//
// Created by Jeremy Cote on 2023-07-25.
//

#include "DataAggregationModule.h"

static velocity_t motorRPM;

void SystemSetMotorRPM(velocity_t rpm) {
    motorRPM = rpm;
}
velocity_t SystemGetMotorRPM(void) {
    return motorRPM;
}