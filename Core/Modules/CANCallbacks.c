#include "ApplicationTypes.h"

#include "CANMessageLookUpModule.h"
#include "InternalCommsModule.h"
#include "CANDriver.h"
#include "DataAggregatorWrapper.h"

static DataAggregatorWrapper* aggregatorWrapper;

void CAN_SetAggregator(DataAggregatorWrapper* wrapper) {
    aggregatorWrapper = wrapper;
}

static bool CAN_Enabled() {
    return aggregatorWrapper != NULL;
}

void CAN_Dummy_RPM(velocity_t v) {
    // Invert motor RPM to display in human-readable manor
    SetMotorRPM(aggregatorWrapper, v);
}

void MotorRPMDataCallback(iCommsMessage_t* msg) {
    if (!CAN_Enabled()) {
        return;
    }

    velocity_t rpm = readMsg(msg);
    DebugPrint("CAN rpm received: %d", rpm);
    SetMotorRPM(aggregatorWrapper, rpm * -1);
}

void VoltageDataCallback(iCommsMessage_t* msg) {
    if (!CAN_Enabled()) {
        return;
    }

    uint32_t voltage = readMsg(msg);
    DebugPrint("CAN voltage received: %d", voltage);
    SetBatteryVoltage(aggregatorWrapper, voltage);
}

void ThrottleDataCallback(iCommsMessage_t* msg) {
//    DebugPrint("ThrottleDataCallback not implemented! %d", msg->standardMessageID);
    if (!CAN_Enabled()) {
        return;
    }

    throttle_raw_t throttle = readMsg(msg);
    DebugPrint("CAN throttle received: %d", throttle);
    SetThrottlePosition(aggregatorWrapper, throttle);
}

void ErrorDataCallback(iCommsMessage_t* msg) {
    DebugPrint("ErrorDataCallback not implemented! %d", msg->standardMessageID);
}

void SpeedDataCallback(iCommsMessage_t* msg) {
    DebugPrint("SpeedDataCallback not implemented! %d", msg->standardMessageID);
}

void EventDataCallback(iCommsMessage_t* msg) {
    DebugPrint("EventDataCallback not implemented! %d", msg->standardMessageID);
}

void CurrentVoltageDataCallback(iCommsMessage_t* msg) {
    DebugPrint("CurrentVoltageDataCallback not implemented! %d", msg->standardMessageID);
}
