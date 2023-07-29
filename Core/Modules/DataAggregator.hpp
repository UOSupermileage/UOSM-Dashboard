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

#include "ObservedObject.hpp"

using namespace std;

class DataAggregator {
public:
    ObservedObject<velocity_t> motorRPM{0};
    ObservedObject<voltage_t> batteryVoltage{0};
};

DataAggregator& DataAggregator_GetReference(DataAggregatorWrapper* wrapper);

#endif //UOSM_DASHBOARD_DATAAGGREGATOR_HPP
