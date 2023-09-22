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

/** @ingroup core-modules
 * Creates a data aggregator wrapper object and returns a pointer to it.
 * @return A pointer to the data aggregator wrapper object.
*/
DataAggregatorWrapper* DataAggregator_Create(uint8_t motorVelocitiesSize, uint8_t batteryVoltagesSize, uint8_t lapEfficienciesSize, uint8_t lapTimesSize, uint8_t throttleSize);

/** @ingroup core-modules
 *  Sets the motor RPM data in the data aggregator object from a given wrapper.
 *  @param wrapper The pointer to the wrapper that contains the data aggregator object.
 *  @param rpm The motor RPM data to set.
 */
void SetMotorRPM(DataAggregatorWrapper* wrapper, velocity_t rpm);

/** @ingroup core-modules
 *  Sets the battery voltage data in the data aggregator object from a given wrapper.
 *  @param wrapper The pointer to the wrapper that contains the data aggregator object.
 *  @param voltage The battery voltage data to set.
 */
void SetBatteryVoltage(DataAggregatorWrapper* wrapper, voltage_t voltage);

/** @ingroup core-modules
 *  Sets the lap time in the data aggregator object from a given wrapper.
 *  @param wrapper The pointer to the wrapper that contains the data aggregator object.
 *  @param time The runtime to set.
 */
void SetLapTime(DataAggregatorWrapper* wrapper, ms_t time);

/** @ingroup core-modules
 *  Sets the throttle position (using the percentage) in the data aggregator object from a given wrapper.
 *  @param wrapper The pointer to the wrapper that contains the data aggregator object.
 *  @param throttle The throttle position to set.
 */
void SetThrottlePosition(DataAggregatorWrapper* wrapper, percentage_t throttle);

#ifdef  __cplusplus
}
#endif

#endif //UOSM_DASHBOARD_DATAAGGREGATORWRAPPER_H
