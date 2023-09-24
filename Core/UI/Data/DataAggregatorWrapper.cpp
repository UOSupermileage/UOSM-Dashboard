//
// Created by Jeremy Cote on 2023-07-25.
//

#include "DataAggregatorWrapper.h"
#include "DataAggregator.hpp"

struct DataAggregatorWrapper {
    DataAggregator aggregator;

    explicit DataAggregatorWrapper(uint8_t motorVelocitiesSize, uint8_t batteryVoltagesSize, uint8_t lapEfficienciesSize, uint8_t lapTimesSize, uint8_t throttleSize, uint8_t canLogSize):
        aggregator(motorVelocitiesSize, batteryVoltagesSize, throttleSize, lapEfficienciesSize, lapTimesSize, canLogSize) {}
};

DataAggregatorWrapper* DataAggregator_Create(uint8_t motorVelocitiesSize, uint8_t batteryVoltagesSize, uint8_t lapEfficienciesSize, uint8_t lapTimesSize, uint8_t throttleSize, uint8_t canLogSize) {
    auto* wrapper = new DataAggregatorWrapper(motorVelocitiesSize, batteryVoltagesSize, lapEfficienciesSize, lapTimesSize, throttleSize, canLogSize);
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

void LogCanMessage(DataAggregatorWrapper* wrapper, ICommsMessageLookUpIndex type, uint32_t value, CANLogEntryFormat style) {
    wrapper->aggregator.canLogEntries.add(new CANLogEntry(type, value, style));
}

void LogCanMessagePairValue(DataAggregatorWrapper* wrapper, ICommsMessageLookUpIndex type, uint32_t a, uint32_t b, CANLogEntryFormat style) {
    wrapper->aggregator.canLogEntries.add(new CANLogEntry(type, a, b, style));
}

DataAggregator& DataAggregator_GetReference(DataAggregatorWrapper* wrapper) {
    return wrapper->aggregator;
}