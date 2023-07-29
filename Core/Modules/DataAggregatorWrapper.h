//
// Created by Jeremy Cote on 2023-07-29.
//

#ifndef UOSM_DASHBOARD_DATAAGGREGATORWRAPPER_H
#define UOSM_DASHBOARD_DATAAGGREGATORWRAPPER_H

#include "ApplicationTypes.h"
#include "DataAggregatorWrapperType.h"

#ifdef __cplusplus
extern "C" {
#endif

DataAggregatorWrapper* DataAggregator_Create();

void SetMotorRPM(DataAggregatorWrapper* wrapper, velocity_t rpm);
void SetBatteryVoltage(DataAggregatorWrapper* wrapper, voltage_t voltage);

#ifdef  __cplusplus
}
#endif

#endif //UOSM_DASHBOARD_DATAAGGREGATORWRAPPER_H
