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

void ResetTimer(DataAggregatorWrapper* wrapper, uint32_t timer) {
    DebugPrint("Lap timer reset\n");
    wrapper->aggregator.lapTimer.notify(timer);
}

void SetRPMSpeed(DataAggregatorWrapper* wrapper, int32_t rpm) {
    wrapper->aggregator.rpmSpeed.notify(rpm);
}

void SetBatteryVoltage(DataAggregatorWrapper* wrapper, voltage_t voltage) {
    wrapper->aggregator.batteryVoltage.notify(voltage);
}

void SetBatteryCurrent(DataAggregatorWrapper* wrapper, current_t current) {
    wrapper->aggregator.batteryCurrent.notify(current);
}

void SetMotorTemperature(DataAggregatorWrapper* wrapper, temperature_t temperature) {
    wrapper->aggregator.temperature.notify(temperature);
}

DataAggregator& DataAggregator_GetReference(DataAggregatorWrapper* wrapper) {
    return wrapper->aggregator;
}