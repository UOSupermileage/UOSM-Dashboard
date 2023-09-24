//
// Created by Jeremy Cote on 2023-07-25.
//

#ifndef UOSM_DASHBOARD_DATAAGGREGATOR_HPP
#define UOSM_DASHBOARD_DATAAGGREGATOR_HPP

#include <map>
#include <memory>
#include <variant>

#include "ApplicationTypes.h"
#include "DataAggregatorWrapperType.h"

#include "ObservedDataQueue.hpp"

#include "CANLogEntry.hpp"

using namespace std;

/** @ingroup core-modules
 *  A class that aggregates the data from different sources, such as the CAN bus and the sensors, and provides them as observed objects.
 *  It uses the ApplicationTypes.h file to define the types of the data, such as velocity_t and voltage_t.
 *  It also uses the DataAggregatorWrapperType.h file to wrap the data aggregator object for the C interface.
 */
class DataAggregator {
public:
    explicit DataAggregator(uint8_t motorVelocitiesSize, uint8_t batteryVoltagesSize, uint8_t throttleSize, uint8_t lapEfficienciesSize, uint8_t lapTimesSize, uint8_t canLogMessagesSize, bool prefillLapTimes = true):
            motorVelocities(motorVelocitiesSize),
            batteryVoltages(batteryVoltagesSize),
            throttlePositions(throttleSize),
            lapEfficiencies(lapEfficienciesSize),
            lapTimes(lapTimesSize),
            canLogEntries(canLogMessagesSize) {
        if (prefillLapTimes) {
            for (uint8_t i = 0; i < lapTimesSize; i++){
                lapTimes.add(0);
            }
        }
    }
    /** The observed object that holds the motor RPM data. */
    ObservedDataQueue<velocity_t> motorVelocities;
    /** The observed object that holds the battery voltage data. */
    ObservedDataQueue<voltage_t> batteryVoltages;
    /** The observed object that holds the current lap time. */
    ObservedDataQueue<ms_t> lapTimes;
    /** The observed object that holds a collection of lap efficiencies. */
    ObservedDataQueue<watt_hour_t> lapEfficiencies;
    /** The observed object that holds the throttle percentage data. */
    ObservedDataQueue<percentage_t> throttlePositions;
    /** The observed object that holds pointers to logged can messages; */
    ObservedDataQueue<CANLogEntry*> canLogEntries;
};

/** Returns a reference to the data aggregator object from a given wrapper.
 *  @param wrapper The pointer to the wrapper that contains the data aggregator object.
 *  @return A reference to the data aggregator object.
 */
DataAggregator& DataAggregator_GetReference(DataAggregatorWrapper* wrapper);

#endif //UOSM_DASHBOARD_DATAAGGREGATOR_HPP