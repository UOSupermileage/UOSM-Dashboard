//
// Created by Jeremy Cote on 2023-07-25.
//

#ifndef UOSM_DASHBOARD_DATAAGGREGATIONMODULE_H
#define UOSM_DASHBOARD_DATAAGGREGATIONMODULE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ApplicationTypes.h"

PUBLIC void SystemSetMotorRPM(velocity_t);

PUBLIC velocity_t SystemGetMotorRPM(void);

PUBLIC void SystemSetBatteryVoltage(voltage_t);

PUBLIC voltage_t SystemGetBatteryVoltage(void);

#ifdef __cplusplus
}
#endif

#endif //UOSM_DASHBOARD_DATAAGGREGATIONMODULE_H
