//
// Created by Jeremy Cote on 2023-07-25.
//

#include "DataAggregatorWrapper.h"
#include "DataAggregator.hpp"

struct DataAggregatorWrapper {
    DataAggregator aggregator;
    explicit DataAggregatorWrapper() : aggregator() {}
};

DataAggregatorWrapper* DataAggregator_Create() {
    return new DataAggregatorWrapper();
}

void SetEfficiency(DataAggregatorWrapper* wrapper, lap_efficiencies_t* efficiencies) {
    wrapper->aggregator.efficiency.notify(*efficiencies);
}

void SetSpeed(DataAggregatorWrapper* wrapper, speed_t speed) {
    wrapper->aggregator.speed.notify(speed);
}

DataAggregator& DataAggregator_GetReference(DataAggregatorWrapper* wrapper) {
    return wrapper->aggregator;
}