//
// Created by Jeremy Cote on 2023-07-25.
//

#ifndef UOSM_DASHBOARD_DATAAGGREGATIONMODULE_H
#define UOSM_DASHBOARD_DATAAGGREGATIONMODULE_H

#include "ApplicationTypes.h"

PUBLIC void SystemSetMotorRPM(velocity_t);
PUBLIC velocity_t SystemGetMotorRPM(void);

PUBLIC void SystemSetBatteryVoltage(voltage_t);
PUBLIC voltage_t SystemGetBatteryVoltage(void);

#endif //UOSM_DASHBOARD_DATAAGGREGATIONMODULE_H
