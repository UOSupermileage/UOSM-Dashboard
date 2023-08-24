//
// Created by Jeremy Cote on 2023-07-25.
//

#include "DataAggregatorWrapper.h"
#include "DataAggregator.hpp"

struct DataAggregatorWrapper {
    DataAggregator aggregator;

    explicit DataAggregatorWrapper(uint8_t motorVelocitiesSize, uint8_t batteryVoltagesSize, uint8_t lapEfficiencySize):
        aggregator(motorVelocitiesSize, batteryVoltagesSize, lapEfficiencySize) {}
};

DataAggregatorWrapper* DataAggregator_Create(uint8_t motorVelocitiesSize, uint8_t batteryVoltagesSize, uint8_t lapEfficiencySize) {
    auto* wrapper = new DataAggregatorWrapper(motorVelocitiesSize, batteryVoltagesSize, lapEfficiencySize);
    return wrapper;
}

void SetMotorRPM(DataAggregatorWrapper* wrapper, velocity_t rpm) {
    wrapper->aggregator.motorVelocities.getMutable()->add(rpm);
}

void SetBatteryVoltage(DataAggregatorWrapper* wrapper, voltage_t voltage) {
    wrapper->aggregator.batteryVoltages.getMutable()->add(voltage);
}

void SetLapTime(DataAggregatorWrapper* wrapper, ms_t time) {
    wrapper->aggregator.lapTime.set(time);
}

DataAggregator& DataAggregator_GetReference(DataAggregatorWrapper* wrapper) {
    return wrapper->aggregator;
}