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
#include "BarDataCollection.h"

#include "ObservedObject.hpp"

using namespace std;

/** @ingroup core-modules
 *  A class that aggregates the data from different sources, such as the CAN bus and the sensors, and provides them as observed objects.
 *  It uses the ApplicationTypes.h file to define the types of the data, such as velocity_t and voltage_t.
 *  It also uses the DataAggregatorWrapperType.h file to wrap the data aggregator object for the C interface.
 */
class DataAggregator {
public:
    explicit DataAggregator(uint8_t lapEfficiencySize): lapEfficiencies({BarDataCollection<watt_hour_t>(lapEfficiencySize)}) {

    }

    /** The observed object that holds the motor RPM data. */
    ObservedObject<velocity_t> motorRPM{0};
    /** The observed object that holds the battery voltage data. */
    ObservedObject<voltage_t> batteryVoltage{0};
    /** The observed object that holds the current lap time. */
    ObservedObject<ms_t> lapTime{0};
    /** The observed object that holds a collection of lap efficiencies. */
    ObservedObject<BarDataCollection<watt_hour_t>> lapEfficiencies;
};

/** Returns a reference to the data aggregator object from a given wrapper.
 *  @param wrapper The pointer to the wrapper that contains the data aggregator object.
 *  @return A reference to the data aggregator object.
 */
DataAggregator& DataAggregator_GetReference(DataAggregatorWrapper* wrapper);

#endif //UOSM_DASHBOARD_DATAAGGREGATOR_HPP