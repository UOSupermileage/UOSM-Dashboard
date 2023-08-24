//
// Created by Jeremy Cote on 2023-07-25.
//

#include "DataAggregatorWrapper.h"
#include "DataAggregator.hpp"

struct DataAggregatorWrapper {
    DataAggregator aggregator;

    explicit DataAggregatorWrapper(uint8_t motorVelocitiesSize, uint8_t batteryVoltagesSize, uint8_t lapEfficienciesSize, uint8_t lapTimesSize):
        aggregator(motorVelocitiesSize, batteryVoltagesSize, lapEfficienciesSize, lapTimesSize) {}
};

DataAggregatorWrapper* DataAggregator_Create(uint8_t motorVelocitiesSize, uint8_t batteryVoltagesSize, uint8_t lapEfficienciesSize, uint8_t lapTimesSize) {
    auto* wrapper = new DataAggregatorWrapper(motorVelocitiesSize, batteryVoltagesSize, lapEfficienciesSize, lapTimesSize);
    return wrapper;
}

void SetMotorRPM(DataAggregatorWrapper* wrapper, velocity_t rpm) {
    wrapper->aggregator.motorVelocities.add(rpm);
}

void SetBatteryVoltage(DataAggregatorWrapper* wrapper, voltage_t voltage) {
    wrapper->aggregator.batteryVoltages.add(voltage);
}

void SetLapTime(DataAggregatorWrapper* wrapper, ms_t time) {
    wrapper->aggregator.lapTimes.add(time);
}

DataAggregator& DataAggregator_GetReference(DataAggregatorWrapper* wrapper) {
    return wrapper->aggregator;
}