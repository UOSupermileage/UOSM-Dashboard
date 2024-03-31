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
 *  It also uses the DataAggregatorWrapperType.h file to wrap the data aggregator object for the C interface.
 */
class DataAggregator {
public:
    Observable<voltage_t> batteryVoltage;
    Observable<lap_efficiencies_t> efficiency;
    Observable<speed_t> speed;
};

/** Returns a reference to the data aggregator object from a given wrapper.
 *  @param wrapper The pointer to the wrapper that contains the data aggregator object.
 *  @return A reference to the data aggregator object.
 */
DataAggregator& DataAggregator_GetReference(DataAggregatorWrapper* wrapper);

#endif //UOSM_DASHBOARD_DATAAGGREGATOR_HPP