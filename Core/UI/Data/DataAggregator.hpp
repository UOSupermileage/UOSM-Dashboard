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

#include "Observable.hpp"
#include "CANLogEntry.hpp"

using namespace std;

/** @ingroup core-modules
 *  A class that aggregates the data from different sources, such as the CAN bus and the sensors, and provides them as observed objects.
 *  It uses the ApplicationTypes.h file to define the types of the data, such as velocity_t and voltage_t.
 *  It also uses the DataAggregatorWrapperType.h file to wrap the data aggregator object for the C interface.
 */
class DataAggregator {
public:
    /** The observed object that holds the motor RPM data. */
    Observable<velocity_t> motorVelocity;

    /** The observed object that holds the battery voltage data. */
    Observable<voltage_t> batteryVoltage;

    /** The observed object that holds the current lap time. */
    Observable<ms_t> lapTime;

    /** The observed object that holds the throttle percentage data. */
    Observable<percentage_t> throttlePosition;

    /** The observed object that holds pointers to logged can messages; */
    Observable<CANLogEntry*> canLogEntry;
    /** The observed object that holds the amount of seconds to countdown from */
    Observable<seconds_t> countdownTime;

    Observable<current_t> current;

    Observable<lap_efficiencies_t> efficiency;
};

/** Returns a reference to the data aggregator object from a given wrapper.
 *  @param wrapper The pointer to the wrapper that contains the data aggregator object.
 *  @return A reference to the data aggregator object.
 */
DataAggregator& DataAggregator_GetReference(DataAggregatorWrapper* wrapper);

#endif //UOSM_DASHBOARD_DATAAGGREGATOR_HPP