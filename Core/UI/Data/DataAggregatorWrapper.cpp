//
// Created by Jeremy Cote on 2023-07-25.
//

#include "DataAggregatorWrapper.h"
#include "DataAggregator.hpp"

struct DataAggregatorWrapper {
    DataAggregator aggregator;

    //TODO: LAP EFFICIENCIES DOESN'T GET USED
    explicit DataAggregatorWrapper(uint8_t motorVelocitiesSize, uint8_t batteryVoltagesSize,
                                   uint8_t lapEfficienciesSize, uint8_t lapTimesSize, uint8_t throttleSize,
                                   uint8_t canLogSize,
                                   uint8_t countdownTimeSize, uint8_t currentSize) :
            aggregator() {}
};

DataAggregatorWrapper*
DataAggregator_Create(uint8_t motorVelocitiesSize, uint8_t batteryVoltagesSize, uint8_t lapEfficienciesSize,
                      uint8_t lapTimesSize, uint8_t throttleSize, uint8_t canLogSize,
                      uint8_t countdownTimeSize, uint8_t currentSize) {
    auto* wrapper = new DataAggregatorWrapper(motorVelocitiesSize, batteryVoltagesSize, lapEfficienciesSize,
                                              lapTimesSize, throttleSize, canLogSize, countdownTimeSize, currentSize);
    return wrapper;
}


void SetCountDownTime(DataAggregatorWrapper* wrapper, seconds_t time) {
    wrapper->aggregator.countdownTime.notify(time);
}

void SetMotorRPM(DataAggregatorWrapper* wrapper, velocity_t rpm) {
    wrapper->aggregator.motorVelocity.notify(rpm);
}

void SetBatteryVoltage(DataAggregatorWrapper* wrapper, voltage_t voltage) {
    wrapper->aggregator.batteryVoltage.notify(voltage);
}

void SetEfficiency(DataAggregatorWrapper* wrapper, lap_efficiencies_t* efficiencies) {
    wrapper->aggregator.efficiency.notify(*efficiencies);
}

void SetCurrent(DataAggregatorWrapper* wrapper, current_t current) {
    wrapper->aggregator.current.notify(current);
}

void SetLapTime(DataAggregatorWrapper* wrapper, ms_t time) {
    wrapper->aggregator.lapTime.notify(time);
}

void
LogCanMessage(DataAggregatorWrapper* wrapper, ICommsMessageLookUpIndex type, uint32_t value, CANLogEntryFormat style) {
    CANLogEntry* e = new CANLogEntry(type, value, style);
    wrapper->aggregator.canLogEntry.notify(e);
}

void LogCanMessagePairValue(DataAggregatorWrapper* wrapper, ICommsMessageLookUpIndex type, uint32_t a, uint32_t b,
                            CANLogEntryFormat style) {
    CANLogEntry* e;
    wrapper->aggregator.canLogEntry.notify(e);
}

void SetThrottlePosition(DataAggregatorWrapper* wrapper, percentage_t throttle) {
    percentage_t p = throttle / 10;
    wrapper->aggregator.throttlePosition.notify(p);
}

DataAggregator& DataAggregator_GetReference(DataAggregatorWrapper* wrapper) {
    return wrapper->aggregator;
}